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
private:
    constexpr static const double MOVE_DIS = 8.0;
    
    static const int MAX_ZORDER = 99;
    
    Size WIN_SIZE;
    
    Size DESIGN_SIZE;
    
    double SCALE_RATIO;
    
    double BASE_Y;
    
    int TOUCH_PRIORITY_9;
    int TOUCH_PRIORITY_8;
    
    long record;
    
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
    
    double getMoveDis();
    
    int getMaxZOrder();
    
    void addImageCache();
};

#endif /* defined(__Ball__GameTools__) */
