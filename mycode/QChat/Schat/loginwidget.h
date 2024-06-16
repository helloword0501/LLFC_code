#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include"uilabel.h"

class LogInWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogInWidget(QWidget *parent = nullptr);

signals:
private:
    void InitUi();
};

#endif // LOGINWIDGET_H
