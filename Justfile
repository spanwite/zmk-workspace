config := absolute_path('config')
build := absolute_path('.build')
firmware := absolute_path('firmware')
draw := absolute_path('draw')

set positional-arguments

default:
    @just --list --unsorted

# parse build.yaml and filter targets by expression
_parse_targets $expr:
    #!/usr/bin/env bash
    attrs="[.board, .shield, .snippet, .\"artifact-name\"]"
    filter="(($attrs | map(. // [.]) | combinations), ((.include // {})[] | $attrs)) | join(\",\")"
    echo "$(yq -r "$filter" build.yaml | grep -v "^," | grep -i "${expr/#all/.*}")"

# build firmware for single board & shield combination
_build_single $board $shield $snippet $artifact *west_args:
    #!/usr/bin/env bash
    set -euo pipefail
    artifact="${artifact:-${shield:+${shield// /+}-}${board}}"
    build_dir="{{ build / '$artifact' }}"

    echo "Building firmware for $artifact..."
    west build -s zmk/app -d "$build_dir" -b $board {{ west_args }} ${snippet:+-S "$snippet"} -- \
        -DZMK_CONFIG="{{ config }}" ${shield:+-DSHIELD="$shield"}

    if [[ -f "$build_dir/zephyr/zmk.uf2" ]]; then
        mkdir -p "{{ firmware }}" && cp "$build_dir/zephyr/zmk.uf2" "{{ firmware }}/$artifact.uf2"
    else
        mkdir -p "{{ firmware }}" && cp "$build_dir/zephyr/zmk.bin" "{{ firmware }}/$artifact.bin"
    fi

# build firmware for matching targets
build expr *west_args:
    #!/usr/bin/env bash
    set -euo pipefail
    targets=$(just _parse_targets {{ expr }})

    [[ -z $targets ]] && echo "No matching targets found. Aborting..." >&2 && exit 1
    echo "$targets" | while IFS=, read -r board shield snippet artifact; do
        just _build_single "$board" "$shield" "$snippet" "$artifact" {{ west_args }}
    done

# clear build cache and artifacts
clean:
    rm -rf {{ build }} {{ firmware }}

# clear all automatically generated files
clean-all: clean
    rm -rf .west zmk

# clear nix cache
clean-nix:
    nix-collect-garbage --delete-old

# draw specified keymap with necessary layers and styles
# just _draw_single <input_file> <image_name> [--two-columns] [<layer1 layer2 ...>]
_draw_single $input_file $image_name *args='':
	#!/usr/bin/env bash
	set -euo pipefail
	temp_dir="{{ draw }}/temp"
	config="$temp_dir/config.yaml"

	if [ "$3" == "--two-columns" ]; then
		yq -Yi '.draw_config.n_columns = 2' $config
		shift 1
	else
		yq -Yi '.draw_config.n_columns = 1' $config
	fi

	mkdir -p "{{ draw }}/svg" "{{ draw }}/png"
	keymap -c $config draw "$temp_dir/$input_file" -z "corne" ${3:+-s $3}>"{{ draw }}/svg/$image_name.svg"
	inkscape --export-type png --export-dpi 300 --export-background=white --export-filename "{{ draw }}/png/$image_name.png" "{{ draw }}/svg/$image_name.svg"

# parse and draw the config with all the layers and combos
draw_default:
	#!/usr/bin/env bash
	set -euo pipefail
	keymap -c "{{ draw }}/config.yaml" parse -z "config/keymap/main.keymap" >"{{ draw }}/temp/keymap.yaml"
	just _draw_single "keymap.yaml" "all" --two-columns

# parse and draw various parts of the config
draw:
	#!/usr/bin/env bash
	set -euo pipefail
	config="{{ draw }}/config.yaml"
	temp_dir="{{ draw }}/temp"

	mkdir -p $temp_dir
	keymap -c $config parse -z "config/keymap/main.keymap" >"$temp_dir/keymap.yaml"
	cp "$temp_dir/keymap.yaml" "$temp_dir/keymap.no-separate-combos.yaml"
	cp $config "$temp_dir/config.yaml"
	yq -Yi '.combos |= map(select(.draw_separate != true))' "$temp_dir/keymap.no-separate-combos.yaml"

	just _draw_single "keymap.yaml" "all" --two-columns
	just _draw_single "keymap.no-separate-combos.yaml" "preview" "alpha numRow sym nav"
	just _draw_single "keymap.no-separate-combos.yaml" "main" --two-columns "alpha shifted numRow numpad sym nav mouse fn media"
	just _draw_single "keymap.no-separate-combos.yaml" "game" --two-columns "game dota2 gameExtra gameNumpad gameMouse"
	just _draw_single "keymap.no-separate-combos.yaml" "specific" "mehs lock unlock"

# initialize west
init:
    west init -l config
    west update --fetch-opt=--filter=blob:none
    west zephyr-export

# list build targets
list:
    @just _parse_targets all | sed 's/,*$//' | sort | column

# update west
update:
    west update --fetch-opt=--filter=blob:none

# upgrade zephyr-sdk and python dependencies
upgrade-sdk:
    nix flake update --flake .

[no-cd]
test $testpath *FLAGS:
    #!/usr/bin/env bash
    set -euo pipefail
    testcase=$(basename "$testpath")
    build_dir="{{ build / "tests" / '$testcase' }}"
    config_dir="{{ '$(pwd)' / '$testpath' }}"
    cd {{ justfile_directory() }}

    if [[ "{{ FLAGS }}" != *"--no-build"* ]]; then
        echo "Running $testcase..."
        rm -rf "$build_dir"
        west build -s zmk/app -d "$build_dir" -b native_posix_64 -- \
            -DCONFIG_ASSERT=y -DZMK_CONFIG="$config_dir"
    fi

    ${build_dir}/zephyr/zmk.exe | sed -e "s/.*> //" |
        tee ${build_dir}/keycode_events.full.log |
        sed -n -f ${config_dir}/events.patterns > ${build_dir}/keycode_events.log
    if [[ "{{ FLAGS }}" == *"--verbose"* ]]; then
        cat ${build_dir}/keycode_events.log
    fi

    if [[ "{{ FLAGS }}" == *"--auto-accept"* ]]; then
        cp ${build_dir}/keycode_events.log ${config_dir}/keycode_events.snapshot
    fi
    diff -auZ ${config_dir}/keycode_events.snapshot ${build_dir}/keycode_events.log
