#ifndef SOCOBAN_H
#define SOCOBAN_H

#include <QGLWidget>
#include <QKeyEvent>
#include <appsetings.h>
#include <QTimer>
#include "drawer.h"

class Socoban : public QGLWidget
{
public:
    //перечисление состояния игры
    enum class eState
     {
       MENU //меню
      ,SELECT_LEVEL //выбор уровня
      ,PLAYER_STAT //статистика игрока
      ,PLAY //играть
      ,EXIT //выход
     };
    //перечесления меню на каком пункте мы нажали энтер
     enum class eMenu
     {
       START = -1
      ,PLAY //0
      ,SELECT_LEVEL //1
      ,PLAYER_STAT //2
      ,EXIT //3
      ,END //4
     };


public:
    Socoban();
    void initializeGL()                    override;//перекрываю функцию иницилицации окно(2D<3D..)
    void resizeGL(int w, int h)            override;//перекрываю функцию изменения размеров окна(пересчитывает размеры прапоции если окно меняет размер)
    void paintGL()                         override;//перекрываю функцию прорисовки окна
    void keyReleaseEvent(QKeyEvent *)      override;//перекрываю функцию обработки клавиатуры


private:
  void _proccesing();//функция процессов вычислениы считиванияюю
  void _draw(); //отрисовка действий

  void _draw_menu();//функция отрисовки пункта меню
  void _draw_menu_select_level();//функция отрисовки пункта выбор уровня
  void _draw_player_stat();//функция отрисовки пункта статистика игрока
  void _draw_play();//функция отрисовки пункта играть


   void _key_released_menu(int);//функция обработко клавиш когда мы находимися в меню
   void _key_released_menu_select_level(int);//функция обработко клавиш когда мы находимися в пункте выборе уровня
   void _key_released_player_stat(int);//функция обработко клавиш когда мы находимися в пункте статистике игрока
   void _key_released_play(int); //функция обработко клавиш когда мы находимися в пункте играть

private:
   int mSelectLevelIndex{0};//переменная выбора уровня

   Level mLevel; //объект класса  уровней

   Drawer mDrawer;  //объект класса отрисовки

  eState  mState{eState::MENU};//стартовое состояние мнгю
  eMenu   mCurrentMenu{eMenu::PLAY};;//текущее сосиояние меню

  QTimer mTimer;//объект таймера

  std::vector<std::pair<eMenu, std::string>> mvMenu;//вектор пар, пукт меню и что надо нарисовать
};


#endif // SOCOBAN_H
