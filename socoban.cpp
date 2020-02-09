#include "socoban.h"

//------------------- ADDITIONAL FUNCTIONS -------------------------------------
//------------------------------------------------------------------------------
Socoban::eMenu operator++(Socoban::eMenu &aMenu)//перегрузка опнратора ++ для перемещения по меню вверх
{
  aMenu = Socoban::eMenu(int(aMenu) + 1);

  if(aMenu == Socoban::eMenu::END )
  {
     aMenu = Socoban::eMenu::PLAY;
     return aMenu;
  }
  return aMenu;
}
//------------------------------------------------------------------------------
Socoban::eMenu operator--(Socoban::eMenu &aMenu)//перегрузка оператора -- вниз
{
  aMenu = Socoban::eMenu(int(aMenu) - 1);

  if(aMenu == Socoban::eMenu::START )
  {
     aMenu = Socoban::eMenu::EXIT;
     return aMenu;
  }
  return aMenu;
}

//------------------------------------------------------------------------------
int menuStateToInt(const Socoban::eMenu &aMenu)//ковертирую пункты меню в int
{
  switch(aMenu)
  {
    case Socoban::eMenu::START:       return (int)Socoban::eMenu::START;
    case Socoban::eMenu::END:         return (int)Socoban::eMenu::END;
    case Socoban::eMenu::SELECT_LEVEL:return (int)Socoban::eMenu::SELECT_LEVEL;
    case Socoban::eMenu::PLAY:        return (int)Socoban::eMenu::PLAY;
    case Socoban::eMenu::PLAYER_STAT: return (int)Socoban::eMenu::PLAYER_STAT;
    case Socoban::eMenu::EXIT:        return (int)Socoban::eMenu::EXIT;
  }
  return -1;
}
//------------------------------------------------------------------------------
Socoban::eState menuStateToGameState(const Socoban::eMenu &aMenu)//функция перехода из основеоно меню в игровое меню
{
  switch(aMenu)
  {
    case Socoban::eMenu::START:
    case Socoban::eMenu::END:         return Socoban::eState::MENU;

    case Socoban::eMenu::SELECT_LEVEL:return Socoban::eState::SELECT_LEVEL;
    case Socoban::eMenu::PLAY:        return Socoban::eState::PLAY;
    case Socoban::eMenu::PLAYER_STAT: return Socoban::eState::PLAYER_STAT;
    case Socoban::eMenu::EXIT:        return Socoban::eState::EXIT;
  }
  return Socoban::eState::MENU;
}


Socoban::Socoban()
       {
    //фиксированный размер окна нелбзя изменить
     setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
     //размер окна
     setFixedSize(800,600);
     //каждые 2000 млс таймер подает сигнал
    mTimer.start(33);
    //соединяю сигнал timeout cо слото
    connect(&mTimer,SIGNAL(timeout()), this, SLOT(repaint()));
      /*передаю текущий объект точнее срез QGLWidget иницилизация меню*/
     appSetings::instanse().setQGLWidget(*this);
       mvMenu.push_back({eMenu::PLAY,        "Играть"});
       mvMenu.push_back({eMenu::SELECT_LEVEL,"Выбор уровня"});
       mvMenu.push_back({eMenu::PLAYER_STAT, "Статистика"});
       mvMenu.push_back({eMenu::EXIT,        "Выход"});



}
//---------------------------------------------------//перекрываю функцию иницилицации окно(2D<3D..)
void Socoban::initializeGL()
{
     static  auto w = appSetings::instanse().screenWidth();
     static auto h = appSetings::instanse().screenHeight();

         //самый минимум 2D режим
         //размер окна
         glOrtho(0, w, h, 0, 0, 1);

         glDisable(GL_DEPTH_TEST);
          glEnable(GL_BLEND);
          glEnable(GL_LINE_SMOOTH);
          glEnable(GL_POINT_SMOOTH);
          glEnable(GL_SMOOTH);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          //важно включить текстуру
          glEnable(GL_TEXTURE_2D);
          //загружаею файл уровней
          appSetings::instanse().load();
}
//----------------------------------------------------------//перекрываю функцию изменения размеров окна(пересчитывает размеры прапоции если окно меняет размер)
void Socoban::resizeGL(int aW, int aH)
{
    static  auto w = appSetings::instanse().screenWidth();
    static auto h = appSetings::instanse().screenHeight();

     glLoadIdentity();
     glViewport(0, 0, (GLint)aW, (GLint)aH);
     //если размер окна изменился вызываю opgl функцию она пересчитывает пропорции
     glOrtho(0, w, h, 0, 0, 1);

}
//--------------------------------------------------------------//перекрываю функцию прорисовки окна
void Socoban::paintGL()
{
           //очищаю экран
          glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
          //цвет окна
          qglClearColor(Qt::darkCyan);


          _proccesing();

          _draw();
}
//------------------------------------------------------------------//перекрываю функцию обработки клавиатуры
void Socoban::keyReleaseEvent(QKeyEvent * apKeyEvent)
{
    //выбор пункта меню
    switch (mState)
    {
        case eState::MENU:
        {
        _key_released_menu(apKeyEvent->key());
          break;
        }
        case eState::SELECT_LEVEL:
        {
        _key_released_menu_select_level(apKeyEvent->key());
          break;
        }
        case eState::PLAYER_STAT:
        {
        _key_released_player_stat(apKeyEvent->key());
          break;
        }
        case eState::PLAY:
        {
        _key_released_play(apKeyEvent->key());
          break;
        }
        case eState::EXIT:
        {

          close();
          break;
        }
      }

}
//------------------------------------------------------------------//функция процессов вычислениы считиванияюю

void Socoban::_proccesing()
{
    //выбор пункта меню
    switch (mState)
      {
        case eState::MENU:
        {
          break;
        }
        case eState::SELECT_LEVEL:
        {
          break;
        }
        case eState::PLAYER_STAT:
        {
          break;
        }
        case eState::PLAY:
        {
          break;
        }
        case eState::EXIT:
        {
          close();
          break;
        }
      }
}
//------------------------------------------------------ //отрисовка действий
void Socoban::_draw()
{
    //выбор пункта меню и его отрисовка
    switch (mState)
      {
        case eState::MENU:
        {
        _draw_menu();
          break;
        }
        case eState::SELECT_LEVEL:
        {
        _draw_menu_select_level();
          break;
        }
        case eState::PLAYER_STAT:
        {
        _draw_player_stat();
          break;
        }
        case eState::PLAY:
        {
        _draw_play();
          break;
        }
        case eState::EXIT:
        {

          close();
          break;
        }
      }

}
//----------------------------------------------------------------------------//функция отрисовки пункта меню

void Socoban::_draw_menu()
{
    // ТОЧКА начала отрисовки меню
    static auto app_w = appSetings::instanse().screenWidth() / 2.f;
     static auto app_h = appSetings::instanse().screenHeight() / 3.f;
       //шрифт если пункт меню не выбран
     static auto font          = QFont("Sans", 25);
     //шрифт если пункт меню  выбран
     static auto font_selected = QFont("Sans", 30);
     //для выбраного шрифта устанавливаю жиность
     font_selected.setBold(true);
    //сдвигаю точку отрисовки по оси х
     auto x   = app_w - 100;
     auto y   = app_h;
     //смещение по оси у
     auto dy  = 55.f;
     //переменная хранящая калличество элементов меню
     int  end = mvMenu.size();
     //пробегаем по меню
     for(int i = 0; i < end; ++i)
     {
         //если пункт меню совпадает с выбраным
       if(i == menuStateToInt(mCurrentMenu))
       {
           //подсвечиваеи его
         qglColor(Qt::red);
         //стандатная функция отрисовки текста.....  меняю шрифт
         renderText(x, y, mvMenu[i].second.c_str(), font_selected);
       }
       else
       {
         qglColor(Qt::white);
         renderText(x, y, mvMenu[i].second.c_str(), font);
       }
       //после прохода смещаю по оси у
       y += dy;
     }
}
//---------------------------------------------------------------------//функция отрисовки пункта выбор уровня
void Socoban::_draw_menu_select_level()
{
     auto &app = appSetings::instanse();
     static auto app_w = app.screenWidth() / 2.f;
     static auto app_h = app.screenHeight() / 3.f;
     //получаю уровни
     auto &levels = app.availablesLevels();
     //переменная кол уровней
     int  l_count = (int)levels.size();
     //если уровней нет
     if(levels.empty())
       return;

     //шрифты для выброного уровня и нет
     static auto font          = QFont("Comic Sans MS", 15);
     static auto font_selected = QFont("Comic Sans MS", 20);
     font_selected.setBold(true);

     int tmp = (mSelectLevelIndex - 6);
     int start = tmp < 0 ? 0 : tmp;

     //типо скролл не более 6 елементов
     tmp = (start + 6);
     int end = (tmp < l_count) ? tmp : l_count - 1;

     //переменные для отрисовки примерно по соредине экрана
     auto x   = app_w - 100;
     auto y   = app_h;
     auto dy  = 25.f;

     for(int i = start; i <= end; ++i)
     {
         //декомпозиция с++ 17
       const auto &[lvl, isLock] = levels[i];
       //формирую строку (уровень..номер)
       QString item_str = "Уровень " + QString::number(lvl);
      //если номер уровня выбран его подсвечиваю....
       QFont  &rf = (i == mSelectLevelIndex) ? font_selected : font;

       Qt::GlobalColor color = Qt::gray;

       if(i == mSelectLevelIndex)
       {
         if(isLock == true)
           color = Qt::red;
       }
       else
       {
         if(isLock == true)
           color = Qt::white;
       }

       qglColor(color);
       renderText(x, y, item_str, rf);

       y += dy;
     }

}
//---------------------------------------------------------------//функция отрисовки пункта статистика игрока
void Socoban::_draw_player_stat()
{

}
//-------------------------------------------------------------------------//функция отрисовки пункта играть
void Socoban::_draw_play()
{
  mDrawer.draw(mLevel, *this);
}
//----------------------------------------------------------------------------------//функция обработко клавиш когда мы находимися в меню
void Socoban::_key_released_menu(int aKey)
{
    switch (aKey) {

    case Qt::Key_Up :
    {
      --mCurrentMenu;
        break;
    }
    case Qt::Key_Down:
    {
        ++mCurrentMenu;
        break;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter:
    {
        //переводим наше стартовое положение в меню в текущее
       mState = menuStateToGameState(mCurrentMenu);
        break;
    }

    }
}
//----------------------------------------------------------------------//функция обработко клавиш когда мы находимися в пункте выборе уровня
void Socoban::_key_released_menu_select_level(int aKey)
{
    const auto &levels = appSetings::instanse().availablesLevels();
    //переменная кол уровней
     int levels_count = (int)levels.size();
    switch(aKey)
      {
        case Qt::Key_Up:
        {
        --mSelectLevelIndex;
         if(mSelectLevelIndex < 0)
           mSelectLevelIndex = 0;
          break;
        }
        case Qt::Key_Down:
        {
        ++mSelectLevelIndex;
         if(mSelectLevelIndex >= levels_count)
           mSelectLevelIndex = levels_count - 1;
          break;
        }
        case Qt::Key_Enter:
        case Qt::Key_Return:
        {
        if(mSelectLevelIndex >= 0)
             {
               if(mSelectLevelIndex >= levels_count)
                 break;

               const auto & [lvl, isLock] = levels[mSelectLevelIndex];
               if(isLock)
               {
                   mLevel.load(lvl);
                   mState = eState::PLAY;
               }
             }
          break;
        }
        case Qt::Key_Escape:
        {
          mState = eState::MENU;
          break;
        }
      }
}
//---------------------------------------------------------------------
void Socoban::_key_released_player_stat(int aKey)//функция обработко клавиш когда мы находимися в пункте статистике игрока
{
    switch(aKey)
     {
       case Qt::Key_Escape:
       {
         mState = eState::MENU;
         break;
       }
     }
}
//----------------------------------------------------------------------
void Socoban::_key_released_play(int aKey) //функция обработко клавиш когда мы находимися в пункте играть
{
    switch(aKey)
      {
        case Qt::Key_Up:
        {
        mLevel.player_up();
          break;
        }
        case Qt::Key_Down:
        {
        mLevel.player_down();
          break;
        }
        case Qt::Key_Left:
        {
        mLevel.player_left();
          break;
        }
        case Qt::Key_Right:
        {
        mLevel.player_rigth();
          break;
        }
        case Qt::Key_Escape:
        {
          mState = eState::MENU;
          break;
        }
        case Qt::Key_R:
        {
        mLevel.reset();
          break;
        }
      }
}
//--------------------------------------------------------------------------------
