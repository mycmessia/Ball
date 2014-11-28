//
//  OverLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-26.
//
//
#include <string>
#include "cocos2d.h"
#include "config.h"
#include "GameTools.h"
#include "WelcomeLayer.h"
#include "GameLayer.h"
#include "OverLayer.h"

USING_NS_CC;
USING_NS_GC;

extern GameTools GT;

bool OverLayer::init()
{
    if (!AlertLayer::init())
    {
        return false;
    }
    
    auto board = this->getBoard();
    
    auto title = Sprite::createWithSpriteFrameName(s_over_txt);
    title->setPosition(Vec2(board->getContentSize().width / 2, board->getContentSize().height));
    board->addChild(title);

    // 重开按钮
    auto restartSprite = Sprite::createWithSpriteFrameName(s_restart_btn);
    auto restartSpriteActive = Sprite::createWithSpriteFrameName(s_restart_btn_a);
    auto restartItem = MenuItemSprite::create(restartSprite, restartSpriteActive,
                                              CC_CALLBACK_1(OverLayer::restartCallBack, this));
	restartItem->setAnchorPoint(Vec2::ZERO);
    restartItem->setScale(0.7f);
    restartItem->setPosition(Vec2(70, 50));
    
    // 回首页按钮
    auto goHomeSprite = Sprite::createWithSpriteFrameName(s_go_home_btn);
    auto goHomeSpriteActive= Sprite::createWithSpriteFrameName(s_go_home_btn_a);
    auto goHomeItem = MenuItemSprite::create(goHomeSprite, goHomeSpriteActive,
                                             CC_CALLBACK_1(OverLayer::goHomeCallBack, this));
	goHomeItem->setAnchorPoint(Vec2::ZERO);
    goHomeItem->setScale(0.7f);
    goHomeItem->setPosition(Vec2(200, 50));
    
    auto menu = Menu::create(restartItem, goHomeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    board->addChild(menu);
    
    EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);      // 是否吞掉事件让下面的层无法响应
    listener->onTouchBegan = CC_CALLBACK_2(OverLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(OverLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(OverLayer::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool OverLayer::onTouchBegan(Touch *touch, Event *event)
{
    return true;
}

void OverLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void OverLayer::onTouchEnded(Touch *touch, Event *event)
{
    
}

void OverLayer::restartCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Director::getInstance()->getRunningScene();
    
    this->removeFromParent();
    scene->removeChildByTag(GAME_LAYER);
    auto layer = GameLayer::create();
    scene->addChild(layer, 0, GAME_LAYER);
}

void OverLayer::goHomeCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Scene::create();
    auto layer = WelcomeLayer::create();
    scene->addChild(layer, 0, WELCOME_LAYER);
    
    auto replaceAni = TransitionTurnOffTiles::create(0.5f, scene);
    
    Director::getInstance()->replaceScene(replaceAni);
}