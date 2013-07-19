//
//  Actions.cpp
//  GroupWork_MSG
//
//  Created by S-xy on 13-7-12.
//
//

#include "Actions.h"

//根据每张图片(frame)名字,图片总数量生成动作


bool Actions::  init()
{
    bool bRet =false;
    do {
        
        CC_BREAK_IF(!CCAction::create());
        _act = NULL;
        
        
        
        bRet =true;
    } while (0);
    return bRet;
}

//根据frame创建动画
CCAnimation * Actions:: creatAnimationForAction(const char * picName,int startNum,int endNum,float timePerFrame)
{
    CCAnimation * animation;
    //创建保存frame的数组
    CCArray * frames = CCArray::createWithCapacity(endNum-startNum+1);
    //循环把frame加入数组
    for (int i =startNum; i< endNum+1; i++)
    {
        
        //通过文件名字字符串,获得frame
        CCSpriteFrame * frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("%s%02d.png",picName,i)->getCString());
        
        frames->addObject(frame);
        
    }
    
    //根据数组,创建走路动画
    animation = CCAnimation::createWithSpriteFrames(frames,timePerFrame);
    
    
    return animation;
    
    
}

//设置行走动作        
CCActionInterval * Actions:: creatWalkAction(const char * picName,int startNum,int endNum)
{


    CCAnimation * animation = this->creatAnimationForAction(picName, startNum, endNum,0.3);
    //根据动画创建不断循环执行的动作
    _act = CCRepeatForever::create(CCAnimate::create(animation));
    return _act;

}


//设置攻击动作
CCActionInterval * Actions:: creatAttackAction(const char * picName,int startNum,int endNum)
{
    

    CCAnimation * animation = this->creatAnimationForAction(picName, startNum, endNum,0.1);
    //根据动画创建不断循环执行的动作
    _act =  CCAnimate::create(animation);
    return _act;


    
}
