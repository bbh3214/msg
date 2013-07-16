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
        
//        this->scheduleUpdate();


   
        bRet=true;
    } while (0);

    _heroes = CCArray::createWithCapacity(10);
    
    _enemy= CCArray::createWithCapacity(10);
    _army= CCArray::createWithCapacity(10);
    //导入plist,pvr.ccz文件入缓存
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("MSG.plist");
    
    _actors = CCSpriteBatchNode::create("MSG.pvr.ccz");
    _actors->getTexture()->setAliasTexParameters();
    this->addChild(_actors,-5);
    
    
    //加入精灵测试走动//////////////
    for (int i=0; i<5; i++) {
        int random= arc4random()%5;
        
        CCLog("________%i",random);
        ActionSprite * temp = ActionSprite::create();
        _actors->addChild(temp,5-i);
        temp->putSpriteIntoBattleField(ccp(GRID_EDGE+GRID_WIDTH*(random),GRID_BOTTOM+GRID_WIDTH*(random)));
        temp->walkWithDirection(true);
//        _heroes->addObject(temp);
        _enemy->addObject(temp);
    }
    for (int i=0; i<1; i++) {
        
        ActionSprite * temp = ActionSprite::create();
        _actors->addChild(temp,5-i);
        temp->putSpriteIntoBattleField(ccp(GRID_EDGE+GRID_WIDTH*(0),GRID_BOTTOM+GRID_WIDTH*(i)));
        temp->walkWithDirection(false);
//        _heroes->addObject(temp);
        _army->addObject(temp);
    }
    CCLog("+++++++++%i",_heroes->count());
    ActionSprite * testMoveS = (ActionSprite *) _army->objectAtIndex(0);
    ActionSprite * testTarget  =this->findTarget(testMoveS);
   
    testMoveS ->goToTarget(testTarget);
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
            
            int distance= this->getDistence(attacker, target);
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
            
            int distance= this->getDistence(attacker, target);
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
    _heroeTest=NULL;
}
void GameLayer:: update(float dt)
{
    if (_heroeTest) {
        _heroeTest->walkWithDirection(true);
    }
    

}