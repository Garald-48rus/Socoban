#ifndef DRAWER_H
#define DRAWER_H
#include "level.h"
#include <QGLWidget>



class Drawer
{
public:
    Drawer();

    Drawer(Drawer &) = delete;
    Drawer(Drawer &&) = delete;

    void draw(const Level&, QGLWidget &);//функция отрисовки уровня

private:
      void _draw_grid(const Level&, QGLWidget &);//функция отрисовки сетки
      void _draw_objects(const Level&, QGLWidget &);//функция отрисовки объектов
      void _draw_statistic(const Level&, QGLWidget &);//функция отрисовки статистики

    private:
      bool mTextureIsLoad{false};//флаг загрузки текстуры
};

#endif // DRAWER_H
