#include "imageinitializer.h"
#include "action.h"
#include "gamemap.h"
#include "gameui.h"
#include "image.h"
#include "unit.h"


void ImageInitializer::ImageInitial() {
  Steve::sm_images[Unit::Hold] =
      new Image(":/image/unit/steve/steve.png", BLOCK_SIZE, BLOCK_SIZE * 2,
                false, QPoint(HALF_BLOCK_SIZE, BLOCK_SIZE + HALF_BLOCK_SIZE));
  Steve::sm_images[Unit::Walk] =
      new Image(":/image/unit/steve/steve_walk.gif", BLOCK_SIZE, BLOCK_SIZE * 2,
                true, QPoint(HALF_BLOCK_SIZE, BLOCK_SIZE + HALF_BLOCK_SIZE));
  Steve::sm_images[Unit::Attack] =
      new Image(":/image/unit/steve/steve_attack.gif", BLOCK_SIZE * 4 / 3,
                BLOCK_SIZE + BLOCK_SIZE, true,
                QPoint(HALF_BLOCK_SIZE * 1.67, BLOCK_SIZE + HALF_BLOCK_SIZE));

  Golem::sm_images[Unit::Hold] =
      new Image(":/image/unit/golem/golem.png", BLOCK_SIZE * 2, BLOCK_SIZE * 3,
                false, QPoint(BLOCK_SIZE, BLOCK_SIZE * 2));
  Golem::sm_images[Unit::Walk] =
      new Image(":/image/unit/golem/golem_walk.gif", BLOCK_SIZE * 2,
                BLOCK_SIZE * 3, true, QPoint(BLOCK_SIZE, BLOCK_SIZE * 2));
  Golem::sm_images[Unit::Attack] = new Image(
      ":/image/unit/golem/golem_attack.gif", BLOCK_SIZE * 2.4, BLOCK_SIZE * 3.5,
      true, QPoint(BLOCK_SIZE * 1.71, BLOCK_SIZE * 2.25));

  Zombie::sm_images[Unit::Hold] =
      new Image(":/image/unit/zombie/zombie.png", BLOCK_SIZE * 1.6,
                BLOCK_SIZE * 3.2, false, QPoint(BLOCK_SIZE, BLOCK_SIZE * 2.3));
  Zombie::sm_images[Unit::Walk] =
      new Image(":/image/unit/zombie/zombie_walk.gif", BLOCK_SIZE * 1.6,
                BLOCK_SIZE * 2.2, true, QPoint(BLOCK_SIZE, BLOCK_SIZE * 1.8));
  Zombie::sm_images[Unit::Attack] =
      new Image(":/image/unit/zombie/zombie_attack.gif", BLOCK_SIZE * 1.6,
                BLOCK_SIZE * 3.2, true, QPoint(BLOCK_SIZE, BLOCK_SIZE * 2.3));

  Creeper::sm_images[Unit::Hold] =
      new Image(":/image/unit/creeper/creeper.png", BLOCK_SIZE, BLOCK_SIZE * 2,
                false, QPoint(HALF_BLOCK_SIZE, BLOCK_SIZE + HALF_BLOCK_SIZE));
  Creeper::sm_images[Unit::Walk] = new Image(
      ":/image/unit/creeper/creeper_walk.gif", BLOCK_SIZE, BLOCK_SIZE * 2, true,
      QPoint(HALF_BLOCK_SIZE, BLOCK_SIZE + HALF_BLOCK_SIZE));
  Creeper::sm_images[Unit::Attack] = new Image(
      ":/image/unit/creeper/creeper_explode.gif", BLOCK_SIZE, BLOCK_SIZE * 2,
      true, QPoint(HALF_BLOCK_SIZE, BLOCK_SIZE + HALF_BLOCK_SIZE));

  Dirt::m_image =
      new Image(":/image/block/dirt/dirt.png", BLOCK_SIZE, BLOCK_SIZE, false,
                QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  Grass::m_image =
      new Image(":/image/block/grass/grass_block_top.png", BLOCK_SIZE,
                BLOCK_SIZE, false, QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  Stone::m_image =
      new Image(":/image/block/stone/stone.png", BLOCK_SIZE, BLOCK_SIZE, false,
                QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  Water::m_image =
      new Image(":/image/block/water/water_still.gif", BLOCK_SIZE, BLOCK_SIZE,
                true, QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  Lava::m_image =
      new Image(":/image/block/lava/lava_still.gif", BLOCK_SIZE, BLOCK_SIZE,
                true, QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  GrassPath::m_image =
      new Image(":/image/block/grasspath/grass_path_top.png", BLOCK_SIZE,
                BLOCK_SIZE, false, QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  Ice::m_image = new Image(":/image/block/ice/ice.png", BLOCK_SIZE, BLOCK_SIZE,
                           false, QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));
  NetherPortal::m_image =
      new Image(":/image/block/netherportal/nether_portal.gif", BLOCK_SIZE,
                BLOCK_SIZE, true, QPoint(HALF_BLOCK_SIZE, HALF_BLOCK_SIZE));

  UnitStatus::m_book =
      new Image(":/image/ui/book/book.png", 300, 400, false, QPoint(0, 0));

  Explosion::m_image = new Image(":/image/item/explosion/explosion.gif", 64, 64,
                                 true, QPoint(32, 32));

  UnitActionMenu::sm_backgroundImage =
      new Image(":/image/ui/background/demo_background.png", 176, 128, false,
                QPoint(0, 0));
  UnitActionMenu::sm_walkIcon =
      new Image(":/image/ui/icon/speed.png", 48, 48, false, QPoint(-8, -8));
  UnitActionMenu::sm_attackIcon =
      new Image(":/image/ui/icon/strength.png", 48, 48, false, QPoint(-8, -8));
  UnitActionMenu::sm_sword = new Image(":/image/ui/icon/iron_sword.png", 48, 48,
                                       false, QPoint(-8, -8));
  UnitActionMenu::sm_axe = new Image(":/image/ui/icon/diamond_axe.png", 48, 48,
                                     false, QPoint(-8, -8));
  UnitActionMenu::sm_tnt =
      new Image(":/image/ui/icon/tnt_side.png", 48, 48, false, QPoint(-8, -8));
  GameIcon::sm_containerImage1 = new Image(
      ":/image/ui/container/container1.png", 64, 64, false, QPoint(0, 0));
  GameIcon::sm_containerImage2 = new Image(
      ":/image/ui/container/container2.png", 64, 64, false, QPoint(0, 0));
}
