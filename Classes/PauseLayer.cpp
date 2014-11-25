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
    if (!Layer::init())
    {
        return false;
    }
    
    BOARD_TAG = this->getUniqueTag();
    
    auto board = Sprite::createWithSpriteFrameName(s_alert_board);
    board->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() / 2));
    this->addChild(board, GT.getMaxZOrder(), BOARD_TAG);
    
    auto title = Sprite::createWithSpriteFrameName(s_pause);
    title->setPosition(Vec2(board->getContentSize().width / 2, board->getContentSize().height));
    board->addChild(title);
    
    // 继续按钮
    auto resumeSprite = Sprite::createWithSpriteFrameName(s_resume_btn);
    auto resumeSpriteActive = Sprite::createWithSpriteFrameName(s_resume_btn_a);
    auto resumeItem = MenuItemSprite::create(resumeSprite, resumeSpriteActive,
                                            CC_CALLBACK_1(PauseLayer::resumeCallBack, this));
	resumeItem->setAnchorPoint(Vec2::ZERO);
    resumeItem->setScale(0.7f);
    resumeItem->setPosition(Vec2(40, 50));
    
    // 重开按钮
    auto restartSprite = Sprite::createWithSpriteFrameName(s_restart_btn);
    auto restartSpriteActive = Sprite::createWithSpriteFrameName(s_restart_btn_a);
    auto restartItem = MenuItemSprite::create(restartSprite, restartSpriteActive,
                                             CC_CALLBACK_1(PauseLayer::restartCallBack, this));
	restartItem->setAnchorPoint(Vec2::ZERO);
    restartItem->setScale(0.7f);
    restartItem->setPosition(Vec2(140, 50));
    
    // 回首页按钮
    auto goHomeSprite = Sprite::createWithSpriteFrameName(s_go_home_btn);
    auto goHomeSpriteActive= Sprite::createWithSpriteFrameName(s_go_home_btn_a);
    auto goHomeItem = MenuItemSprite::create(goHomeSprite, goHomeSpriteActive,
                                             CC_CALLBACK_1(PauseLayer::goHomeCallBack, this));
	goHomeItem->setAnchorPoint(Vec2::ZERO);
    goHomeItem->setScale(0.7f);
    goHomeItem->setPosition(Vec2(240, 50));
    
    auto menu = Menu::create(resumeItem, restartItem, goHomeItem, NULL);
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
    log("PauseLayer::onTouchBegan");
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

void PauseLayer::restartCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Director::getInstance()->getRunningScene();
    
    scene->removeChildByTag(PAUSE_LAYER);
    scene->removeChildByTag(GAME_LAYER);
    auto layer = GameLayer::create();
    scene->addChild(layer, 0, GAME_LAYER);
}

void PauseLayer::goHomeCallBack(Ref *pSender)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Scene::create();
    auto layer = WelcomeLayer::create();
    scene->addChild(layer, 0, WELCOME_LAYER);
    
    auto replaceAni = TransitionTurnOffTiles::create(0.5f, scene);
    
    Director::getInstance()->replaceScene(replaceAni);
}
