//
//  ActionSprite.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#ifndef __GroupWork_MSG__ActionSprite__
#define __GroupWork_MSG__ActionSprite__

#include <iostream>
 #include "cocos2d.h"
#include "Define.h"
#include "Actions.h"
using namespace cocos2d;
class ActionSprite: public CCSprite {

public:
    CREATE_FUNC(ActionSprite);
    //状态
    CC_SYNTHESIZE(ActionStates , _actionState, ActionState);
    CC_SYNTHESIZE(bool, _directionToRight, DirectionToRight);
    //工厂类对象用于创建action
    CC_SYNTHESIZE_RETAIN(Actions *, _factory, Factory);
    //动作
    
    CC_SYNTHESIZE_RETAIN(CCAction *, _idleAction, IdleAction);
    CC_SYNTHESIZE_RETAIN(CCAction *, _attackAction, AttackAction);
    CC_SYNTHESIZE_RETAIN(CCAction *, _walkAction, WalkAction);
    CC_SYNTHESIZE_RETAIN(CCAction *, _negativeWalkAction, NegativeWalkAction);
    CC_SYNTHESIZE_RETAIN(CCAction *, _hurtAction, HurtAction);
    CC_SYNTHESIZE_RETAIN(CCAction *, _knockedOutAction, KnockedOutAction);
    //属性
    CC_SYNTHESIZE(int, _hp, Hp);
    CC_SYNTHESIZE(int, _damage, Damage);
    CC_SYNTHESIZE(int, _movement, Movement);
    CC_SYNTHESIZE(int, _range, Range);
    //更新函数
    void updata();
    //动作状态
    void idle();
    
    void attack(ActionSprite * target);
    void hurtWithDamage(float damage);
    void knockout();
    void walkWithDirection(bool directionToRight);
    //构造,析构
    ActionSprite();
    ~ActionSprite();
    bool init();
    //放置精灵进入战场
    void  putSpriteIntoBattleField(CCPoint position);
    //放置精灵行动
    void goToTarget(ActionSprite * target);

};
#endif /* defined(__GroupWork_MSG__ActionSprite__) */
