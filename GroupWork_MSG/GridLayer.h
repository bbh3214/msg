//
//  Grid.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#ifndef __GroupWork_MSG__GridLayer__
#define __GroupWork_MSG__GridLayer__

#include <iostream>
    #include "cocos2d.h"
using namespace cocos2d;

class GridLayer:public CCLayer {
    
    
public:
    bool init();
    void draw();
    CCSpriteBatchNode *  _actors;
CREATE_FUNC(GridLayer);
};
#endif /* defined(__GroupWork_MSG__Grid__) */
