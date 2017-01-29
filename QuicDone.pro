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
    src/HKAssembly.cpp

HEADERS += \
    src/HKApplication.h \
    src/HKConfig.h \
    src/HKDefs.h \
    src/HKFunctions.h \
    src/HKScript.h \
    src/HKAssembly.h

RC_FILE += \
    Resource.rc
