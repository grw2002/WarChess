QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/gamecontroller.cpp \
    Controller/gamemain.cpp \
    Controller/mapcontroller.cpp \
    Controller/unitcontroller.cpp \
    GameBase/gameitem.cpp \
    GameBase/gamescene.cpp \
    GameBase/gameview.cpp \
    Help/helpwidget.cpp \
    Model/action.cpp \
    Model/gamemap.cpp \
    Model/gameui.cpp \
    Model/level.cpp \
    Model/unit.cpp \
    Util/imageinitializer.cpp \
    Util/soundinitializer.cpp \
    View/image.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Controller/gamecontroller.h \
    Controller/gamemain.h \
    Controller/mapcontroller.h \
    Controller/unitcontroller.h \
    GameBase/GameConfig.h \
    GameBase/gameitem.h \
    GameBase/gamescene.h \
    GameBase/gameview.h \
    Help/helpwidget.h \
    Model/action.h \
    Model/gamemap.h \
    Model/gameui.h \
    Model/level.h \
    Model/unit.h \
    Util/imageinitializer.h \
    Util/soundinitializer.h \
    View/image.h \
    mainwindow.h

FORMS += \
    Help/helpwidget.ui \
    mainwindow.ui

INCLUDEPATH += GameBase/
INCLUDEPATH += Controller/
INCLUDEPATH += View/
INCLUDEPATH += Model/
INCLUDEPATH += Asset/
INCLUDEPATH += Util/
INCLUDEPATH += Help/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Asset/image/block/BlockImage.qrc \
    Asset/image/item/ItemImage.qrc \
    Asset/image/ui/UIImage.qrc \
    Asset/image/unit/UnitImage.qrc \
    Asset/sound/Sound.qrc \
    Help/Help.qrc
