//
//  BattleScene.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#ifndef __GroupWork_MSG__BattleScene__
#define __GroupWork_MSG__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "GridLayer.h"
#include "GameLayer.h"
using namespace cocos2d;
class BattleScene:public CCScene {
    
    
public:
    BattleScene();
    ~BattleScene();
    bool init();
    CREATE_FUNC(BattleScene);
    CC_SYNTHESIZE(GridLayer *, _battleGrid, BattleGrid);
    CC_SYNTHESIZE(GameLayer *, _gameLayer, GameLayer);
};
#endif /* defined(__GroupWork_MSG__BattleScene__) */
