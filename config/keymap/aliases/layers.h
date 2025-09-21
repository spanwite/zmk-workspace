#define ALPHA         0
#define SHIFTED       1
#define NUM_ROW       2
#define NUMPAD        3
#define SYM           4

#define GAME_DEFAULT  5
#define GAME_MOUSE    6
#define GAME_DOTA2    7
#define GAME_EXTRA    8
#define GAME_NUMPAD   9

#define NAV           10
#define MOUSE         11
#define FN            12
#define MEDIA         13
#define MEHS          14
#define LOCK          15
#define UNLOCK        16

#define LAYERS_HOLD   NAV SYM FN MEDIA
#define LAYERS_TOGGLE ALPHA MOUSE NUMPAD NUM_ROW SHIFTED MEHS
#define LAYERS_GAME   GAME_DEFAULT GAME_MOUSE GAME_DOTA2 GAME_EXTRA

#define LAYERS_ALL    LAYERS_HOLD LAYERS_TOGGLE
