#ifndef MUSICITEMWIDGET_H
#define MUSICITEMWIDGET_H


#include <QWidget>
#include<QMap>

class QLabel;
class QToolButton;
class QSpacerItem;

typedef struct SongInformation {
    int index;
    QPixmap cover;
    QString songName;
    QString signer;
    QString duration;
}SongInfor;

class MusicItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MusicItemWidget(const SongInfor&info, QWidget *parent = nullptr);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
signals:
    void playRequest(int index);

private:
    void initUi();

private:
    QLabel* m_indexLab{};
    QLabel* m_coverLab{};
    QLabel* m_nameLab{};
    QLabel* m_singerLab{};
    QLabel* m_durationLab{};
    QSpacerItem* m_spacerItem1{};
    QSpacerItem* m_spacerItem2{};
    QToolButton* m_playToolBtn{};
    QToolButton* m_playNextToolBtn{};
    QToolButton* m_downloadToolBtn{};
    QToolButton* m_collectToolBtn{};
    QToolButton* m_moreToolBtn{};

    int m_index;
    QPixmap m_cover;
    QString m_name;
    QString m_singer;
    QString m_duration;

    SongInfor m_information;
};

#endif // MUSICITEMWIDGET_H
