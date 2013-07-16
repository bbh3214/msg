//
//  Define.h
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-10.
//
//

#ifndef GroupWork_MSG_Define_h
#define GroupWork_MSG_Define_h

#pragma once
#include "cocos2d.h"


//屏幕size
#define SCREEN CCDirector::sharedDirector()->getWinSize()

//git参考书籍 swicegood <pragmatic version control using git>2008
/////////GridLayer中////////
//网格宽度
#define GRID_WIDTH 35
//网格离屏幕左边缘距离
#define GRID_EDGE 90
//网格离屏幕下边缘距离
#define GRID_BOTTOM 20
//格子行数
#define GRID_ROW_NUM 5
//格子列数
#define GRID_COLUMN_NUM 9

////////ActionSprite中//////////
//精灵缩放比例
#define SPRITE_SCALE 0.6f
//移动动画每格所需时间
#define ANIMATION_DURATION 0.5
//人物状态枚举
typedef enum _ActionStates
{
    kActionStateNone = 0,
    kActionStateIdle,
    kActionStateAttack,
    kActionStateWalk,
    kActionStateHurt,
    kActionStateKnockedOut,
    kActionStateEdit
    
} ActionStates;

#endif
