/**
 * 这里放了一些全局配置
 */

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

class GameView;
class GameScene;
class GameItem;
class GameMain;
class Image;
class Unit;
class Action;
class GameUI;
class UnitStatus;
class Block;
class GameIcon;
class GameUI;
class Bullet;
class Level;
class Encounter;
class Assault;
class GameMap;
class QGraphicsSimpleTextItem;
struct Ability;

class MapController;
class UnitController;
class GameController;

#define INF 0x7fffffff

#endif // GAMECONFIG_H
