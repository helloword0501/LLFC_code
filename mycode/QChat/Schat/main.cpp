#include "widget.h"
#include"loginwidget.h"
#include <QApplication>
#include<QFile>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/style/stylesheet.qss");
    if( qss.open(QFile::ReadOnly))
    {
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("Open failed");
    }

    Widget w;
    w.show();
    return a.exec();
}
