#include <QApplication>

#include "socoban.h"
#include "appsetings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    appSetings::instanse();

    Socoban s;

    s.show();


    return a.exec();
}
