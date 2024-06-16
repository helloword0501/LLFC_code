#include "widget.h"
#include"loginwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   Widget w;
   w.show();
   // LogInWidget w ;
   // w.show();
    return a.exec();
}
