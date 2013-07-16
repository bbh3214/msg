//
//  BattleScene.cpp
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#include "BattleScene.h"
#include "ActionSprite.h"

BattleScene::BattleScene()
{
    _battleGrid = NULL;
    _gameLayer = NULL;
}

BattleScene::~BattleScene()
{

}

bool BattleScene:: init()
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!CCScene::init());
        _battleGrid = GridLayer::create();
        
        this->addChild(_battleGrid,-6);
        _gameLayer = GameLayer::create();
        this->addChild(_gameLayer,-5);
        bRet=true;
    } while (0);

    return bRet;
}