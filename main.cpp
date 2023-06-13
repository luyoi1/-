#include "StudentSystem.h"
#include"QtMySQLClass.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StudentSystem w;
    QtMySQLClass* sqlPtr = QtMySQLClass::GetDataBase(
        "localhost","StudentSystem","root","1314520XX",3306);
    w.show();
    return a.exec();
}
