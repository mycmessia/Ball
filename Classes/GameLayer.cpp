//
//  GameLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include "cocos2d.h"
#include "GameLayer.h"
#include "PauseLayer.h"
#include "GameTools.h"
#include "config.h"

USING_NS_CC;
USING_NS_GC;

extern GameTools GT;

bool GameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    MENU_TAG = getUniqueTag();
    BOARD_TAG = getUniqueTag();
    
    auto bg = Sprite::create(s_background);
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg);
    
    // 分数
    auto grade = Sprite::createWithSpriteFrameName(s_grade_txt);
    grade->setAnchorPoint(Vec2::ZERO);
    grade->setPosition(Vec2(40, GT.getBaseY() - 70));
    this->addChild(grade);
    
    // 下回出现
    auto next = Sprite::createWithSpriteFrameName(s_next_txt);
    next->setAnchorPoint(Vec2::ZERO);
    next->setPosition(Vec2(320, GT.getBaseY() - 70));
    this->addChild(next);
    
    // 暂停按钮
    auto pauseSprite = Sprite::createWithSpriteFrameName(s_pause_btn);
    auto pauseItem = MenuItemSprite::create(pauseSprite, pauseSprite,
                                           CC_CALLBACK_1(GameLayer::pauseCallBack, this));
	pauseItem->setAnchorPoint(Vec2::ZERO);
    pauseItem->setPosition(Vec2(GT.getDesignSize().width - 90, GT.getBaseY() - 90));
    
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0, MENU_TAG);
    
//    Scale9Sprite 游戏面板 无法编译通过
//    auto board = Scale9Sprite::create(s_board, Rect(0, 0, 584, 732), Rect(90, 90, 400, 500));
//    board->setContentSize(Size(584, 732));
//    board->setAnchorPoint(Vec2::ZERO);
//    board->setPosition(Vec2::ZERO);
//    this->addChild(board);
    
    auto board = Sprite::create(s_board);
    board->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() / 2 - GT.getBaseY() / 12));
    this->addChild(board, 0, BOARD_TAG);
    
    createRects();
    
    EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->setAnchorPoint(Vec2::ZERO);
    this->setScale(GT.getScaleRatio());
    
    return true;
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    log("GameLayer::onTouchBegan");
    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event)
{
    
}

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
    
}

void GameLayer::pauseCallBack(Ref *pSender)
{
    USING_NS_GC;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = PauseLayer::create();
    
    scene->addChild(layer, GT.getMaxZOrder(), GAME_LAYER);
    
}

void GameLayer::createRects()
{
    auto board = this->getChildByTag(BOARD_TAG);
    auto boardPos = board->getPosition();
    
    for (int i = 0; i < GT.getMaxCol(); i++)
    {
        for (int j = 0; j < GT.getMaxRow(); j++)
        {
            auto rect = Sprite::createWithSpriteFrameName(s_board_rect);
            Size size = rect->getContentSize();
            rect->setPosition(Vec2(
                GT.getPaddingLR() + i * size.width + size.width / 2,
                GT.getPaddingTB() + j * size.height + size.height / 2
            ));
            board->addChild(rect);
        }
    }
}