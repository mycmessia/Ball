//
//  PauseLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-13.
//
//

#ifndef __Ball__PauseLayer__
#define __Ball__PauseLayer__

#include "cocos2d.h"
#include "BaseLayer.h"

USING_NS_CC;

class PauseLayer : public BaseLayer
{
private:
    int BOARD_TAG;
    
public:
    PauseLayer();
    ~PauseLayer();
    
    bool init();
    
    void resumeCallBack(cocos2d::Ref* pSender);
    
    void restartCallBack(cocos2d::Ref* pSender);
    
    void goHomeCallBack(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(PauseLayer);
};

#endif /* defined(__Ball__PauseLayer__) */
