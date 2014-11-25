//
//  GameLayer.h
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include <vector>
#include "cocos2d.h"
#include "Queue.h"
#include "BaseLayer.h"
#include "Ball.h"

#ifndef __Ball__GameLayer__
#define __Ball__GameLayer__

struct matrixCell {
    Ball *sprite;
    bool isVisited;
};

struct pos {
    int col;
    int row;
};

typedef matrixCell *mPointer;

class GameLayer: public BaseLayer
{
private:
    static const int MCELL_WIDTH = 70;
    static const int MCELL_HEIGHT = 70;
    static const int MAX_COL = 7;
    static const int MAX_ROW = 9;
    static const int PADDING_LR = 48;
    static const int PADDING_TB = 48;
    static const int NUM_CAN_REMOVE = 4;
    static const int NEW_BALLS_COUNT = 3;

    int MENU_TAG;
    int BOARD_TAG;
    int GRADE_LABEL_TAG;
    
    mPointer matrix[MAX_COL][MAX_ROW];
    
    bool _isCanTouch = true;
    Ball *_funnyBall = nullptr;
    
    cocos2d::Vec2 touchStart;
    int touchCol;
    int touchRow;
    
    Queue queue;                        // 寻路用临时队列
    Queue path;                         // 最终路线
    
    std::vector<mPointer> removeList;   // 要移除的matrixCellPointer列表
    std::vector<Ball *> nextList;       // 要出现的ball列表
    
    unsigned int grade;                 // 分数
    
public:
    virtual bool init();
    
    void onExit();
    
    void checkCanTouch(float dt);
    
    void pauseCallBack(cocos2d::Ref* pSender);
    
    void createUI();
    
    void initBeginBalls();
    
    void visit(int col, int row);
    void cleanPath();
    void searchPath(pathCell start, pathCell dest);
    void resetIsVisited();
    
    void ballGo(const pathCell& start, const pathCell& dest);
    void ballArrive(const pathCell& start, const pathCell& dest);
    
    bool isCanAdd(int col, int row);
    void checkAddBallToRemove(int col, int row);
    void recoverRemoveList(int sum, int oldLength);
    
    void checkHorizontal(int col, int row);
    void checkVertical(int col, int row);
    void checkAllDirections(int col, int row);
    
    void removeMatrixCells();
    
    std::string calcGrade();
    void setGrade();
    
    void showNextBalls();
    void addNextBalls();
    
    bool isGameOver();
    void handleGameOver();
    
    bool onTouchBegan(cocos2d::Touch *, cocos2d::Event *);
    void onTouchMoved(cocos2d::Touch *, cocos2d::Event *);
    void onTouchEnded(cocos2d::Touch *, cocos2d::Event *);
    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__Ball__GameLayer__) */
