#include "loginwidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QLineEdit>
#include<QPushButton>
#include<QSpacerItem>
#include <QSizePolicy>

LogInWidget::LogInWidget(QWidget *parent) : QWidget(parent)
{
    this->setMaximumSize(500,700);
    this->setMinimumSize(500,700);
    InitUi();
}

void LogInWidget::InitUi()
{
    QVBoxLayout *MianLayout = new QVBoxLayout(this);
    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    QHBoxLayout *Hlayout3 = new QHBoxLayout();
    QHBoxLayout *Hlayout4 = new QHBoxLayout();
    QHBoxLayout *Hlayout5 = new QHBoxLayout();

    QLabel uerLbael("用户");
    QLabel mailboxLbael("邮箱");
    QLabel passWorLbael("密码");
    QLabel verifyLbael("确认");
    QLabel VcodeuerLbael("验证码");

    QLineEdit uerLLine("用户");
    QLineEdit mailboxLine("邮箱");
    QLineEdit passWorLine("密码");
    QLineEdit verifyLine("确认");
    QLineEdit VcodeuerLine("验证码");
    // 添加顶部弹簧
    QSpacerItem* topSpacer = new QSpacerItem(100, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    MianLayout->addSpacerItem(topSpacer);
    Hlayout1->addWidget(&uerLbael);
    Hlayout1->addWidget(&uerLLine);
    MianLayout->addLayout(Hlayout1);

    Hlayout2->addWidget(&mailboxLbael);
    Hlayout2->addWidget(&mailboxLine);
    MianLayout->addLayout(Hlayout2);

    Hlayout3->addWidget(&passWorLbael);
    Hlayout3->addWidget(&passWorLine);
    MianLayout->addLayout(Hlayout3);

    Hlayout4->addWidget(&verifyLbael);
    Hlayout4->addWidget(&verifyLine);
    MianLayout->addLayout(Hlayout4);

    Hlayout5->addWidget(&VcodeuerLbael);
    Hlayout5->addWidget(&VcodeuerLine);
    MianLayout->addLayout(Hlayout5);
    // 添加底部弹簧
    QSpacerItem* bottomSpacer = new QSpacerItem(100, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    MianLayout->addSpacerItem(bottomSpacer);
}
