//
//  GameTools.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-11.
//
//

#include "GameTools.h"
#include "cocos2d.h"

USING_NS_CC;

GameTools::GameTools() {};

GameTools::~GameTools() {};

void GameTools::init()
{
    auto director = Director::getInstance();
    
    Size winSize = director->getWinSize();
    
    log("winSize.width: %f", winSize.width);
    
    Size designSize = Size(Vec2(640, 960));
    
    double SCALE_RATIO = winSize.width / designSize.width;
    double BASE_Y = winSize.height / SCALE_RATIO;
    
    setWinSize(winSize);
    setDesignSize(designSize);
    setScaleRatio(SCALE_RATIO);
    setBaseY(BASE_Y);
    
    addImageCache();
}

Size GameTools::getWinSize() { return WIN_SIZE; }
void GameTools::setWinSize(cocos2d::Size winSize) { WIN_SIZE = winSize; }

Size GameTools::getDesignSize() { return DESIGN_SIZE; }
void GameTools::setDesignSize(cocos2d::Size designSize) { DESIGN_SIZE = designSize; }

double GameTools::getScaleRatio() { return SCALE_RATIO; }
void GameTools::setScaleRatio(double scaleRatio) { SCALE_RATIO = scaleRatio; }

double GameTools::getBaseY() { return BASE_Y; }
void GameTools::setBaseY(double baseY) { BASE_Y = baseY; }

void GameTools::addImageCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main_images.plist", "main_images.png");
}