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
    Size WIN_SIZE;
    
    Size DESIGN_SIZE;
    
    double MOVE_DIS;
    
    double SCALE_RATIO;
    
    double BASE_Y;
    
    int TOUCH_PRIORITY_9;
    int TOUCH_PRIORITY_8;
    
    int MAX_COL = 6;
    int MAX_ROW = 7;
    int PADDING_LR = 45;
    int PADDING_TB = 70;
    
    int MAX_ZORDER = 99;
    
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
    
    int getMaxCol();
    int getMaxRow();
    int getPaddingTB();
    int getPaddingLR();
    
    int getMaxZOrder();
    
    void addImageCache();
};

#endif /* defined(__Ball__GameTools__) */
