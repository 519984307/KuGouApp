//
// Created by WeiWang on 24-11-15.
//

#ifndef ALLRECENT_H
#define ALLRECENT_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class AllRecent; }
QT_END_NAMESPACE

class AllRecent : public QWidget {
Q_OBJECT

public:
    explicit AllRecent(QWidget *parent = nullptr);
    ~AllRecent() override;

private:
    Ui::AllRecent *ui;
};


#endif //ALLRECENT_H
