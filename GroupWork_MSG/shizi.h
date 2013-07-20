//
//  shizi.h
//  GroupWork_MSG
//
//  Created by 马梓元 on 13-7-18.
//
//

#ifndef __GroupWork_MSG__shizi__
#define __GroupWork_MSG__shizi__

#include <iostream>
#include "cocos2d.h"
#include "ActionSprite.h"
using namespace cocos2d;
class Shizi: public CCSprite {
    
public:
    CREATE_FUNC(Shizi);
    //    void goToTarget(ActionSprite * target);
    bool init();
    CC_SYNTHESIZE(CCActionInterval*, _atAnimation, AtAnimation);
    
};
#endif /* defined(__GroupWork_MSG__shizi__) */
