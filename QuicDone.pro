QT += core widgets script
CONFIG += qt c++14

TARGET = QuicDone #HotKey
TEMPLATE = app

RCC_DIR = $$PWD/output/tmp
MOC_DIR = $$PWD/output/tmp
OBJECTS_DIR = $$PWD/output/tmp
DESTDIR = $$PWD/output/bin

SOURCES += \
    src/main.cpp \
    src/HKApplication.cpp \
    src/HKConfig.cpp \
    src/HKDefs.cpp \
    src/HKFunctions.cpp \
    src/HKScript.cpp \
    src/HKAssembly.cpp \
    src/HKHook.cpp

HEADERS += \
    src/HKApplication.h \
    src/HKConfig.h \
    src/HKDefs.h \
    src/HKFunctions.h \
    src/HKScript.h \
    src/HKAssembly.h \
    src/HKHook.h

win32 {
message(Building for Windows)
HEADERS += \
    src/HKApplication_win.hpp \
    src/HKFunctions_win.hpp \
    src/HKDefs_win.hpp \
    src/HKHook_win.hpp
}
unix {
message(Building for Linux)
HEADERS += \
    src/HKApplication_linux.hpp \
    src/HKFunctions_linux.hpp \
    src/HKDefs_linux.hpp \
    src/HKHook_linux.hpp
}

RC_FILE += \
    Resource.rc
