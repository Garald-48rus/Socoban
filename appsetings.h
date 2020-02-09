#ifndef APPSETINGS_H
#define APPSETINGS_H

#include <QString>
#include <vector>
#include <QDirIterator>
#include <QGLWidget>


class appSetings
{
public:
    //перечесление текстур игры
    enum class eTexturesID
      {
        Wall = 0
       ,Player
       ,Box
       ,BoxGoal
       ,Goal
       ,End
      };

    appSetings(appSetings &) =               delete ;//запрещаю конструктор копироваия
    appSetings & operator = (appSetings &) = delete ;//запрещаю оператор присваивания

    static appSetings& instanse();//функция возвращающая экземпляр класса

    void load();//функция загрузки сохраненной игры
    void save();//функция сохранения игры

    void setQGLWidget(QGLWidget &);//фенкция задает GL контекст

    unsigned screenWidth() const;//функция возвращающая ширину
    unsigned screenHeight() const;//функция возвращающая высоту

    QString levelsPath();//фунуция возвращпющая адрес файла уровней

    unsigned int textureID(eTexturesID aId); //функция вохвращающая текстуру


    const std::vector<std::pair<int, bool>> &availablesLevels(); //ФУНКЦИЯ ВОЗВРАЩАЮЩИАЯ массив уровней

private:
  void _load_textures();//функция загрузки тексту

private:
    appSetings();
    ~appSetings();



private:
  unsigned mScreenWidth{0};//ширина
  unsigned mScreenHeight{0};//высота

   std::vector<std::pair<int, bool>> mAvailableLevels; //массив уровней(номер уровня и пройден или нет)

   QGLWidget *mpGLContext{nullptr}; //указатель на наш контекст

};


#endif // APPSETINGS_H
