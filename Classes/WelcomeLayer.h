#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class WelcomeLayer : public BaseLayer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void settingCallBack(cocos2d::Ref* pSender);
    
    void rankCallBack(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeLayer);
};

#endif // __WELCOME_SCENE_H__
