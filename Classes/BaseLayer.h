//
//  BaseLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-11.
//
//

#ifndef __Ball__BaseLayer__
#define __Ball__BaseLayer__

#include "cocos2d.h"

class BaseLayer : public cocos2d::Layer
{
private:
    int tagCounter = 0;
    
public:
    BaseLayer();
    virtual ~BaseLayer();
    
    virtual bool init();
    int getUniqueTag();
    
    CREATE_FUNC(BaseLayer);
};

#endif /* defined(__Ball__BaseLayer__) */
