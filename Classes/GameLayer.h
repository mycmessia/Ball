//
//  GameLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include "cocos2d.h"
#include "BaseLayer.h"
#include "Ball.h"

#ifndef __Ball__GameLayer__
#define __Ball__GameLayer__

typedef struct matrixCell {
    Ball *sprite;
    bool isVisited;
} *mPointer;

class GameLayer: public BaseLayer
{
private:
    static const int MAX_COL = 7;
    static const int MAX_ROW = 9;
    static const int PADDING_LR = 48;
    static const int PADDING_TB = 48;

    int MENU_TAG;
    int BOARD_TAG;
    int GRADE_LABEL_TAG;
    
    mPointer matrix[MAX_COL][MAX_ROW];
    
    bool isCanTouch = true;
    Ball *FunnyBall = nullptr;
    
    cocos2d::Vec2 touchStart;
    int touchCol = -1;
    int touchRow = -1;
    
public:
    virtual bool init();
    
    void update();
    
    void pauseCallBack(cocos2d::Ref* pSender);
    
    void createRects();         // 创建底板
    
    void initBeginBalls();      // 创建一上来就有的球
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__Ball__GameLayer__) */
