//
// Created by WeiWang on 25-2-6.
//

#ifndef WATERZOOMBUTTON_H
#define WATERZOOMBUTTON_H

#include "InteractiveButtonBase.h"

class WaterZoomButton : public InteractiveButtonBase {
    Q_OBJECT

public:
    explicit WaterZoomButton(const QString& text = "", QWidget *parent = nullptr);

    void setChoking(const int& c);

    void setChokingProp(const double& p);

    void setRadiusZoom(const int& radius);

    void setRadius(const int& x, const int& x2);

protected:
    QPainterPath getBgPainterPath() override;

    void resizeEvent(QResizeEvent *event) override;

    int choking; // 向里缩的长度
    double choking_prop;
    int radius_zoom; // 收缩时的半径
};


#endif //WATERZOOMBUTTON_H
