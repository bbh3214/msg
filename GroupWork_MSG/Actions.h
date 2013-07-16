//
//  Actions.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-12.
//
//

#ifndef __GroupWork_MSG__Actions__
#define __GroupWork_MSG__Actions__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;


//创建动作的工厂类
class Actions:public CCAction {
    
    
public:
    CREATE_FUNC(Actions);
    bool init();
    
    CC_SYNTHESIZE(CCAction*, _act, Act);
    CCAction* creatWalkAction(const char * picName,int startNum,int endNum);
    CCAction* creatAttackAction(const char * picName,int startNum,int endNum);
    CCAnimation *  creatAnimationForAction(const char * picName,int startNum,int endNum,float timePerFrame);
};
#endif /* defined(__GroupWork_MSG__Actions__) */
