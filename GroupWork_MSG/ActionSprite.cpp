//
//  ActionSprite.cpp
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#include "ActionSprite.h"

#pragma mark - 构造,析构
ActionSprite:: ActionSprite()
{
    _actionState = kActionStateNone;
    _directionToRight = true;
    _idleAction=NULL;
    _walkAction = NULL;
    _attackAction = NULL;
    _hurtAction = NULL;
    _knockedOutAction = NULL;

}
ActionSprite::~ActionSprite()
{
    
   


}
bool ActionSprite:: init()
{

    bool bRet = false;
    do {
        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("golden_02.png"));
       //设定缩放以求适应网格
        this->setScale(SPRITE_SCALE);
        this->setRange(1);
        this->setMovement(7);
        this->setHp(10);
        this->setDamage(2);
        _factory= Actions::create();
        _negativeWalkAction = _factory->creatWalkAction("golden_" , 9,12);
        _walkAction = _factory->creatWalkAction("golden_" , 5,8);
        _attackAction = _factory->creatAttackAction("x_attack_",1,20);
        bRet=true;
    } while (0);
    
    return bRet;


}
void ActionSprite::walkWithDirection(bool directionToRight)
{
    
    if (directionToRight) {
        this->runAction(_walkAction);
    }
    else{
        this->runAction(_negativeWalkAction);
    }

}
void ActionSprite:: putSpriteIntoBattleField(CCPoint position)
{
    //获得精灵图片宽高的一半,以便算出图片位置
    float spriteHalfWidth = this->boundingBox().size.width/2;
    float spriteHalfHeight = this->boundingBox().size.height/2;
    //精灵图片出现位置的行号,列号
    int x_row_mun = (position.x - GRID_EDGE)/GRID_WIDTH;
    int y_row_mun = (position.y - GRID_BOTTOM)/GRID_WIDTH;
    //根据行号,列号放置精灵
    this->setPosition(ccp(GRID_EDGE+GRID_WIDTH*x_row_mun+spriteHalfWidth, GRID_BOTTOM+GRID_WIDTH*y_row_mun+spriteHalfHeight));
}

//精灵行动动作
void ActionSprite::goToTarget(ActionSprite * target)
{
//为什么报错
//    this->runAction(_walkAction);
    CCPoint target_point =  target->getPosition();
    CCPoint self_point = this->getPosition();
    CCLog("target_point.x=%f  target_point.y  ==%f",target_point.x,target_point.y);
    CCLog("self_point.x=%f  self_point.y  ==%f",self_point.x,self_point.y);
    //计算出与目标精灵x,y轴上距离几格
    int distance_x =  ccpSub(target_point, self_point).x/GRID_WIDTH;
    int distance_y =  ccpSub(target_point, self_point).y/GRID_WIDTH;
    //精灵的实际攻击范围(单位:格子数)
    int total_range = this->getRange()+this->getMovement();
    //离目标的实际距离(单位:格子数)
    int total_distance =abs(distance_x) +abs(distance_y);
    CCLog("total_range %i  +++++total_distance%i",total_range ,total_distance);
    //如果在总范围内那么移动后攻击
    if (total_range>=total_distance)
    {
        //如果在攻击范围内,直接攻击
        if (this->getRange()>total_distance) {
            
            ///////////////////
            ///////攻击还没写呢//
            ///////////////////
            this->attack(target);
        }
        //否则移动后攻击
        else{
            //计算所需移动步数
            
            int move_step =  total_distance-this->getRange();
            //先走横线再走竖线
            if (move_step>distance_x) {
                CCLog("走折线");
                //水平方向行走动作
                CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*distance_x, ccp(GRID_WIDTH*distance_x,0));
                //垂直方向行走动作
                CCMoveBy * movement_colunm = CCMoveBy::create(ANIMATION_DURATION*(distance_y-1), ccp(0,GRID_WIDTH*(distance_y-1)));
                //动画执行后攻击
                CCCallFuncO * attackCall = CCCallFuncO::create(this, callfuncO_selector(ActionSprite:: attack), target);
                //组合动作
                CCFiniteTimeAction * movement = CCSequence::create(movement_row,movement_colunm,attackCall,NULL);
                CCFiniteTimeAction * move11= CCSequence::create(movement, movement,NULL);
                this->runAction(move11);
//                this->schedule(schedule_selector(attack(target)), ANIMATION_DURATION*(distance_x+distance_y-1));
//                this->schedule(schedule_selector(idle()),5 );

            }
            //走水平方向就够嘞
            else{
                CCLog("走直线");
                CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*move_step, ccp(GRID_WIDTH*move_step,0));
                
                //动画执行后攻击
                CCCallFuncO * attackCall = CCCallFuncO::create(this, callfuncO_selector(ActionSprite:: attack), target);
                //组合动作
                CCFiniteTimeAction * movement = CCSequence::create(movement_row,attackCall,NULL);
                CCFiniteTimeAction * move11= CCSequence::create(movement, movement,NULL);
                this->runAction(move11);
                
            }
        }
    }
    //打不到敌人,水平方向移动
    else
    {
        CCLog("打不到");
        CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*this->getMovement(), ccp(GRID_WIDTH*this->getMovement(),0));
        this->runAction(movement_row);
    
    }
//    CCLog("888888888");
//    CCDelayTime *wait = CCDelayTime::actionWithDuration(11);
//    CCLog("999999999");
    
}
void ActionSprite:: idle()
{
    
    
}

void ActionSprite::attack(ActionSprite * target)
{
    
    CCLog("%i",target->getHp());
    //目标被攻击后hp减少,减少量为攻击者的伤害
    target->setHp(target->getHp()-this->getDamage());
    if (target->getHp()<=0) {
        target->setOpacity(0);
    }
    //十字攻击特效//////////
    ActionSprite * att = ActionSprite::create();
    target->addChild(att,2);
    att->runAction(att->getAttackAction());
    
    att->setPosition(ccp(target->boundingBox().size.width,target->boundingBox().size.width));
    att->setScale(0.4);
    ////////////////

    CCLog("%i",target->getHp());
//    this->unschedule(schedule_selector( attack(target) ));
}
void ActionSprite::hurtWithDamage(float damage)
{

}
void ActionSprite::knockout()
{

}




//更新
//void ActionSprite:: updata()
//{
//    switch (_actionState) {
//        case 0:
//            CCLog("11");
//            break;
//        case 1:
//            this->idle();
//            break;
//        case 2:
//            this->attack();
//            break;
//        case kActionStateWalk:
//
////            this->stopAllActions();
////            this->runAction(_walkAction);
////            _actionState = kActionStateWalk;
//            break;
//        case 4:
////            this->hurtWithDamage(0);
//            break;
//        case 5:
//            this->knockout();
//            break;
//        case kActionStateEdit:
////?
//            break;
//
//        default:
//            break;
//    }
//
//}