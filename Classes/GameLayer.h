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
private:
    int MAX_COL;
    int MAX_ROW;
    int PADDING_LR;
    int PADDING_TB;

    int MENU_TAG;
    int BOARD_TAG;
    int GRADE_LABEL_TAG;
    
public:
    virtual bool init();
    
    void pauseCallBack(cocos2d::Ref* pSender);
    
    void createRects();         // 创建底板
    
    void initBeginBalls();      // 创建一上来就有的球
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__Ball__GameLayer__) */
