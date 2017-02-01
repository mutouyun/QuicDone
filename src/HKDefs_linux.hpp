#include <linux/input.h>

static const QHash<int, HK::EN_KeyEvent> __evtTable =
{
    { 1, HK::KeyPress   },
    { 0, HK::KeyRelease }
};

static const QHash<int, const char*> __codeTable =
{
    { KEY_SPACE     , "SPACE" },
    { KEY_ESC       , "ESC"   },
    { KEY_ENTER     , "ENTER" },
    { KEY_LEFTSHIFT , "SHIFT" },
    { KEY_RIGHTSHIFT, "SHIFT" },
    { KEY_LEFTCTRL  , "CTRL"  },
    { KEY_RIGHTCTRL , "CTRL"  },
    { KEY_LEFTALT   , "ALT"   },
    { KEY_RIGHTALT  , "ALT"   },
    { KEY_LEFTMETA  , "WIN"   },
    { KEY_RIGHTMETA , "WIN"   },
    { KEY_A         , "A"     },
    { KEY_B         , "B"     },
    { KEY_C         , "C"     },
    { KEY_D         , "D"     },
    { KEY_E         , "E"     },
    { KEY_F         , "F"     },
    { KEY_G         , "G"     },
    { KEY_H         , "H"     },
    { KEY_I         , "I"     },
    { KEY_J         , "J"     },
    { KEY_K         , "K"     },
    { KEY_L         , "L"     },
    { KEY_M         , "M"     },
    { KEY_N         , "N"     },
    { KEY_O         , "O"     },
    { KEY_P         , "P"     },
    { KEY_Q         , "Q"     },
    { KEY_R         , "R"     },
    { KEY_S         , "S"     },
    { KEY_T         , "T"     },
    { KEY_U         , "U"     },
    { KEY_V         , "V"     },
    { KEY_W         , "W"     },
    { KEY_X         , "X"     },
    { KEY_Y         , "Y"     },
    { KEY_Z         , "Z"     },
    { KEY_0         , "0"     },
    { KEY_1         , "1"     },
    { KEY_2         , "2"     },
    { KEY_3         , "3"     },
    { KEY_4         , "4"     },
    { KEY_5         , "5"     },
    { KEY_6         , "6"     },
    { KEY_7         , "7"     },
    { KEY_8         , "8"     },
    { KEY_9         , "9"     }
};
