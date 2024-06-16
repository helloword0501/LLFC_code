#ifndef WIDGET_H
#define WIDGET_H

#include"uilabel.h"
#include"loginwidget.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    UIlabel *_LabelUse;
    LogInWidget *_logInWidget;

private:
    void InitUi();

private slots:
    void openLogInWidget();

};
#endif // WIDGET_H
