//
//  PauseLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-13.
//
//
#include "cocos2d.h"
#include "config.h"
#include "GameTools.h"
#include "WelcomeLayer.h"
#include "GameLayer.h"
#include "PauseLayer.h"

USING_NS_CC;
USING_NS_GC;

extern GameTools GT;

PauseLayer::PauseLayer ()
{
    
}

PauseLayer::~PauseLayer()
{
    
}

bool PauseLayer::init()
{
    if (!OverLayer::init())
    {
        return false;
    }
    
    auto board = this->getBoard();
    
    // 继续按钮
    auto resumeSprite = Sprite::createWithSpriteFrameName(s_resume_btn);
    auto resumeSpriteActive = Sprite::createWithSpriteFrameName(s_resume_btn_a);
    auto resumeItem = MenuItemSprite::create(resumeSprite, resumeSpriteActive,
                                            CC_CALLBACK_1(PauseLayer::resumeCallBack, this));
	resumeItem->setAnchorPoint(Vec2::ZERO);
    resumeItem->setScale(0.7f);
    resumeItem->setPosition(Vec2(40, 50));
    
    auto menu = Menu::create(resumeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    board->addChild(menu);
    
    EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);      // 是否吞掉事件让下面的层无法响应
    listener->onTouchBegan = CC_CALLBACK_2(PauseLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PauseLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(PauseLayer::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool PauseLayer::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void PauseLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void PauseLayer::onTouchEnded(Touch *touch, Event *event)
{
    
}

void PauseLayer::resumeCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Director::getInstance()->getRunningScene();
    scene->removeChildByTag(PAUSE_LAYER);
}
