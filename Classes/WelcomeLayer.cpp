#include "WelcomeLayer.h"
#include "GameTools.h"
#include "BtnSprite.h"

USING_NS_CC;

extern GameTools GT;

Scene* WelcomeLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WelcomeLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto bg = Sprite::create("background.png");
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg);
    
    auto logo = Sprite::createWithSpriteFrameName("logo");
    logo->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 150));
    this->addChild(logo);
    
    auto startBtn = BtnSprite::createWithSpriteFrameName("start_btn");
    startBtn->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 400));
    this->addChild(startBtn);
    
    auto introBtn = BtnSprite::createWithSpriteFrameName("intro_btn");
    introBtn->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 530));
    this->addChild(introBtn);
    
    auto quitBtn = BtnSprite::createWithSpriteFrameName("quit_btn");
    quitBtn->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() - 660));
    this->addChild(quitBtn);
    
    auto settingSprite = Sprite::createWithSpriteFrameName("setting_btn");
    auto closeItem = MenuItemSprite::create(settingSprite, settingSprite,
                                            CC_CALLBACK_1(WelcomeLayer::settingCallBack, this));
	closeItem->setAnchorPoint(Vec2::ZERO);
    closeItem->setPosition(Vec2(GT.getDesignSize().width - 100, 30));
    
    auto rankSprite = Sprite::createWithSpriteFrameName("rank_btn");
    auto rankItem = MenuItemSprite::create(rankSprite, rankSprite,
                                           CC_CALLBACK_1(WelcomeLayer::rankCallBack, this));
	rankItem->setAnchorPoint(Vec2::ZERO);
    rankItem->setPosition(Vec2(GT.getDesignSize().width - 200, 30));
    
    auto menu = Menu::create(closeItem, rankItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
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
    log("WelcomeLayer touch begin\n");
    return true;
}

void WelcomeLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void WelcomeLayer::onTouchEnded(Touch *touch, Event *event)
{
    log("WelcomeLayer touch end\n");
}

void WelcomeLayer::settingCallBack(Ref* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}

void WelcomeLayer::rankCallBack(Ref* pSender)
{
    
}