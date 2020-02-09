#include "drawer.h"
#include "appsetings.h"


Drawer::Drawer()
{

}
//--------------------------------------------
 void Drawer::draw(const Level& aLevel, QGLWidget & aGLWidget)//функция отрисовки уровня
 {
     if(!aLevel.mIsLoad)
         return;

       _draw_grid(aLevel, aGLWidget);
       _draw_objects(aLevel, aGLWidget);
       _draw_statistic(aLevel, aGLWidget);

 }
//-----------------------------------------
 void Drawer::_draw_grid(const Level& aLevel, QGLWidget & aGLWidget)//функция отрисовки сетки
  {
     static auto sw =  appSetings::instanse().screenHeight() - 100;

       auto &lines   = aLevel.mLines;
       auto &columns = aLevel.mColumns;

       float fw    = (float)sw / (float)columns;  // field width
       float map_w = sw;
       float map_h = fw*lines;

       float x{(appSetings::instanse().screenWidth() - sw)/ 2.f};
       float y{100.f};

         aGLWidget.qglColor(Qt::darkGray);

         glBegin(GL_LINES);

         for(int r = 0; r <= lines; ++r)
         {
           glVertex2i(x,         y + fw*r);
           glVertex2i(x + map_w, y + fw*r);
         }

         for(int c = 0.f; c <= columns; ++c)
         {
           glVertex2i(x + fw*c, y );
           glVertex2i(x + fw*c, y + map_h);
         }

         glEnd();
  }
//----------------------------------------------------
 void Drawer::_draw_objects(const Level& aLevel, QGLWidget & aGLWidget)//функция отрисовки объектов
  {
     auto &app = appSetings::instanse(); //создаю ссылку на объект appSetings

      static auto sw = app.screenHeight() - 100;

      auto &lines   = aLevel.mLines;
      auto &columns = aLevel.mColumns;

      float fw    = (float)sw / (float)columns;  // field width

      float x{(appSetings::instanse().screenWidth() - sw)/ 2.f};

      float y{100.f};

      auto tbox      = app.textureID(appSetings::eTexturesID::Box);
      auto tbox_goal = app.textureID(appSetings::eTexturesID::BoxGoal);
      auto tplayer   = app.textureID(appSetings::eTexturesID::Player);
      auto twall     = app.textureID(appSetings::eTexturesID::Wall);
      auto tgoal     = app.textureID(appSetings::eTexturesID::Goal);

      const auto &map = aLevel.mRoom;

     glEnable(GL_TEXTURE_2D);

      aGLWidget.qglColor(Qt::white);

      for(int l = 0; l < lines; ++l)
        for(int c = 0; c < columns; ++c)
        {
          unsigned int textureID = 0;
          switch(map[l*columns + c])
          {
            case Level::eField::BOX:
            {
              textureID = tbox;
              break;
            }
            case Level::eField::BOX_ON_GOAL:
            {
              textureID = tbox_goal;
              break;
            }
            case Level::eField::PLAYER:
            case Level::eField::PLAYER_ON_GOAL:
            {
              textureID = tplayer;
              break;
            }
            case Level::eField::WALL:
            {
              textureID = twall;
              break;
            }
            case Level::eField::GOAL:
            {
              textureID = tgoal;
              break;
            }
            case Level::eField::EMPTY:
            {
              break;
            }
          }

          if(textureID != 0)
            aGLWidget.drawTexture(QRectF{x + c*fw, y + l*fw, fw, fw}, textureID);
        }

      glDisable(GL_TEXTURE_2D);
  }
//--------------------------------------------------------
 void Drawer::_draw_statistic(const Level& aLevel, QGLWidget &aGLWidget) //функция отрисовки статистики
  {
     static auto font = QFont("Comic Sans MS", 15);
       aGLWidget.qglColor(Qt::blue);

       QString str;

       str = "Steps        : ";
       str += QString::number(aLevel.steps_count());
       aGLWidget.renderText(15, 20, str, font);

       str = "Boxes on goal: ";
       str += QString::number(aLevel.boxes_on_goal());;
       str += "/";
       str += QString::number(aLevel.goals());
       aGLWidget.renderText(15, 40, str, font);
  }
//--------------------------------------------------------
