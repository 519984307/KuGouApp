//
// Created by WeiWang on 24-11-15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_PurchasedAlbums.h" resolved

#include "PurchasedAlbums.h"
#include "ui_PurchasedAlbums.h"

#include <QFile>

#define GET_CURRENT_DIR (QString(__FILE__).first(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))

PurchasedAlbums::PurchasedAlbums(QWidget *parent) :
    QWidget(parent), ui(new Ui::PurchasedAlbums) {
    ui->setupUi(this);
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/albums.css"));
        if (file.open(QIODevice::ReadOnly)) {
            this->setStyleSheet(file.readAll());
        } else {
            qDebug() << "样式表打开失败QAQ";
            return;
        }
    }
}

PurchasedAlbums::~PurchasedAlbums() {
    delete ui;
}
