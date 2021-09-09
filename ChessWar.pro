QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/gamemain.cpp \
    Controller/mapcontroller.cpp \
    Controller/unitcontroller.cpp \
    GameBase/gameitem.cpp \
    GameBase/gamescene.cpp \
    GameBase/gameview.cpp \
    Model/action.cpp \
    Model/gamemap.cpp \
    Model/gameui.cpp \
    Model/level.cpp \
    Model/uielement.cpp \
    Model/unit.cpp \
    Util/imageinitializer.cpp \
    View/image.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Controller/gamemain.h \
    Controller/mapcontroller.h \
    Controller/unitcontroller.h \
    GameBase/GameConfig.h \
    GameBase/gameitem.h \
    GameBase/gamescene.h \
    GameBase/gameview.h \
    Model/action.h \
    Model/gamemap.h \
    Model/gameui.h \
    Model/level.h \
    Model/uielement.h \
    Model/unit.h \
    Util/imageinitializer.h \
    View/image.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += GameBase/
INCLUDEPATH += Controller/
INCLUDEPATH += View/
INCLUDEPATH += Model/
INCLUDEPATH += Asset/
INCLUDEPATH += Util/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Asset/image/block/BlockImage.qrc \
    Asset/image/item/ItemImage.qrc \
    Asset/image/ui/UIImage.qrc \
    Asset/image/unit/UnitImage.qrc
