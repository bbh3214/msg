//
//  Hero.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-12.
//
//

#ifndef __GroupWork_MSG__Hero__
#define __GroupWork_MSG__Hero__

#include <iostream>
#include "cocos2d.h"
#include "ActionSprite.h"
using namespace cocos2d;
class Hero: public ActionSprite {
    
public:
    CREATE_FUNC(Hero);
//    void goToTarget(ActionSprite * target);
    bool init();
    
    
};
#endif /* defined(__GroupWork_MSG__Hero__) */
