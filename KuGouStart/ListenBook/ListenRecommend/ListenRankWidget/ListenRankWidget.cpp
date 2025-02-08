//
// Created by WeiWang on 25-2-8.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ListenRankWidget.h" resolved

#include "ListenRankWidget.h"

#include <QHBoxLayout>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#define GET_CURRENT_DIR (QString(__FILE__).left(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))

ListenRankWidget::ListenRankWidget(QWidget *parent)
    : QWidget(parent)
    , rank_free(new RankPartWidget(this))
    , rank_skyrocket(new RankPartWidget(this))
    , rank_sell(new RankPartWidget(this))
    , rank_new(new RankPartWidget(this))
{
    initUi();
}

void ListenRankWidget::initUi() {
    const auto lay = new QHBoxLayout(this);
    lay->setContentsMargins(10, 0, 10, 10);
    lay->addWidget(this->rank_free);
    lay->addWidget(this->rank_skyrocket);
    lay->addWidget(this->rank_sell);
    lay->addWidget(this->rank_new);
    //初始隐藏新品榜
    rank_new->hide();
    //设置标题
    this->rank_free->setTitle(" 免费榜 ›");
    this->rank_skyrocket->setTitle(" 飙升榜 ›");
    this->rank_sell->setTitle(" 热销榜 ›");
    this->rank_new->setTitle(" 新品榜 ›");
    //初始化
    initRankFree();
    initRankSkyrocket();
    initRankSell();
    initRankNew();

}

void ListenRankWidget::initRankFree() {
    //解析json文件
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/../jsonFiles/rank-free.json"));
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open file for reading rank-free.json";
            return;
        }
        const auto obj = QJsonDocument::fromJson(file.readAll());
        auto arr = obj.array();
        const QString pathArr[] = {
            ":/ListenBook/Res/listenbook/first.svg",
            ":/ListenBook/Res/listenbook/second.svg",
            ":/ListenBook/Res/listenbook/third.svg"
        };
        for (int i = 0 ; i < 5 ; ++i) {
            QString desc = arr[i].toObject().value("desc").toString();
            this->rank_free->getRankListWidget(i)->setDescText(desc);
            this->rank_free->getRankListWidget(i)->setCoverImg(
                QString(":/ListCover/Res/listcover/music-list-cover%1.jpg").arg(20+i));
            if (i < 3)
                this->rank_free->getRankListWidget(i)->setRankMedal(pathArr[i]);
            else
                this->rank_free->getRankListWidget(i)->setRankNumber(QString("%1").arg(i+1));
        }
        file.close();
    }
}

void ListenRankWidget::initRankSkyrocket() {
    //解析json文件
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/../jsonFiles/rank-skyrocket.json"));
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open file for reading rank-skyrocket.json";
            return;
        }
        const auto obj = QJsonDocument::fromJson(file.readAll());
        auto arr = obj.array();
        const QString pathArr[] = {
            ":/ListenBook/Res/listenbook/first.svg",
            ":/ListenBook/Res/listenbook/second.svg",
            ":/ListenBook/Res/listenbook/third.svg"
        };
        for (int i = 0 ; i < 5 ; ++i) {
            QString desc = arr[i].toObject().value("desc").toString();
            this->rank_skyrocket->getRankListWidget(i)->setDescText(desc);
            this->rank_skyrocket->getRankListWidget(i)->setCoverImg(
                QString(":/ListCover/Res/listcover/music-list-cover%1.jpg").arg(30+i));
            if (i < 3)
                this->rank_skyrocket->getRankListWidget(i)->setRankMedal(pathArr[i]);
            else
                this->rank_skyrocket->getRankListWidget(i)->setRankNumber(QString("%1").arg(i+1));
        }
        file.close();
    }
}

void ListenRankWidget::initRankSell() {
    //解析json文件
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/../jsonFiles/rank-sell.json"));
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open file for reading rank-sell.json";
            return;
        }
        const auto obj = QJsonDocument::fromJson(file.readAll());
        auto arr = obj.array();
        const QString pathArr[] = {
            ":/ListenBook/Res/listenbook/first.svg",
            ":/ListenBook/Res/listenbook/second.svg",
            ":/ListenBook/Res/listenbook/third.svg"
        };
        for (int i = 0 ; i < 5 ; ++i) {
            QString desc = arr[i].toObject().value("desc").toString();
            this->rank_sell->getRankListWidget(i)->setDescText(desc);
            this->rank_sell->getRankListWidget(i)->setCoverImg(
                QString(":/ListCover/Res/listcover/music-list-cover%1.jpg").arg(40+i));
            if (i < 3)
                this->rank_sell->getRankListWidget(i)->setRankMedal(pathArr[i]);
            else
                this->rank_sell->getRankListWidget(i)->setRankNumber(QString("%1").arg(i+1));
        }
        file.close();
    }
}

void ListenRankWidget::initRankNew() {
    //解析json文件
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/../jsonFiles/rank-sell.json"));
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Could not open file for reading rank-sell.json";
            return;
        }
        const auto obj = QJsonDocument::fromJson(file.readAll());
        auto arr = obj.array();
        const QString pathArr[] = {
            ":/ListenBook/Res/listenbook/first.svg",
            ":/ListenBook/Res/listenbook/second.svg",
            ":/ListenBook/Res/listenbook/third.svg"
        };
        for (int i = 0 ; i < 5 ; ++i) {
            QString desc = arr[i+5].toObject().value("desc").toString();
            this->rank_new->getRankListWidget(i)->setDescText(desc);
            this->rank_new->getRankListWidget(i)->setCoverImg(
                QString(":/ListCover/Res/listcover/music-list-cover%1.jpg").arg(50+i));
            if (i < 3)
                this->rank_new->getRankListWidget(i)->setRankMedal(pathArr[i]);
            else
                this->rank_new->getRankListWidget(i)->setRankNumber(QString("%1").arg(i+1));
        }
        file.close();
    }
}

void ListenRankWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    //qDebug()<<"当前宽度："<<this->parentWidget()->width();
    if (this->parentWidget()->width() > 1100) {
        this->rank_new->show();
    }
    else {
        this->rank_new->hide();
    }
}
