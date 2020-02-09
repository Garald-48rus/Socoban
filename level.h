#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>
#include <QFile>
#include <QTextStream>
#include "appsetings.h"



// http://www.sokobano.de/wiki/index.php?title=Level_format
// http://www.sourcecode.se/sokoban/levels
/*
Wall                  #   0x23
Player                @   0x40
Player on goal square +   0x2b
Box                   $   0x24
Box on goal square    *   0x2a
Goal square           .   0x2e
Floor            (Space)  0x20
*/

class Level
{
    friend class Drawer;

  //класс перечеслений игровых елементов
    enum class eField
     {
       EMPTY
      ,WALL
      ,PLAYER
      ,PLAYER_ON_GOAL
      ,BOX
      ,BOX_ON_GOAL
      ,GOAL
     };


public:
    Level();

      void reset();
      void load(int);//загрузка уровня
      void load(std::string);//загрузка последенго уровня продолжение игры
      bool isComplete();//проверка пройден ли уровень
      bool isLoad();//проверка загрузился лт уровень

     //функции упрвления игроком
      void player_up();
      void player_down();
      void player_left();
      void player_rigth();

      int steps_count() const;//функция возращающая кол ходов
      int goals() const; //функция возращающая кол ящиков
      int boxes_on_goal() const;//функция возращающая кол ящиков на месте
private:
      void _move(int, int); //функция смещения по осям

private:
       int mLevel{-1};//текущий уровень
       int mColumns{0};//кол колонок
       int mLines{0};//кол линий в уровне

       int mSteps{0};//кол зделаных ходов
       int mGoalCount{0};//кол ящиков
       int mBoxesOnGoal{0};//кол ящиков на метках

       bool mIsComplete{false};//флаг пройден ли уровень
       bool mIsLoad{false};//флаг загрузился ли уровень

       std::pair<int,int>  mPlayerPos;//хранение позиции игрока
       std::vector<eField> mRoom;//вектор хренения элементов уровня

};

#endif // LEVEL_H
