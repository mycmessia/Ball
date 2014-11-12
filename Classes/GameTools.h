//
//  GameTools.h
//  Ball
//
//  Created by meiyuchen on 14-11-11.
//
//

#ifndef __Ball__GameTools__
#define __Ball__GameTools__

#include "cocos2d.h"

USING_NS_CC;

class GameTools
{
public:
    GameTools();
    ~GameTools();
    
    void init();
    
    Size getWinSize();
    void setWinSize(Size winSize);
    
    Size getDesignSize();
    void setDesignSize(Size winSize);
    
    double getScaleRatio();
    void setScaleRatio(double scaleRatio);
    
    double getBaseY();
    void setBaseY(double baseY);
    
    void addImageCache();

private:
    Size WIN_SIZE;
    
    Size DESIGN_SIZE;
    
    double MOVE_DIS;
    
    double SCALE_RATIO;
    
    double BASE_Y;
    
    int TOUCH_PRIORITY_9;
    int TOUCH_PRIORITY_8;
    
    int BALL_COLORS;
    
    int BOARD_COL;
    int BOARD_ROW;
    
    long record;
};

#endif /* defined(__Ball__GameTools__) */
