#include "loginwidget.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include <QLineEdit>
#include<QPushButton>
#include<QSpacerItem>
#include <QSizePolicy>
#include<QDebug>
#include <QShowEvent>
#include"Global.h"

LogInWidget::LogInWidget(QWidget *parent) : QWidget(parent)
{
    this->setMaximumSize(500,700);
    this->setMinimumSize(500,700);
    // 对于窗口
    this->setStyleSheet("background-color: white;");
    InitUi();
}

LogInWidget::~LogInWidget()
{
    qDebug()<<"子窗口析构";
}

void LogInWidget::InitUi()
{

    QWidget *topWidget = new QWidget();
    _TopWidgetLabel = new QLabel("测试",topWidget);
    QVBoxLayout *MianLayout = new QVBoxLayout(this);
    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    QHBoxLayout *Hlayout3 = new QHBoxLayout();
    QHBoxLayout *Hlayout4 = new QHBoxLayout();
    QHBoxLayout *Hlayout5 = new QHBoxLayout();
    QHBoxLayout *Hlayout6 = new QHBoxLayout();

    QLabel *uerLbael = new QLabel("用户");
    QLabel *mailboxLbael= new QLabel("邮箱");
    QLabel *passWorLbael= new QLabel("密码");
    QLabel *verifyLbael= new QLabel("确认");
    QLabel *VcodeuerLbael= new QLabel("验证码");

    QLineEdit *uerLLine = new QLineEdit();
    QLineEdit *mailboxLine= new QLineEdit();
    QLineEdit *passWorLine= new QLineEdit();
    QLineEdit *verifyLine= new QLineEdit();
    QLineEdit *VcodeuerLine= new QLineEdit();
    //模式为密码模式
    passWorLine->setEchoMode(QLineEdit::Password);
    verifyLine->setEchoMode(QLineEdit::Password);

    QPushButton *getButton = new QPushButton("获取");
    QPushButton *verifyButton = new QPushButton("确认");
    QPushButton *canceButton = new QPushButton("取消");

    connect(verifyButton ,&QPushButton::clicked ,this ,&LogInWidget::codeButtonClick);
    //
    _TopWidgetLabel->setProperty("state","normal");
    repolish(_TopWidgetLabel);

    _TopWidgetLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _TopWidgetLabel->setStyleSheet("background-color:rgb(191,191,191);border-radius:5px;");
    MianLayout->addWidget(topWidget);
    // 添加顶部弹簧
    QSpacerItem* topSpacer = new QSpacerItem(100, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    MianLayout->addSpacerItem(topSpacer);
    Hlayout1->addWidget(uerLbael);
    Hlayout1->addWidget(uerLLine);
    MianLayout->addLayout(Hlayout1);

    Hlayout2->addWidget(mailboxLbael);
    Hlayout2->addWidget(mailboxLine);
    MianLayout->addLayout(Hlayout2);

    Hlayout3->addWidget(passWorLbael);
    Hlayout3->addWidget(passWorLine);
    MianLayout->addLayout(Hlayout3);

    Hlayout4->addWidget(verifyLbael);
    Hlayout4->addWidget(verifyLine);
    MianLayout->addLayout(Hlayout4);

    Hlayout5->addWidget(VcodeuerLbael);
    Hlayout5->addWidget(VcodeuerLine);
    Hlayout5->addWidget(getButton);
    MianLayout->addLayout(Hlayout5);
    // 添加底部弹簧
    QSpacerItem* bottomSpacer = new QSpacerItem(100, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    MianLayout->addSpacerItem(bottomSpacer);

    Hlayout6->addWidget(verifyButton);
    Hlayout6->addWidget(canceButton);
    MianLayout->addLayout(Hlayout6);
}

void LogInWidget::ShowTips(QString tips)
{
    _TopWidgetLabel->setProperty("state","err");
    _TopWidgetLabel->setText(tips);
    repolish(_TopWidgetLabel);
}

void LogInWidget::codeButtonClick()
{
    qDebug()<<"this";
    ShowTips("错误");
}

