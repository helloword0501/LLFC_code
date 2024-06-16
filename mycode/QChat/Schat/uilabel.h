#ifndef UILABEL_H
#define UILABEL_H

#include<QLabel>
class QString;
class UIlabel :public QLabel
{
public:
    explicit UIlabel(QString name ,QWidget *parent = 0);
    ~UIlabel();
};

#endif // UILABEL_H
