//
//  BtnSprite.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include "BtnSprite.h"

BtnSprite::BtnSprite() {};
BtnSprite::~BtnSprite() {};

void BtnSprite::touchDown()
{
    this->setScale(1.2);
}

void BtnSprite::touchUp()
{
    this->setScale(1);
}