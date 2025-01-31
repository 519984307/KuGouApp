//
// Created by WeiWang on 25-1-31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RecentlyChannelBlock.h" resolved

#include "RecentlyChannelBlock.h"
#include "ui_RecentlyChannelBlock.h"

#include <QFile>
#include <QMouseEvent>

#define GET_CURRENT_DIR (QString(__FILE__).first(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))

RecentlyChannelBlock::RecentlyChannelBlock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RecentlyChannelBlock)
{
    ui->setupUi(this);
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/block.css"));
        if (file.open(QIODevice::ReadOnly)) {
            this->setStyleSheet(file.readAll());
        } else {
            qDebug() << "样式表打开失败QAQ";
            return;
        }
    }
    initUi();
}

RecentlyChannelBlock::~RecentlyChannelBlock() {
    delete ui;
}

void RecentlyChannelBlock::setCoverPix(const QString &pixmapPath) const {
    ui->cover_widget->setBorderImage(pixmapPath,10);
}

void RecentlyChannelBlock::initUi() const {
    //遮罩设置
    auto& mask = ui->cover_widget->getMask();
    mask.setDefaultFillCircleColor(Qt::white);
    mask.setHoverFillCircleColor(QColor(QStringLiteral("#5192FE")));
    mask.setDefaultFillTriangleColor(QColor(QStringLiteral("#666666")));
    mask.setHoverFillTriangleColor(QColor(QStringLiteral("#666666")));
    //扩展MyBlockWidget响应范围
    ui->cover_widget->setExpandRespond(true);
}

void RecentlyChannelBlock::mousePressEvent(QMouseEvent *event) {
    event->ignore();
}

void RecentlyChannelBlock::mouseReleaseEvent(QMouseEvent *event) {
    event->ignore();
}

void RecentlyChannelBlock::mouseDoubleClickEvent(QMouseEvent *event) {
    event->ignore();
}
