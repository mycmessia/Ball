//
//  AlertLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-26.
//
//
#include "cocos2d.h"
#include "config.h"
#include "GameTools.h"
#include "AlertLayer.h"

USING_NS_CC;
USING_NS_GC;

extern GameTools GT;

bool AlertLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    BOARD_TAG = this->getUniqueTag();
    
    auto board = Sprite::createWithSpriteFrameName(s_alert_board);
    board->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() / 2));
    this->addChild(board, GT.getMaxZOrder(), BOARD_TAG);
    
    return true;
}

cocos2d::Sprite* AlertLayer::getBoard()
{
    return (cocos2d::Sprite *)this->getChildByTag(BOARD_TAG);
}