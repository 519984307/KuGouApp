//
// Created by WeiWang on 25-1-31.
//

#ifndef RECENTLYMVCHANNEL_H
#define RECENTLYMVCHANNEL_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class RecentlyMVChannel; }
QT_END_NAMESPACE

class RecentlyMVChannel : public QWidget {
Q_OBJECT

public:
    explicit RecentlyMVChannel(QWidget *parent = nullptr);
    ~RecentlyMVChannel() override;

private:
    Ui::RecentlyMVChannel *ui;
};


#endif //RECENTLYMVCHANNEL_H
