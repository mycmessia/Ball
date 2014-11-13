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
    if (!Layer::init())
    {
        return false;
    }
    
    BOARD_TAG = this->getUniqueTag();
    
    auto board = Sprite::createWithSpriteFrameName(s_alert_board);
    board->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() / 2));
    this->addChild(board, GT.getMaxZOrder(), BOARD_TAG);
    
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
    log("PauseLayer::onTouchBegan");
    return true;
}

void PauseLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void PauseLayer::onTouchEnded(Touch *touch, Event *event)
{
    
}

