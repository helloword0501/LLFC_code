#include "uilabel.h"

UIlabel::UIlabel(QString name ,QWidget *parent ):QLabel(parent)
{
    this->setText(name);
    this->setAlignment(Qt::AlignCenter);
    this->setMaximumHeight(25);
    this->setMinimumHeight(25);
    QFont fomart ;
    fomart.setPointSize(15);
    this->setFont(fomart);

}

UIlabel::~UIlabel()
{

}
