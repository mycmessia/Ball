#include "WelcomeLayer.h"
#include "GameTools.h"
#include "BtnSprite.h"
#include "GameLayer.h"
#include "config.h"

USING_NS_CC;
USING_NS_GC;

extern GameTools GT;

WelcomeLayer::WelcomeLayer()
{
    
}

WelcomeLayer::~WelcomeLayer()
{
    
}

Scene* WelcomeLayer::createScene()
{
    USING_NS_GC;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeLayer::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, WELCOME_LAYER);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WelcomeLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    MENU_TAG = getUniqueTag();
    START_BTN_TAG = getUniqueTag();
    INTRO_BTN_TAG = getUniqueTag();
    QUIT_BTN_TAG = getUniqueTag();
    SETTING_BTN_TAG = getUniqueTag();
    RANK_BTN_TAG = getUniqueTag();

    auto bg = Sprite::create(s_background);
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg);
    
    auto banner = Sprite::createWithSpriteFrameName(s_banner);
    banner->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 150));
    this->addChild(banner);
    
    auto startBtn = Sprite::createWithSpriteFrameName(s_start_btn);
    auto startBtnActive = Sprite::createWithSpriteFrameName(s_start_btn_a);
    auto startItem = MenuItemSprite::create(startBtn, startBtnActive,
                                            CC_CALLBACK_1(WelcomeLayer::startCallBack, this));
    startItem->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 400));
    
    auto introBtn = Sprite::createWithSpriteFrameName(s_intro_btn);
    auto introBtnActive = Sprite::createWithSpriteFrameName(s_intro_btn_a);
    auto introItem = MenuItemSprite::create(introBtn, introBtnActive,
                                            CC_CALLBACK_1(WelcomeLayer::introCallBack, this));
    introItem->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 530));
    
    auto quitBtn = Sprite::createWithSpriteFrameName(s_quit_btn);
    auto quitBtnActive = Sprite::createWithSpriteFrameName(s_quit_btn_a);
    auto quitItem = MenuItemSprite::create(quitBtn, quitBtnActive,
                                           CC_CALLBACK_1(WelcomeLayer::quitCallBack, this));
    quitItem->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 660));
    
    auto settingSprite = Sprite::createWithSpriteFrameName(s_setting_btn);
    auto settingSpriteActive = Sprite::createWithSpriteFrameName(s_setting_btn_a);
    auto settingItem = MenuItemSprite::create(settingSprite, settingSpriteActive,
                                            CC_CALLBACK_1(WelcomeLayer::settingCallBack, this));
	settingItem->setAnchorPoint(Vec2::ZERO);
    settingItem->setPosition(Vec2(GT.getDesignSize().width - 100, 30));
    
    auto rankSprite = Sprite::createWithSpriteFrameName(s_rank_btn);
    auto rankSpriteActive = Sprite::createWithSpriteFrameName(s_rank_btn_a);
    auto rankItem = MenuItemSprite::create(rankSprite, rankSpriteActive,
                                           CC_CALLBACK_1(WelcomeLayer::rankCallBack, this));
	rankItem->setAnchorPoint(Vec2::ZERO);
    rankItem->setPosition(Vec2(GT.getDesignSize().width - 200, 30));
    
    auto menu = Menu::create(startItem, introItem, quitItem, settingItem, rankItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0, MENU_TAG);
    
    EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(WelcomeLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(WelcomeLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(WelcomeLayer::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->setAnchorPoint(Vec2::ZERO);
    this->setScale(GT.getScaleRatio());
    
    return true;
}

bool WelcomeLayer::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void WelcomeLayer::onTouchMoved(Touch *touch, Event *event)
{

}

void WelcomeLayer::onTouchEnded(Touch *touch, Event *event)
{
    
}

void WelcomeLayer::startCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer, 0, GAME_LAYER);
    
    auto replaceAni = TransitionTurnOffTiles::create(0.5f, scene);
    
    Director::getInstance()->replaceScene(replaceAni);
}

void WelcomeLayer::introCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
}

void WelcomeLayer::quitCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
        return;
    #endif
    
        Director::getInstance()->end();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

void WelcomeLayer::settingCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
}

void WelcomeLayer::rankCallBack(Ref* pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
}