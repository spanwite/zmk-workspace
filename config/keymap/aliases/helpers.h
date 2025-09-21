/* LEADER */
#undef ZMK_LEADER_SEQUENCE
#define ZMK_LEADER_SEQUENCE(name, leader_bindings, leader_sequence) \
    / { \
        behaviors { \
            leader: leader { \
                compatible = "zmk,behavior-leader-key"; \
                #binding-cells = <0>; \
                ignore-keys = <LSHFT RSHFT>; \
                leader_sequence_ ## name { \
                    bindings = <leader_bindings>; \
                    sequence = <leader_sequence>; \
                }; \
            }; \
        }; \
    };

/* MEH */
#define Y_MEH(KEY)      &kp LC(LS(LA(KEY)))
#define Y_SEMI_MEH(KEY) &kp LS(LA(KEY))
#define Y_HYPER(KEY)    &kp LG(LC(LS(KEY)))

/* HOLD TAP */
#define HOLDTAP(NAME, HOLD, TAP) \
    ZMK_HOLD_TAP(NAME, \
        tapping-term-ms = <TAPPING_TERM_FAST>; \
        flavor = "tap-preferred"; \
        quick-tap-ms = <QUICK_TAP_TERM_FAST>; \
        bindings = <HOLD>, <TAP>; \
    )

#define LAYERTAP(NAME, TAP) \
    ZMK_HOLD_TAP(NAME, \
        tapping-term-ms = <TAPPING_TERM_FAST>; \
        flavor = "balanced"; \
        quick-tap-ms = <QUICK_TAP_TERM_SLOW>; \
        bindings = <&mo>, <TAP>; \
    )

#define HT_DOUBLE(NAME, BINDING) \
    HOLDTAP(ht_dbl_ ## NAME, &mc_dbl_ ## NAME, BINDING) \
    MACRO_FLAT(mc_dbl_ ## NAME, BINDING BINDING)

#define MAKE_HRM(NAME, HOLD, TAP, TRIGGER_POS) \
	ZMK_HOLD_TAP(NAME, \
        flavor = "balanced"; \
        tapping-term-ms = <TAPPING_TERM_MEDIUM>; \
        quick-tap-ms = <QUICK_TAP_TERM_SLOW>; \
        require-prior-idle-ms = <PRIOR_IDLE_TERM>; \
        bindings = <HOLD>, <TAP>; \
        hold-trigger-key-positions = <TRIGGER_POS>; \
        hold-trigger-on-release; \
    )

#define MAKE_HML(NAME, HOLD, TAP) MAKE_HRM(NAME, HOLD, TAP, KEYS_R KEYS_T)

#define MAKE_HMR(NAME, HOLD, TAP) MAKE_HRM(NAME, HOLD, TAP, KEYS_L KEYS_T)

/* MOD MORPH */
#define MORPH_SINGLE(NAME, MOD, UNMODDED, MODDED) \
    ZMK_MOD_MORPH(NAME, \
        mods = <(MOD_ ## MOD)>; \
        bindings = <UNMODDED>, <MODDED>; \
    )

#define MORPH_BOTH(NAME, MOD, MODDED, UNMODDED) \
    ZMK_MOD_MORPH(NAME, \
        mods = <(MOD_L ## MOD|MOD_R ## MOD)>; \
        bindings = <MODDED>, <UNMODDED>; \
    )

/* MACROS */
#define MACRO_TAP(NAME, BINDINGS, WAIT_MS, TAP_MS) \
    ZMK_MACRO(NAME, \
        wait-ms = <WAIT_MS>; \
        tap-ms = <TAP_MS>; \
        bindings = <&macro_tap BINDINGS>; \
    )

#define MACRO_FLAT(NAME, BINDINGS) \
	MACRO_TAP(NAME, BINDINGS, 0, 0)

#define MACRO_FAST(NAME, BINDINGS) \
	MACRO_TAP(NAME, BINDINGS, 10, 10)
	
#define MACRO_SLOW(NAME, BINDINGS) \
	MACRO_TAP(NAME, BINDINGS, 100, 100)

#define MACRO_ALT_SYMBOL(NAME, KP_KEYS) \
    ZMK_MACRO(NAME, \
        wait-ms = <0>; \
        tap-ms = <5>; \
        bindings \
        = <&macro_press   &kp LALT> \
        , <&macro_tap     KP_KEYS> \
        , <&macro_release &kp LALT> \
        ; \
    )

/* COMBOS */
#define COMBO(NAME, KEYS, BINDING, LAYERS) \
    ZMK_COMBO(NAME, BINDING, KEYS, LAYERS, COMBO_TERM, COMBO_IDLE_SLOW)

#define COMBO_FAST(NAME, KEYS, BINDING, LAYERS) \
    ZMK_COMBO(NAME, BINDING, KEYS, LAYERS, COMBO_TERM_FAST, COMBO_IDLE_SLOW)

#define COMBO_SLOW(NAME, KEYS, BINDING, LAYERS) \
    ZMK_COMBO(NAME, BINDING, KEYS, LAYERS, COMBO_TERM_SLOW, COMBO_IDLE_FAST)
