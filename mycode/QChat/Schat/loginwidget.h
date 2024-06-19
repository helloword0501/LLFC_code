#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include"uilabel.h"

class LogInWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogInWidget(QWidget *parent = nullptr);
    ~LogInWidget();
signals:
private:
    void InitUi();
    void ShowTips(QString tips);
public slots:
    void codeButtonClick();
private:
    QLabel *_TopWidgetLabel;

};

#endif // LOGINWIDGET_H
