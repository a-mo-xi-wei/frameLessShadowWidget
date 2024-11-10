#include "MyShadowWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyShadowWidget w;
    w.show();
    return a.exec();
}
