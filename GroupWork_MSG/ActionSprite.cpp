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
    _negativeWalkAction=NULL;
    _negativeattackAction=NULL;
    _attackAction = NULL;
    _hurtAction = NULL;
    _knockedOutAction = NULL;
    _actionDone = false;
    _actionReady=true;

}
ActionSprite::~ActionSprite()
{
    
    _factory->release();
    _attackAction->release();
    _negativeattackAction->release();
    _walkAction->release();
    _negativeWalkAction->release();


}
bool ActionSprite:: init()
{

    bool bRet = false;
    do {
//        CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("zy_05.png"));
         CC_BREAK_IF(!CCSprite::initWithSpriteFrameName("zy_05.png"));
       //设定缩放以求适应网格

        this->setScale(SPRITE_SCALE);
        this->setRange(3);
        this->setMovement(5);
        this->setHp(10);
        this->setDamage(3);
        _factory= Actions::create();
        _factory->retain();
        _negativeWalkAction = _factory->creatWalkAction("zy_" , 9,12);
        _negativeWalkAction-> retain();
        _walkAction = _factory->creatWalkAction("zy_" , 5,8);
        _walkAction->retain();
        _attackAction = _factory->creatAttackAction("zy_melee_",9,12);
        _attackAction->retain();
        _negativeattackAction =_factory->creatAttackAction("zy_melee_", 5, 8);
        _negativeattackAction->retain();
       
        
        this->setAnchorPoint(ccp(0.5, 0.5));
        
        
        _hpBar= CCControlSlider::create("hpbar2.png", "hpbar1.png", "empty.png");
        _hpBar->setPosition(ccp(22, 22));
        _hpBar->setScale(0.99);
        _hpBar->setMaximumValue(1.0);
        _hpBar->setMinimumValue(0);
        _hpBar->setValue(0.5f);
        _hpBar->retain();
        this->addChild(_hpBar,199);
        bRet=true;
    } while (0);
    
    return bRet;


}
void ActionSprite::walkWithDirection(bool directionToRight)
{
    
    if (directionToRight) {
        this->runAction(_walkAction);
        CCLog("this->retainCount()%i",this->retainCount());
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
    this->setPosition(ccp(GRID_EDGE+GRID_WIDTH*(x_row_mun+0.5), GRID_BOTTOM+GRID_WIDTH*(y_row_mun+0.5)));
}
/*
//精灵行动动作
CCFiniteTimeAction* ActionSprite::goToTarget(ActionSprite * target)
{
//为什么报错
//    this->runAction(_walkAction);
    CCFiniteTimeAction * movement ;
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
            
            this->attack(target);
        }
        //否则移动后攻击
        else{
            //计算所需移动步数
            
            int move_step =  total_distance-this->getRange();
            //先走横线再走竖线
            if (move_step>abs(distance_x)) {
                CCLog("走折线");
                //水平方向行走动作
                CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*abs(distance_x), ccp(GRID_WIDTH*distance_x,0));
                //垂直方向行走动作
                CCMoveBy * movement_colunm = CCMoveBy::create(ANIMATION_DURATION*(move_step-abs(distance_x)), ccp(0,GRID_WIDTH*(distance_y)/abs(distance_y)*(move_step-abs(distance_x))));
                //动画执行后攻击
                CCCallFuncO * attackCall = CCCallFuncO::create(this, callfuncO_selector(ActionSprite:: attack), target);
                //组合动作
                movement = CCSequence::create(movement_row,movement_colunm,attackCall,NULL);

            }
            //走水平方向就够嘞
            else{
                CCLog("走直线");
                CCMoveBy * movement_row;
                if (distance_x!=0) {
                
                movement_row = CCMoveBy::create(ANIMATION_DURATION*move_step, ccp(GRID_WIDTH*move_step*distance_x/abs(distance_x),0));
                }
                else{
                movement_row = CCMoveBy::create(ANIMATION_DURATION*move_step, ccp(GRID_WIDTH*move_step,0));
                }
                //动画执行后攻击
                CCCallFuncO * attackCall = CCCallFuncO::create(this, callfuncO_selector(ActionSprite:: attack), target);
                //组合动作
                movement = CCSequence::create(movement_row,attackCall,NULL);
           
                
            }
        }
    }
    //打不到敌人,水平方向移动
    else
    {
        CCLog("打不到");
        
        
        //计算所需移动步数
        
        int move_step = this->getMovement();
        //先走横线再走竖线
        if (move_step>abs(distance_x) ) {
            CCLog("走折线");
            //水平方向行走动作
            CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*abs(distance_x), ccp(GRID_WIDTH*distance_x,0));
            //垂直方向行走动作
            CCMoveBy * movement_colunm = CCMoveBy::create(ANIMATION_DURATION*(move_step-abs(distance_x)), ccp(0,GRID_WIDTH*(move_step-distance_x)));
            //组合动作
            movement = CCSequence::create(movement_row,movement_colunm,NULL);
       
            
        }
        //走水平方向就够嘞
        else{
            CCLog("走直线");
            CCMoveBy * movement_row = CCMoveBy::create(ANIMATION_DURATION*this->getMovement(), ccp(GRID_WIDTH*this->getMovement(),0));
            movement = CCSequence::create(movement_row,NULL);

            
        }
            
    }
    return movement;
    
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
    
    att->setPosition(ccp(target->boundingBox().size.width/2,target->boundingBox().size.width/2));
    att->setScale(0.4);
    ////////////////

    CCLog("%i",target->getHp());
//    this->unschedule(schedule_selector( attack(target) ));
}
 */
void ActionSprite::hurtWithDamage(float damage)
{

}
void ActionSprite::knockout()
{

}

