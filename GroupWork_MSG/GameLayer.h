//
//  GameLayer.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-11.
//
//

#ifndef __GroupWork_MSG__GameLayer__
#define __GroupWork_MSG__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "ActionSprite.h"
#include "Hero.h"
#include "shizi.h"
using namespace cocos2d;
class GameLayer:public CCLayer
{
public:
    CREATE_FUNC(GameLayer);
    CCSpriteBatchNode * _actors;
    CCSpriteBatchNode * _showAttacks;
    bool init();
    void update(float dt);
    GameLayer();
    CC_SYNTHESIZE_RETAIN(CCArray * , _heroes, Heroes);
    CC_SYNTHESIZE_RETAIN(CCArray * , _army, Army);
    CC_SYNTHESIZE_RETAIN(CCArray * , _enemy, Enemy);
    CC_SYNTHESIZE_RETAIN(ActionSprite * , _actionSprite, ActionSprite);
    CC_SYNTHESIZE_RETAIN(ActionSprite * , _targetSprite, TargetSprite);
    CC_SYNTHESIZE_RETAIN(CCControlSlider * , _hpBar, HpBar);
    ActionSprite* findTarget(ActionSprite* attacker);
    int getDistence(ActionSprite* self,ActionSprite* target);
    CCFiniteTimeAction* goToTarget();
    void isactnot();
    void attack();
    void log();
    void test();
    void valueChanged();
};

#endif /* defined(__GroupWork_MSG__GameLayer__) */
