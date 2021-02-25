#include "mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "workPublishDialog.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle(tr("person publish center"));
    this->setFixedSize(500,200);
    qreal rate = 1;

    QPushButton *buttonBoxPublish = new QPushButton(this);
    QPushButton *buttonBoxCancel = new QPushButton(this);
    buttonBoxCancel->setText(tr("Back"));
    buttonBoxPublish->setText(tr("publish work"));

    buttonBoxPublish->move(150,100);
    buttonBoxCancel->move(250,100);
    buttonBoxPublish->setMinimumSize(75 * rate, 27 * rate);
    buttonBoxPublish->setMaximumSize(75 * rate, 27 * rate);
    buttonBoxCancel->setMinimumSize(75 * rate, 27 * rate);
    buttonBoxCancel->setMaximumSize(75 * rate, 27 * rate);
    buttonBoxPublish->setStyleSheet("QPushButton{border: none; background-color: #017FFF; color: #FFFFFF; border-radius: 3px;}"
                                                           "QPushButton:hover{background-color: #056BD3;}");

    buttonBoxCancel->setStyleSheet("QPushButton{background-color: #D5D7DB; color: #000000; border-radius: 3px;}"
                                                               "QPushButton:hover{background-color: #C5C6C9;}");
    connect(buttonBoxPublish, &QPushButton::click, this, [=](){
                TemporaryUserPublishDiaog *publishDialog = new TemporaryUserPublishDiaog();
                if(publishDialog)
                    publishDialog->show();
            });
    connect(buttonBoxCancel, &QPushButton::click, this, [=](){
        this->hide();
    });
    TemporaryUserPublishDiaog *publishDialog = new TemporaryUserPublishDiaog();
    if(publishDialog)
        publishDialog->show();
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->setMargin(5);
    buttonLayout->addWidget(buttonBoxPublish);
    buttonLayout->addSpacing(5);
    buttonLayout->addWidget(buttonBoxCancel);

    this->setLayout(buttonLayout);

}

MainWindow::~MainWindow()
{
}

