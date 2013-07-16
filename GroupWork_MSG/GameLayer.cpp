//
//  GameLayer.cpp
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-11.
//
//

#include "GameLayer.h"

bool GameLayer:: init()
{

    bool bRet = false;
    do {
        
        CC_BREAK_IF(!CCLayer::init());
        
    


   
        bRet=true;
    } while (0);
    this->scheduleUpdate();

    _heroes = CCArray::createWithCapacity(10);
    
    _enemy= CCArray::createWithCapacity(10);
    _army= CCArray::createWithCapacity(10);
    //导入plist,pvr.ccz文件入缓存
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("MSG.plist");
    
    _actors = CCSpriteBatchNode::create("MSG.pvr.ccz");
    _actors->getTexture()->setAliasTexParameters();
    this->addChild(_actors,-5);
    
    
    //加入精灵测试走动//////////////
    for (int i=0; i<1; i++) {
        
        ActionSprite * temp = ActionSprite::create();
        _actors->addChild(temp,5-i);
        temp->putSpriteIntoBattleField(ccp(GRID_EDGE+GRID_WIDTH*(0),GRID_BOTTOM+GRID_WIDTH*(i)));
        temp->walkWithDirection(false);
        _heroes->addObject(temp);
        _army->addObject(temp);
    }
    for (int i=0; i<5; i++) {
        int random= arc4random()%5;
        
        CCLog("________%i",random);
        ActionSprite * temp = ActionSprite::create();
        _actors->addChild(temp,5-i);
        temp->putSpriteIntoBattleField(ccp(GRID_EDGE+GRID_WIDTH*(random%3+3),GRID_BOTTOM+GRID_WIDTH*(random%2+3)));
        temp->walkWithDirection(true);
        _heroes->addObject(temp);
        _enemy->addObject(temp);
    }

    CCLog("+++++++++%i",_heroes->count());

    CCLog("_heroes->retainCount()%i",_heroes->retainCount());
    _heroes->retain();
    _army->retain();
    _enemy->retain();
    CCLog("_heroes->retainCount()%i",_heroes->retainCount());
//    CCLog("+++++++++%i",_heroes->count());
//    ActionSprite * testMoveS = (ActionSprite *) _army->objectAtIndex(0);
//    ActionSprite * testTarget  =this->findTarget(testMoveS);
//   
//    testMoveS ->goToTarget(testTarget);
    ////////////////////////////

       return bRet;
}
//确定精灵最近的对象
ActionSprite* GameLayer::findTarget(ActionSprite* attacker)
{
    
    ActionSprite * target=ActionSprite::create();
    //攻击者为army
    int min=99;
    if (_army->containsObject(attacker)) {
        
        CCObject* obj=NULL;
        
        CCARRAY_FOREACH(_enemy, obj)
        {
            ActionSprite * temp=(ActionSprite*)obj;
            
            int distance= this->getDistence(attacker, temp);
            if (distance<=min) {
                min=distance;
                target=temp;
            }
        }
    }
    //攻击者为enemy
    else
    {
        CCObject* obj=NULL;
        CCARRAY_FOREACH(_army, obj)
        {
            ActionSprite * temp=(ActionSprite*)obj;
            
            int distance= this->getDistence(attacker, temp);
            if (distance<=min) {
                min=distance;
                target=temp;
            }
        }

    
    
    }
    CCLog("min ==== %i",min);
    return target;

    
}
//确定精灵之间的距离
int GameLayer::getDistence(ActionSprite* self,ActionSprite* target)
{
    CCPoint target_point =  target->getPosition();
    CCPoint self_point = self->getPosition();
    //计算出与目标精灵x,y轴上距离几格
    int distance_x =  ccpSub(target_point, self_point).x/GRID_WIDTH;
    int distance_y =  ccpSub(target_point, self_point).y/GRID_WIDTH;
    //离目标的实际距离(单位:格子数)
    int total_distance = abs(distance_x) +abs(distance_y) ;
    CCLog("total_distance ==== %i",total_distance);
    return total_distance;

}
GameLayer:: GameLayer()
{
    _heroes=NULL;
    _actionSprite=NULL;
    _targetSprite=NULL;
}
static float pastTime = 0;
static int pastFrameNum = 0;
void GameLayer:: update(float dt)
{

   
    if (pastFrameNum==30) {
///////////////test////////////////////////////////////////////
//       CCLog("+++++++++%i",_heroes->count());
//        CCLog("+++++++++%@",_actionSprite);
//      CCLog("retainCount%i",_actionSprite->retainCount());
//////////////////////////////////////////////////////////////
        this->test();
    }

    pastTime += dt;
    pastFrameNum += 1;
}
void GameLayer:: test()
{
    static int actionHeroNum=0;
    CCLog("startAnimation =%f",pastTime);
    CCLog("startAnimation =%i",pastFrameNum);
    _actionSprite = (ActionSprite*)_heroes->objectAtIndex(actionHeroNum);
    _targetSprite  =this->findTarget(_actionSprite);
    /////////////////////???????????????????//////////////
    CCLog("%i",_targetSprite->retainCount());
    /////////////////////???????????????????//////////////
    CCFiniteTimeAction * movement = _actionSprite ->goToTarget(_targetSprite);
    actionHeroNum=(1+actionHeroNum)%(_heroes->count());
    CCFiniteTimeAction * finalAction = CCSequence::create(movement,CCDelayTime::actionWithDuration(1.0f),CCCallFunc::create(this, callfunc_selector(GameLayer::test)),NULL);
    _actionSprite->runAction(finalAction);


}

void GameLayer::attack()
{
    
    CCLog("%i",_targetSprite->getHp());
    //目标被攻击后hp减少,减少量为攻击者的伤害
    CCLog("1111=%i",_army->count());
    _targetSprite->setHp(_targetSprite->getHp()-_actionSprite->getDamage());
    CCLog("%i",_targetSprite->getHp());
    if (_targetSprite->getHp()<=0) {
        _targetSprite->setOpacity(0);
         CCLog("3333333333%i",_army->count());
        if (_army->containsObject(_targetSprite)) {
             CCLog("444444444++++++++%i",_army->count());
            _army->removeObject(_targetSprite);
            _heroes->removeObject(_targetSprite);
            CCLog("444444444444%i",_army->count());
        }
        else{
             CCLog("444444444++++++++%i",_army->count());
            _enemy->removeObject(_targetSprite);
            _heroes->removeObject(_targetSprite);
           
        }
    }
    //十字攻击特效//////////
    ActionSprite * att = ActionSprite::create();
    _targetSprite->addChild(att,2);
    att->runAction(att->getAttackAction());
    
    att->setPosition(ccp(_targetSprite->boundingBox().size.width,_targetSprite->boundingBox().size.width));
    att->setScale(0.4);
    ////////////////
    
    
    //    this->unschedule(schedule_selector( attack(target) ));
}
void GameLayer::log()
{
    CCLog("000000");
}