//
//  Hero.cpp
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-12.
//
//

#include "Hero.h"

bool Hero:: init()
{
    bool Rbet = false;
    do {
        CC_BREAK_IF(ActionSprite::init());
        
        
        
        
        
        Rbet = true;
    } while (0);
    return Rbet;
}
/*
void Hero::goToTarget(ActionSprite * target)
{
    this->runAction(this->getWalkAction());
    
    CCPoint target_point =  target->getPosition();
    CCPoint self_point = this->getPosition();
    //计算出与目标精灵x,y轴上距离几格
    int distance_x =  ccpSub(target_point, self_point).x/GRID_WIDTH;
    int distance_y =  ccpSub(target_point, self_point).y/GRID_WIDTH;
    int total_range = this->getRange()+this->getMovement();
    int total_distance = distance_x+distance_y;
    //如果在总范围内那么移动或攻击
    if (total_range>total_distance) {
        //如果在攻击范围内,直接攻击
        if (this->getRange()>total_distance) {
            this->attack(target);
        }
        //否则移动后攻击
        else{
            //计算所需移动步数
            int move_step =  total_distance-this->getRange();
            //先走横线再走竖线
            if (move_step>distance_x) {
                CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*distance_x, ccp(GRID_WIDTH*distance_x,this->getPosition().y));
                CCMoveBy * movement_colunm = CCMoveBy::create(ANIMATION_DURATION*distance_y, ccp(this->getPosition().x,GRID_WIDTH*distance_y));
                CCFiniteTimeAction * movement = CCSequence::create(movement_row,movement_colunm,NULL);
                this->runAction(movement);
            }
        }
        
        
    }
        
       
}
*/