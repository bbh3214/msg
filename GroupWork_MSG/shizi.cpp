//
//  shizi.cpp
//  GroupWork_MSG
//
//  Created by 马梓元 on 13-7-18.
//
//

#include "shizi.h"
#include "Actions.h"
bool Shizi:: init()
{
    bool Rbet = false;
    CCLog("fffff");
    do {
        CC_BREAK_IF(!CCSprite::init());
        
        Actions * temp = Actions::create();
        _atAnimation = temp->creatAttackAction("shizi_", 1, 20);
        _atAnimation->retain();
        this->setPosition(ccp(18,28));
        this->setScale(1.2);
        Rbet = true;
    } while (0);
    return Rbet;
}