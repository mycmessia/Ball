//
//  GameLayer.cpp
//  Ball
//
//  Created by meiyuchen on 14-11-12.
//
//
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "config.h"
#include "Queue.h"
#include "GameLayer.h"
#include "PauseLayer.h"
#include "OverLayer.h"
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
    
    touchCol = -1;
    touchRow = -1;
    grade = 0;
    
    MENU_TAG = getUniqueTag();
    BOARD_TAG = getUniqueTag();
    GRADE_LABEL_TAG = getUniqueTag();
    
    srand((unsigned)time(nullptr));
    
    createUI();
    
    initBeginBalls();
    
    showNextBalls();
    
    EventDispatcher *eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->setAnchorPoint(Vec2::ZERO);
    this->setScale(GT.getScaleRatio());
    
    this->schedule(schedule_selector(GameLayer::checkCanTouch));
    
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

void GameLayer::checkCanTouch(float dt)
{
    _isCanTouch = true;
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            if (matrix[i][j]->sprite && matrix[i][j]->sprite->getNumberOfRunningActions() > 0)
            {
                _isCanTouch = false;
                return;
            }
        }
    }
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    if (!_isCanTouch) return false;
    
    touchCol = -1;
    touchRow = -1;
    
    auto board = this->getChildByTag(BOARD_TAG);
    touchStart = touch->getLocation();
    
    auto touchBoardPos = board->convertToNodeSpace(touchStart);
    
    touchBoardPos.x -= PADDING_LR;
    touchBoardPos.y -= PADDING_TB;
    
    Size size = Size(Vec2(MCELL_WIDTH, MCELL_HEIGHT));
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
    if (!_isCanTouch) return;
    
    auto touchMove = touch->getLocation();
    
    if (abs(touchMove.x - touchStart.x) > GT.getMoveDis() ||
        abs(touchMove.y - touchStart.y) > GT.getMoveDis())
    {
        touchRow = -1;
        touchCol = -1;
    }
}

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
    if (!_isCanTouch) return;
    
    if (touchRow != -1 && touchCol != -1)
    {
        // 如果点击空位置，且已经有funnyBall
        if (!matrix[touchCol][touchRow]->sprite && _funnyBall)
        {
            // funnyBall寻路
            pathCell start = {_funnyBall->getCol(), _funnyBall->getRow(), -1};
            pathCell dest = {touchCol, touchRow, -1};
            
            searchPath(start, dest);
        }
        else if (matrix[touchCol][touchRow]->sprite)
        {
            if (_funnyBall)
            {
                _funnyBall->setLocalZOrder(0);
                _funnyBall->unFunny();
            }
            
            _funnyBall = matrix[touchCol][touchRow]->sprite;
            _funnyBall->setLocalZOrder(9);
            _funnyBall->setCol(touchCol);
            _funnyBall->setRow(touchRow);
            _funnyBall->funny();
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

void GameLayer::createUI()
{
    auto bgLayerColor = LayerColor::create(Color4B(140, 207, 243, 255));
    this->addChild(bgLayerColor);
    
    auto bg = Sprite::createWithSpriteFrameName(s_background);
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg);
    
    // 分数图片
    auto scoreImg = Sprite::createWithSpriteFrameName(s_score_txt);
    scoreImg->setAnchorPoint(Vec2::ZERO);
    scoreImg->setPosition(Vec2(40, GT.getBaseY() - 70));
    this->addChild(scoreImg);
    
    // 分数Label
    std::stringstream ss;
    ss << grade;
    auto gradeLabel = Label::createWithBMFont(s_number_fnt, ss.str());
    gradeLabel->setPosition(Vec2(100, GT.getBaseY() - 100));
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
    pauseItem->setScale(0.7f);
    pauseItem->setPosition(Vec2(GT.getDesignSize().width - 60, GT.getBaseY() - 50));
    
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0, MENU_TAG);
    
    auto board = Sprite::createWithSpriteFrameName(s_board);
    board->setPosition(Vec2(GT.getDesignSize().width / 2, GT.getBaseY() / 2 - GT.getBaseY() / 20));
    this->addChild(board, 0, BOARD_TAG);
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
                Size size = Size(Vec2(MCELL_WIDTH, MCELL_HEIGHT));
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

void GameLayer::visit(int col, int row)
{
    matrix[col][row]->isVisited = true;
    pathCell p = {
        col, row, queue.getHead() - 1
    };
    queue.enqueue(p);
}

void GameLayer::cleanPath()
{
    while (!path.isEmpty())
    {
        path.dequeue();
    }
    
    while (!queue.isEmpty())
    {
        queue.dequeue();
    }
}

void GameLayer::searchPath(pathCell start, pathCell dest)
{
    cleanPath();
    
    queue.enqueue(start);
    
    pathCell nowPos;
    
    while (!queue.isEmpty())
    {
        nowPos = queue.dequeue();
        
        if (nowPos.col == dest.col && nowPos.row == dest.row)
            break;
        
        /* go up */
        if (nowPos.row - 1 >= 0 &&
            !matrix[nowPos.col][nowPos.row - 1]->sprite &&
            matrix[nowPos.col][nowPos.row - 1]->isVisited == false)
        {
            visit(nowPos.col, nowPos.row - 1);
        }
        
        /* down */
        if (nowPos.row + 1 < MAX_ROW &&
            !matrix[nowPos.col][nowPos.row + 1]->sprite &&
            matrix[nowPos.col][nowPos.row + 1]->isVisited == false)
        {
            visit(nowPos.col, nowPos.row + 1);
        }
        
        /* left */
        if (nowPos.col - 1 >= 0 &&
            !matrix[nowPos.col - 1][nowPos.row]->sprite &&
            matrix[nowPos.col - 1][nowPos.row]->isVisited == false)
        {
            visit(nowPos.col - 1, nowPos.row);
        }
        
        /* right */
        if (nowPos.col + 1 < MAX_COL &&
            !matrix[nowPos.col + 1][nowPos.row]->sprite &&
            matrix[nowPos.col + 1][nowPos.row]->isVisited == false)
        {
            visit(nowPos.col + 1, nowPos.row);
        }
    }
    
    if (nowPos.col == dest.col && nowPos.row == dest.row)
    {
        /**
         * nowPos 根据predecessor回滚
         * 把整个路线加入到path中
         */
        while (nowPos.predecessor != -1)
        {
            path.enqueue(nowPos);
            nowPos = queue.getByIndex(nowPos.predecessor);
        }
        
        ballGo(start, dest);
    }
    
    resetIsVisited();
}

void GameLayer::ballGo(const pathCell& start, const pathCell& dest)
{
    /**
     * 第一步 path.getByIndex(path.getTail() - 1)
     * 第二步 path.getByIndex(path.getTail() - 2)
     *                 ....
     * 最后一步 path.getByIndex(path.getHead())
     */
    Vector<FiniteTimeAction *> vecAtion;
    
    for (int i = path.getTail() - 1; i >= path.getHead(); i--)
    {
        auto jump = JumpTo::create(0.2f, Vec2(
            PADDING_LR + path.getByIndex(i).col * MCELL_WIDTH + MCELL_WIDTH / 2,
            PADDING_TB + path.getByIndex(i).row * MCELL_HEIGHT + MCELL_HEIGHT / 2
        ), 40, 1);
        vecAtion.pushBack(jump);
    }
    
    FiniteTimeAction *callfunc = CallFunc::create(CC_CALLBACK_0(GameLayer::ballArrive, this, start, dest));
    vecAtion.pushBack(callfunc);
    
    auto seq = Sequence::create(vecAtion);
    
    _funnyBall->runAction(seq);
}

void GameLayer::ballArrive(const pathCell& start, const pathCell& dest)
{
    if (_funnyBall)
    {
        Vec2 pos = Vec2(
            PADDING_LR + dest.col * MCELL_WIDTH + MCELL_WIDTH / 2,
            PADDING_TB + dest.row * MCELL_HEIGHT + MCELL_HEIGHT / 2
        );
        _funnyBall->setPosition(pos);
        _funnyBall->setLocalZOrder(0);
        _funnyBall->unFunny();
    }
    
    matrix[dest.col][dest.row]->sprite = matrix[start.col][start.row]->sprite;
    matrix[dest.col][dest.row]->sprite->setCol(dest.col);
    matrix[dest.col][dest.row]->sprite->setRow(dest.row);
    
    _funnyBall = nullptr;
    matrix[start.col][start.row]->sprite = nullptr;
    
    checkAllDirections(dest.col, dest.row);
    
    setGrade();
    
    removeMatrixCells();
    
    checkGameOver();
    
    checkAddNextBalls();
}

bool GameLayer::isCanAdd(int col, int row)
{
    std::vector<mPointer>::iterator it;
    for (it = removeList.begin(); it != removeList.end(); it++)
    {
        if ((*it)->sprite->getCol() == col &&
            (*it)->sprite->getRow() == row)
        {
            return false;
        }
    }
    
    return true;
}

void GameLayer::checkAddBallToRemove(int col, int row)
{
    if (isCanAdd(col, row))
    {
        removeList.push_back(matrix[col][row]);
    }
}

void GameLayer::recoverRemoveList(int sum, int oldLength)
{
    if (sum < NUM_CAN_REMOVE)
    {
        removeList.erase(removeList.begin() + oldLength, removeList.begin() + removeList.size());
    }
}

void GameLayer::checkHorizontal(int col, int row)
{
    int oldLength = removeList.size();
    int sum = 1;
    color ballColor = matrix[col][row]->sprite->getColor();
    
    checkAddBallToRemove(col, row);
    
    /* left */
    int newCol = col - 1;
    while (newCol >= 0 &&
           matrix[newCol][row]->sprite &&
           matrix[newCol][row]->sprite->getColor() == ballColor)
    {
        checkAddBallToRemove(newCol, row);
        
        sum++;
        newCol--;
    }
    
    /* right */
    newCol = col + 1;
    while (newCol < MAX_COL &&
           matrix[newCol][row]->sprite &&
           matrix[newCol][row]->sprite->getColor() == ballColor)
    {
        checkAddBallToRemove(newCol, row);
        
        sum++;
        newCol++;
    }
    
    recoverRemoveList(sum, oldLength);
}

void GameLayer::checkVertical(int col, int row)
{
    int oldLength = removeList.size();
    int sum = 1;
    color ballColor = matrix[col][row]->sprite->getColor();
    
    checkAddBallToRemove(col, row);
    
    /* down */
    int newRow = row - 1;
    while (newRow >= 0 &&
           matrix[col][newRow]->sprite &&
           matrix[col][newRow]->sprite->getColor() == ballColor)
    {
        checkAddBallToRemove(col, newRow);
        
        sum++;
        newRow--;
    }
    
    /* up */
    newRow = row + 1;
    while (newRow < MAX_ROW &&
           matrix[col][newRow]->sprite &&
           matrix[col][newRow]->sprite->getColor() == ballColor)
    {
        checkAddBallToRemove(col, newRow);
        
        sum++;
        newRow++;
    }
    
    recoverRemoveList(sum, oldLength);
}

void GameLayer::checkAllDirections(int col, int row)
{
    checkHorizontal(col, row);
    checkVertical(col, row);
}

std::string GameLayer::calcGrade()
{
    int size = removeList.size();
    
    for (int i = 0; i < size; i++)
    {
        grade += size;
    }
    
    std::stringstream ss;
    ss << grade;
    return ss.str();
}

void GameLayer::setGrade()
{
    auto gradeLabel = (Label *)this->getChildByTag(GRADE_LABEL_TAG);
    gradeLabel->setString(calcGrade());
}

void GameLayer::removeMatrixCells()
{
    if (removeList.size())
    {
        std::vector<mPointer>::iterator it;
        for (it = removeList.begin(); it != removeList.end(); it++)
        {
            (*it)->sprite->removeFromParent();
            (*it)->sprite = nullptr;
        }
        
        removeList.clear();
    }
}

void GameLayer::resetIsVisited()
{
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            matrix[i][j]->isVisited = false;
        }
    }
}

void GameLayer::showNextBalls()
{
    if (nextList.size())
    {
        std::vector<Ball *>::iterator it;
        for (it = nextList.begin(); it != nextList.end(); it++)
        {
            (*it)->removeFromParent();
        }
        
        nextList.clear();
    }
    
    for (int i = 0; i < NEW_BALLS_COUNT; i++)
    {
        auto nextBall = Ball::create();
        nextBall->setPosition(Vec2(340 + i * nextBall->getContentSize().width, GT.getBaseY() - 120));
        this->addChild(nextBall);
        
        nextList.push_back(nextBall);
    }
}

void GameLayer::addNextBalls()
{
    int col, row;
    std::vector<pos> posList;
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            if (!matrix[i][j]->sprite)
            {
                pos mPos = {i, j};
                posList.push_back(mPos);
            }
        }
    }
    
    for (int i = 0; i < NEW_BALLS_COUNT; i++)
    {
        int n = CCRANDOM_0_1() * posList.size();
        
        col = posList[n].col;
        row = posList[n].row;
        
        matrix[col][row]->sprite = Ball::create(nextList[i]->getColor());
        matrix[col][row]->sprite->setCol(col);
        matrix[col][row]->sprite->setRow(row);
        matrix[col][row]->sprite->setPosition(Vec2(
            PADDING_LR + col * MCELL_WIDTH + MCELL_WIDTH / 2,
            PADDING_TB + row * MCELL_HEIGHT + MCELL_HEIGHT / 2
        ));
        matrix[col][row]->sprite->setOpacity(0);
        this->getChildByTag(BOARD_TAG)->addChild(matrix[col][row]->sprite);
        
        posList.erase(posList.begin() + n);
        
        if (i == NEW_BALLS_COUNT - 1)
        {
            matrix[col][row]->sprite->runAction(Sequence::create(
                FadeIn::create(0.5),
                CallFunc::create(CC_CALLBACK_0(GameLayer::checkAllDirections, this, col, row)),
                CallFunc::create(CC_CALLBACK_0(GameLayer::setGrade, this)),
                CallFunc::create(CC_CALLBACK_0(GameLayer::removeMatrixCells, this)),
                CallFunc::create(CC_CALLBACK_0(GameLayer::checkGameOver, this)),
                NULL
            ));
        }
        else
        {
            matrix[col][row]->sprite->runAction(Sequence::create(
                FadeIn::create(0.5),
                CallFunc::create(CC_CALLBACK_0(GameLayer::checkAllDirections, this, col, row)),
                NULL
            ));
        }
    }
}

bool GameLayer::isGameOver()
{
    int cellCount = 0;
    
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = 0; j < MAX_ROW; j++)
        {
            if (!matrix[i][j]->sprite)
                cellCount++;
            
            if (cellCount >= NEW_BALLS_COUNT)
                return false;
        }
    }
    
    return true;
}

void GameLayer::handleGameOver()
{
    USING_NS_GC;
    
    auto scene = Director::getInstance()->getRunningScene();
    
    if (scene->getChildByTag(OVER_LAYER))   return;
    
    auto layer = OverLayer::create();
    
    scene->addChild(layer, GT.getMaxZOrder(), OVER_LAYER);
}

void GameLayer::checkGameOver()
{
    if (isGameOver())
    {
        handleGameOver();
    }
}

void GameLayer::checkAddNextBalls()
{
    if (!isGameOver())
    {
        addNextBalls();
        
        showNextBalls();
    }
}