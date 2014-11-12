//
//  BtnSprite.h
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//

#ifndef __Ball__BtnSprite__
#define __Ball__BtnSprite__

#include "cocos2d.h"

class BtnSprite : public cocos2d::Sprite
{
public:
    BtnSprite ();
    ~BtnSprite();
    
    void touchDown();
    void touchUp();
};

#endif /* defined(__Ball__BtnSprite__) */
