//
//  GridLayer.cpp
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#include "GridLayer.h"
#include "Define.h"
#include "ActionSprite.h"
using namespace cocos2d;
bool GridLayer:: init()
{
    bool bRet = false;
    do {
        
        CC_BREAK_IF(!CCLayer::init());
      
//        this->scheduleUpdate();
     
        
        
        bRet=true;
    } while (0);
//     this->draw();
    return bRet;



}

void GridLayer:: draw()
{

    for (int i = 0; i<GRID_ROW_NUM+1; i++) {
        
        
        ccDrawLine(ccp(GRID_EDGE, GRID_BOTTOM+GRID_WIDTH*i), ccp(GRID_EDGE+GRID_COLUMN_NUM*GRID_WIDTH,GRID_BOTTOM+GRID_WIDTH*i));
    }
    for (int i = 0; i<GRID_COLUMN_NUM+1; i++) {
        
        
        ccDrawLine(ccp(GRID_EDGE+GRID_WIDTH*i, GRID_BOTTOM), ccp(GRID_EDGE+GRID_WIDTH*i,GRID_BOTTOM+GRID_WIDTH*GRID_ROW_NUM));
    }
 
}