//
//  GameLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include "cocos2d.h"
#include "BaseLayer.h"

#ifndef __Ball__GameLayer__
#define __Ball__GameLayer__

class GameLayer: public BaseLayer
{
public:
    virtual bool init();
    
    int MENU_TAG;
    int BOARD_TAG;
    
    void pauseCallBack(cocos2d::Ref* pSender);
    
    void createRects();
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__Ball__GameLayer__) */
