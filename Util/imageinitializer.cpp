#include "imageinitializer.h"
#include "unit.h"
#include "gamemap.h"

void ImageInitializer::ImageInitial() {
    Steve::sm_images[Unit::Hold]=new Image(":/image/unit/steve/steve.png",BLOCK_SIZE,BLOCK_SIZE*2,false,QPoint(HALF_BLOCK_SIZE,BLOCK_SIZE+HALF_BLOCK_SIZE));
    Steve::sm_images[Unit::Walk]=new Image(":/image/unit/steve/steve_walk.gif",BLOCK_SIZE,BLOCK_SIZE*2,true,QPoint(HALF_BLOCK_SIZE,BLOCK_SIZE+HALF_BLOCK_SIZE));
    Steve::sm_images[Unit::Attack]=new Image(":/image/unit/steve/steve_attack.gif",BLOCK_SIZE*4/3,BLOCK_SIZE+BLOCK_SIZE,true,QPoint(HALF_BLOCK_SIZE*1.67,BLOCK_SIZE+HALF_BLOCK_SIZE));

    Golem::sm_images[Unit::Hold]=new Image(":/image/unit/golem/golem.png",BLOCK_SIZE*2,BLOCK_SIZE*3,false,QPoint(BLOCK_SIZE,BLOCK_SIZE*2));
    Golem::sm_images[Unit::Walk]=new Image(":/image/unit/golem/golem_walk.gif",BLOCK_SIZE*2,BLOCK_SIZE*3,true,QPoint(BLOCK_SIZE,BLOCK_SIZE*2));
    Golem::sm_images[Unit::Attack]=new Image(":/image/unit/golem/golem_attack.gif",BLOCK_SIZE*2.4,BLOCK_SIZE*3.5,true,QPoint(BLOCK_SIZE*1.71,BLOCK_SIZE*2.25));

    Zombie::sm_images[Unit::Hold]=new Image(":/image/unit/zombie/zombie.png",BLOCK_SIZE*1.6,BLOCK_SIZE*3.2,false,QPoint(BLOCK_SIZE,BLOCK_SIZE*2.3));
    Zombie::sm_images[Unit::Walk]=new Image(":/image/unit/zombie/zombie_walk.gif",BLOCK_SIZE*1.6,BLOCK_SIZE*2.2,true,QPoint(BLOCK_SIZE,BLOCK_SIZE*1.8));
    Zombie::sm_images[Unit::Attack]=new Image(":/image/unit/zombie/zombie_attack.gif",BLOCK_SIZE*1.6,BLOCK_SIZE*3.2,true,QPoint(BLOCK_SIZE,BLOCK_SIZE*2.3));

    Creeper::sm_images[Unit::Hold]=new Image(":/image/unit/creeper/creeper.png",BLOCK_SIZE,BLOCK_SIZE*2,false,QPoint(HALF_BLOCK_SIZE,BLOCK_SIZE+HALF_BLOCK_SIZE));
    Creeper::sm_images[Unit::Walk]=new Image(":/image/unit/creeper/creeper_walk.gif",BLOCK_SIZE,BLOCK_SIZE*2,true,QPoint(HALF_BLOCK_SIZE,BLOCK_SIZE+HALF_BLOCK_SIZE));
    Creeper::sm_images[Unit::Attack]=new Image(":/image/unit/creeper/creeper_explode.gif",BLOCK_SIZE,BLOCK_SIZE*2,true,QPoint(HALF_BLOCK_SIZE,BLOCK_SIZE+HALF_BLOCK_SIZE));

    Dirt::m_image=new Image(":/image/block/dirt/dirt.png",BLOCK_SIZE,BLOCK_SIZE,false,QPoint(HALF_BLOCK_SIZE,HALF_BLOCK_SIZE));
    Lava::m_image=new Image(":/image/block/lava/lava_still.gif",BLOCK_SIZE,BLOCK_SIZE,true,QPoint(HALF_BLOCK_SIZE,HALF_BLOCK_SIZE));
}