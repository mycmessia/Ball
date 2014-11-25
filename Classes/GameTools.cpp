//
//  GameTools.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-11.
//
//
#include "cocos2d.h"
#include "config.h"
#include "GameTools.h"

USING_NS_CC;

GameTools::GameTools() {};

GameTools::~GameTools() {};

void GameTools::init()
{    
    auto director = Director::getInstance();
    
    Size winSize = director->getWinSize();
    
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

double GameTools::getBaseY()
{
    return BASE_Y;
}

void GameTools::setBaseY(double baseY)
{
    BASE_Y = baseY;
}

int GameTools::getMaxZOrder()
{
    return MAX_ZORDER;
}

void GameTools::addImageCache()
{
    FileUtils::getInstance()->addSearchPath(image_search_path);
    FileUtils::getInstance()->addSearchPath(audio_search_path);
    FileUtils::getInstance()->addSearchPath(font_search_path);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_ball_images_plist, s_ball_images);
}

double GameTools::getMoveDis()
{
    return MOVE_DIS;
}