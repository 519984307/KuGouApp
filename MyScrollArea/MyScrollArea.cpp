//
// Created by WeiWang on 24-10-16.
//
#include "MyScrollArea.h"
#include <QWheelEvent>
MyScrollArea::MyScrollArea(QWidget *parent)
    :QScrollArea(parent)
    , m_isAnimating(false)
{

}

void MyScrollArea::setAnimating(const bool& animating) {
    this->m_isAnimating = animating;
}

void MyScrollArea::wheelEvent(QWheelEvent *event) {
    if (!this->m_isAnimating) {
        // 如果没有动画进行，正常处理滚轮事件
        QScrollArea::wheelEvent(event);
    } else {
        // 如果正在进行动画，忽略滚轮事件
        event->ignore();
    }
}
