#ifndef VOLUMETOOLBTN_H
#define VOLUMETOOLBTN_H

#include"SliderWidget.h"

#if defined(VOLUMETOOLBTN_LIBRARY)
#define VOLUMETOOLBTN_EXPORT Q_DECL_EXPORT
#else
#define VOLUMETOOLBTN_EXPORT Q_DECL_IMPORT
#endif

#include <QToolButton>
#include <QLabel>

class QTimer;
class QVBoxLayout;

class VOLUMETOOLBTN_EXPORT VolumeToolBtn : public QToolButton {
    Q_OBJECT

public:
    explicit VolumeToolBtn(QWidget *parent = nullptr);

    void initVolumeWidget();

    void initUi();

    void checkMousePosition() const;

    void getVolumeWidgetPosition();

protected:
    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *event) override;

    void showEvent(QShowEvent *event) override;

public slots:
    void onNoVolume(bool flag);

signals:
    void volumeChange(int value);

private:
    bool m_isNoVolume = false;
    std::unique_ptr<MyWidget> m_volumeWidget;
    std::unique_ptr<QLabel> m_volumeLab;
    std::unique_ptr<SliderWidget> m_volumeSlider;
    QVBoxLayout *m_vBoxLayout{};
    QPoint m_volumePosition;
    QWidget *m_volumeParent{};
    QTimer *m_leaveTimer{};
    QTimer *m_positionCheckTimer; // 检查鼠标位置是否在m_volumeWidget上面
};

#endif //VOLUMETOOLBTN_H
