//
//  Ball.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-13.
//
//
#include <string>
#include <ctime>

#include "cocos2d.h"
#include "config.h"
#include "Queue.h"
#include "Ball.h"

USING_NS_CC;

color Ball::getColor()
{
    return _color;
}

void Ball::setColor(color c)
{
    _color = c;
}

int Ball::getCol()
{
    return _col;
}

void Ball::setCol(int col)
{
    _col = col;
}

int Ball::getRow()
{
    return _row;
}

void Ball::setRow(int row)
{
    _row = row;
}

color Ball::getRandomColor()
{
    return (color) (rand() % MAX_COLOR_TYPES);
}

std::string Ball::getBallFrame()
{
    std::string frameName;
    color ballColor = getRandomColor();
    
    setColor(ballColor);
    
    switch (ballColor)
    {
        case blue:
            frameName = s_blue_ball;
            break;
        case yellow:
            frameName = s_yellow_ball;
            break;
        case red:
            frameName = s_red_ball;
            break;
        case green:
            frameName = s_green_ball;
            break;
    }
    
    CCASSERT(frameName.size() > 0, "Invalid spriteFrameName");
    
    return frameName;
}

std::string Ball::getBallFrame(const color ballColor)
{
    std::string frameName;
    
    setColor(ballColor);
    
    switch (ballColor)
    {
        case blue:
            frameName = s_blue_ball;
            break;
        case yellow:
            frameName = s_yellow_ball;
            break;
        case red:
            frameName = s_red_ball;
            break;
        case green:
            frameName = s_green_ball;
            break;
    }
    
    CCASSERT(frameName.size() > 0, "Invalid spriteFrameName");
    
    return frameName;
}

Ball *Ball::create()
{
    Ball *pRet = new Ball();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}


Ball *Ball::create(const color color)
{
    Ball *pRet = new Ball();
    if (pRet && pRet->init(color))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Ball::init()
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(getBallFrame());
    return initWithSpriteFrame(frame);
}

bool Ball::init(const color ballColor)
{
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(getBallFrame(ballColor));
    return initWithSpriteFrame(frame);
}

void Ball::funny()
{
    auto eye = Sprite::createWithSpriteFrameName(s_eye);
    eye->setAnchorPoint(Vec2::ZERO);
    eye->setPosition(Vec2::ZERO);
    this->addChild(eye, 0, EYE_TAG);
}

void Ball::unFunny()
{
    this->removeChildByTag(EYE_TAG);
}