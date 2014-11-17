//
//  GameLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include <string>
#include <ctime>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "config.h"
#include "GameLayer.h"
#include "PauseLayer.h"
#include "GameTools.h"
#include "Ball.h"

USING_NS_CC_EXT;
USING_NS_CC;
USING_NS_GC;

extern GameTools GT;

bool GameLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    MAX_COL = 7;
    MAX_ROW = 9;
//    MAX_ROW = (GT.getBaseY() - 380) / 70;
    PADDING_LR = 48;
    PADDING_TB = 48;
    
    MENU_TAG = getUniqueTag();
    BOARD_TAG = getUniqueTag();
    GRADE_LABEL_TAG = getUniqueTag();
    
    auto bg = Sprite::create(s_background);
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg);
    
    // 分数图片
    auto grade = Sprite::createWithSpriteFrameName(s_grade_txt);
    grade->setAnchorPoint(Vec2::ZERO);
    grade->setPosition(Vec2(40, GT.getBaseY() - 70));
    this->addChild(grade);
    
    // 分数Label
    auto gradeLabel = LabelTTF::create("999", "Arial", 50);
    gradeLabel->setColor(Color3B(0, 0, 0));
    gradeLabel->setPosition(Vec2(100, GT.getBaseY() - 120));
    this->addChild(gradeLabel, 0, GRADE_LABEL_TAG);
    
    // 下回出现
    auto next = Sprite::createWithSpriteFrameName(s_next_txt);
    next->setAnchorPoint(Vec2::ZERO);
    next->setPosition(Vec2(320, GT.getBaseY() - 70));
    this->addChild(next);
    
    // 暂停按钮
    auto pauseSprite = Sprite::createWithSpriteFrameName(s_pause_btn);
    auto pauseSpriteActive = Sprite::createWithSpriteFrameName(s_pause_btn_a);
    auto pauseItem = MenuItemSprite::create(pauseSprite, pauseSpriteActive,
                                           CC_CALLBACK_1(GameLayer::pauseCallBack, this));
	pauseItem->setAnchorPoint(Vec2::ZERO);
    pauseItem->setPosition(Vec2(GT.getDesignSize().width - 90, GT.getBaseY() - 90));
    
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0, MENU_TAG);
    
    auto board = Scale9Sprite::create(s_board, Rect(0, 0, 584, 732), Rect(0, 0, 584, 732));
    board->setContentSize(Size(584, 732));
    board->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() / 2 - GT.getBaseY() / 20));
    this->addChild(board, 0, BOARD_TAG);
    
//    createRects();
    
    initBeginBalls();
    
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
    
    scene->addChild(layer, GT.getMaxZOrder(), PAUSE_LAYER);
    
}

void GameLayer::createRects()
{
    auto board = this->getChildByTag(BOARD_TAG);
    auto boardPos = board->getPosition();
    auto batchNode = SpriteBatchNode::create(s_repeat_images, MAX_ROW * MAX_COL * 4);
    batchNode->setAnchorPoint(Vec2::ZERO);
    batchNode->setPosition(Vec2::ZERO);
    board->addChild(batchNode);
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            auto rect = Sprite::createWithTexture(batchNode->getTexture(), Rect(0, 0, 80, 80));
            Size size = rect->getContentSize();
            rect->setPosition(Vec2(
                PADDING_LR + i * size.width + size.width / 2,
                PADDING_TB + j * size.height + size.height / 2
            ));
            batchNode->addChild(rect);
        }
    }
}

void GameLayer::initBeginBalls()
{
    auto board = this->getChildByTag(BOARD_TAG);
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            int n = rand() % 10;
            
            if(n < 2)
            {
                auto ball = Ball::create();
                Size size = Size(Vec2(70, 70));
                ball->setPosition(Vec2(
                    PADDING_LR + i * size.width + size.width / 2,
                    PADDING_TB + j * size.height + size.height / 2
                ));
                board->addChild(ball);
            }
        }
    }
}