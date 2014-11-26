//
//  Ball.h
//  Ball
//
//  Created by meiyuchen on 14-11-13.
//
//

#ifndef __Ball__Ball__
#define __Ball__Ball__

#include <string>
#include "cocos2d.h"

#define MAX_COLOR_TYPES 4

enum color
{
    blue = 0,
    yellow,
    red,
    green
};

class Ball : public cocos2d::Sprite
{
private:
    int EYE_TAG = 0;
    
    color _color;
    int _col;
    int _row;
    
public:
    color getColor();
    void setColor(color c);
    
    int getRow();
    void setRow(int row);
    
    int getCol();
    void setCol(int col);
    
    color getRandomColor();
    
    virtual bool init();
    virtual bool init(const color ballColor);
    
    std::string getBallFrame();
    std::string getBallFrame(const color ballColor);
    
    static Ball *create();
    static Ball *create(const color ballColor);
    
    void funny();
    void unFunny();
};

#endif /* defined(__Ball__Ball__) */
