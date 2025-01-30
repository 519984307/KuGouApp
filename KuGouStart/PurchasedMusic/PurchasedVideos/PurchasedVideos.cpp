//
// Created by WeiWang on 24-11-15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PurchasedVideos.h" resolved

#include "PurchasedVideos.h"
#include "ui_PurchasedVideos.h"

#include <QFile>

#define GET_CURRENT_DIR (QString(__FILE__).first(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))

PurchasedVideos::PurchasedVideos(QWidget *parent) :
    QWidget(parent), ui(new Ui::PurchasedVideos) {
    ui->setupUi(this);
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/videos.css"));
        if (file.open(QIODevice::ReadOnly)) {
            this->setStyleSheet(file.readAll());
        } else {
            qDebug() << "样式表打开失败QAQ";
            return;
        }
    }
}

PurchasedVideos::~PurchasedVideos() {
    delete ui;
}
