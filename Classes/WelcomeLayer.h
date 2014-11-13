#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include "BaseLayer.h"

class WelcomeLayer : public BaseLayer
{
private:
    int MENU_TAG;
    int START_BTN_TAG;
    int INTRO_BTN_TAG;
    int QUIT_BTN_TAG;
    int SETTING_BTN_TAG;
    int RANK_BTN_TAG;
    
public:
    WelcomeLayer();
    ~WelcomeLayer();
    
    static cocos2d::Scene *createScene();

    virtual bool init();  
    
    void startCallBack(cocos2d::Ref* pSender);
    
    void introCallBack(cocos2d::Ref* pSender);
    
    void quitCallBack(cocos2d::Ref* pSender);
    
    void settingCallBack(cocos2d::Ref* pSender);
    
    void rankCallBack(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(WelcomeLayer);
};

#endif // __WELCOME_SCENE_H__
