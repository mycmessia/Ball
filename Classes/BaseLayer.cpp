//
//  BaseLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-11.
//
//

#include "BaseLayer.h"

USING_NS_CC;

BaseLayer::BaseLayer()
{
    
}

BaseLayer::~BaseLayer()
{
    
}

bool BaseLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}

int BaseLayer::getUniqueTag()
{
    return m_tagCounter++;
}