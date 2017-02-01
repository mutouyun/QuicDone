#include <Windows.h>

static const QHash<int, HK::EN_KeyEvent> __evtTable =
{
    { WM_SYSKEYDOWN, HK::KeyPress   },
    { WM_KEYDOWN   , HK::KeyPress   },
    { WM_SYSKEYUP  , HK::KeyRelease },
    { WM_KEYUP     , HK::KeyRelease }
};

static const QHash<int, const char*> __codeTable =
{
    { VK_SPACE   , "SPACE" },
    { VK_ESCAPE  , "ESC"   },
    { VK_RETURN  , "ENTER" },
    { VK_LSHIFT  , "SHIFT" },
    { VK_RSHIFT  , "SHIFT" },
    { VK_LCONTROL, "CTRL"  },
    { VK_RCONTROL, "CTRL"  },
    { VK_LMENU   , "ALT"   },
    { VK_RMENU   , "ALT"   },
    { VK_LWIN    , "WIN"   },
    { 'A'        , "A"     },
    { 'B'        , "B"     },
    { 'C'        , "C"     },
    { 'D'        , "D"     },
    { 'E'        , "E"     },
    { 'F'        , "F"     },
    { 'G'        , "G"     },
    { 'H'        , "H"     },
    { 'I'        , "I"     },
    { 'J'        , "J"     },
    { 'K'        , "K"     },
    { 'L'        , "L"     },
    { 'M'        , "M"     },
    { 'N'        , "N"     },
    { 'O'        , "O"     },
    { 'P'        , "P"     },
    { 'Q'        , "Q"     },
    { 'R'        , "R"     },
    { 'S'        , "S"     },
    { 'T'        , "T"     },
    { 'U'        , "U"     },
    { 'V'        , "V"     },
    { 'W'        , "W"     },
    { 'X'        , "X"     },
    { 'Y'        , "Y"     },
    { 'Z'        , "Z"     },
    { '0'        , "0"     },
    { '1'        , "1"     },
    { '2'        , "2"     },
    { '3'        , "3"     },
    { '4'        , "4"     },
    { '5'        , "5"     },
    { '6'        , "6"     },
    { '7'        , "7"     },
    { '8'        , "8"     },
    { '9'        , "9"     }
};
