//
//  AlertLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-26.
//
//

#ifndef __Ball__AlertLayer__
#define __Ball__AlertLayer__

#include "cocos2d.h"
#include "BaseLayer.h"

USING_NS_CC;

class AlertLayer : public BaseLayer
{
private:
    int BOARD_TAG;
    
public:
    
    bool init();
    
    cocos2d::Sprite* getBoard();
    
    CREATE_FUNC(AlertLayer);
};
#endif /* defined(__Ball__AlertLayer__) */
