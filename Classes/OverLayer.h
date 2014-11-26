//
//  OverLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-26.
//
//

#ifndef __Ball__OverLayer__
#define __Ball__OverLayer__

#include "cocos2d.h"
#include "AlertLayer.h"

USING_NS_CC;

class OverLayer : public AlertLayer
{
public:
    bool init();
    
    void restartCallBack(cocos2d::Ref* pSender);
    void goHomeCallBack(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(OverLayer);
};
#endif /* defined(__Ball__OverLayer__) */
