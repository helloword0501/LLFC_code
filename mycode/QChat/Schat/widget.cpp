#include "widget.h"
#include "ui_widget.h"
#include<QScreen>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QLineEdit>
#include<QPushButton>
#include<QSpacerItem>
#include <QSizePolicy>
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(500,700);
    this->setMinimumSize(500,700);
    InitUi();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitUi()
{
    _LabelUse = new UIlabel("用户");
    UIlabel *labelPassword = new UIlabel("密码");
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    QHBoxLayout *Hlayout3 = new QHBoxLayout();
    QHBoxLayout *Hlayout4 = new QHBoxLayout();
    QHBoxLayout *Hlayout5 = new QHBoxLayout();
    QLineEdit *lineUser = new QLineEdit();
    QLineEdit *linePWord = new QLineEdit();
    // 添加顶部弹簧
    QSpacerItem* topSpacer = new QSpacerItem(100, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

     vLayout->addSpacerItem(topSpacer);
    Hlayout1->addWidget(_LabelUse);
    Hlayout1->addWidget(lineUser);
    vLayout->addLayout(Hlayout1);

    Hlayout2->addWidget(labelPassword);
    Hlayout2->addWidget(linePWord);
    vLayout->addLayout(Hlayout2);

    Hlayout5->setAlignment(Qt::AlignRight);
    QPushButton *fogetButton = new QPushButton("忘记密码");
    Hlayout5->addWidget(fogetButton);
    vLayout->addLayout(Hlayout5);
    // 添加底部弹簧
    QSpacerItem* bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Fixed);
    vLayout->addSpacerItem(bottomSpacer);

    Hlayout3->setAlignment(Qt::AlignCenter);
    Hlayout4->setAlignment(Qt::AlignCenter);
    QPushButton *loginButton = new QPushButton("登录");
    QPushButton *SignInButton = new QPushButton("注册");
    connect(SignInButton ,&QPushButton::clicked ,this ,&Widget::openLogInWidget);
    Hlayout3->addWidget(loginButton);
    Hlayout4->addWidget(SignInButton);
    vLayout->addLayout(Hlayout3);
    vLayout->addLayout(Hlayout4);
}

void Widget::openLogInWidget()
{
    qDebug() <<"123";
    LogInWidget *logInWidget1 = new LogInWidget(this);
    logInWidget1->show();
}

