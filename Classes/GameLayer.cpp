//
//  GameLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include <string>
#include <cmath>
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
    auto gradeLabel = Label::createWithBMFont("numbers.fnt", "123");
    gradeLabel->setAnchorPoint(Vec2::ZERO);
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

void GameLayer::onExit()
{
    Layer::onExit();
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            delete matrix[i][j];
        }
    }
}

void GameLayer::update()
{
    isCanTouch = true;
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            if (matrix[i][j]->sprite && matrix[i][j]->sprite->getNumberOfRunningActions() > 0)
            {
                isCanTouch = false;
                return;
            }
        }
    }}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    if (!isCanTouch) return false;
    
    touchCol = -1;
    touchRow = -1;
    
    auto board = this->getChildByTag(BOARD_TAG);
    touchStart = touch->getLocation();
    log("touchStart.x %f\n", touchStart.x);
    
    auto touchBoardPos = board->convertToNodeSpace(touchStart);
    log("touchBoardPos.x %f\n", touchBoardPos.x);
    
    touchBoardPos.x -= PADDING_LR;
    touchBoardPos.y -= PADDING_TB;
    
    Size size = Size(Vec2(70, 70));
    touchRow = touchBoardPos.y / size.height;
    touchCol = touchBoardPos.x / size.width;

    if (touchRow >= MAX_ROW || touchCol >= MAX_COL ||
        touchBoardPos.x < 0 || touchBoardPos.y < 0)
    {
        touchRow = -1;
        touchCol = -1;
    }
    
    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event)
{
    auto touchMove = touch->getLocation();
    
    log("touchMove.x - touchStart.x: %f\n", touchMove.x - touchStart.x);
    log("touchMove.y - touchStart.y: %f\n", touchMove.y - touchStart.y);
    
    if (abs(touchMove.x - touchStart.x) > GT.getMoveDis() ||
        abs(touchMove.y - touchStart.y) > GT.getMoveDis())
    {
        touchRow = -1;
        touchCol = -1;
    }
}

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
    log("touchRow %d\n", touchRow);
    log("touchCol %d\n", touchCol);
    
    if (touchRow != -1 && touchCol != -1)
    {
        // 如果点击空位置，且已经有funnyBall
        if (!matrix[touchCol][touchRow]->sprite && funnyBall)
        {
            // funnyBall寻路
        }
        else if (matrix[touchCol][touchRow]->sprite)
        {
            if (funnyBall)
            {
                funnyBall->setLocalZOrder(0);
                funnyBall->unFunny();
            }
            
            funnyBall = matrix[touchCol][touchRow]->sprite;
            funnyBall->setLocalZOrder(9);
            funnyBall->setCol(touchCol);
            funnyBall->setRow(touchRow);
            funnyBall->funny();
        }
    }
}

void GameLayer::pauseCallBack(Ref *pSender)
{
    USING_NS_GC;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(s_btn_click);
    
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = PauseLayer::create();
    
    scene->addChild(layer, GT.getMaxZOrder(), PAUSE_LAYER);
    
}

void GameLayer::initBeginBalls()
{
    auto board = this->getChildByTag(BOARD_TAG);
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            matrix[i][j] = new matrixCell;
            matrix[i][j]->sprite = nullptr;
            matrix[i][j]->isVisited = false;
            
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
                
                matrix[i][j]->sprite = ball;
            }
        }
    }
}