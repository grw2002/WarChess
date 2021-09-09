#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#define VIEW_WIDTH 1536
#define VIEW_HEIGHT 864
#define MAP_WIDTH 2048
#define MAP_HEIGHT 1536
#define BLOCK_SIZE 64
#define HALF_BLOCK_SIZE 32
#define NUMX 32
#define NUMY 24

#define FPS 30

//#include "gameview.h"
//#include "gamescene.h"
//#include "gameitem.h"

class GameView;
class GameScene;
class GameItem;
class GameMain;
class Image;
class Unit;
class Level;
class Action;
class GameUI;
class UnitStatus;
class Block;
class GameIcon;
class GameUI;

class MapController;
class UnitController;

#include <qDebug>

#endif // GAMECONFIG_H
