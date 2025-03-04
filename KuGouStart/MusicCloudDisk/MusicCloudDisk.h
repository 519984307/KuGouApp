//
// Created by WeiWang on 24-11-14.
//

#ifndef MUSICCLOUDDISK_H
#define MUSICCLOUDDISK_H

#include"UploadedSong.h"
#include"UploadingSong.h"

#include <QWidget>

#if defined(MUSICCLOUDDISK_LIBRARY)
#define MUSICCLOUDDISK_EXPORT Q_DECL_EXPORT
#else
#define MUSICCLOUDDISK_EXPORT Q_DECL_IMPORT
#endif

class QButtonGroup;

QT_BEGIN_NAMESPACE
namespace Ui { class MusicCloudDisk; }
QT_END_NAMESPACE

class MUSICCLOUDDISK_EXPORT MusicCloudDisk : public QWidget {
Q_OBJECT

public:
    explicit MusicCloudDisk(QWidget *parent = nullptr);

    ~MusicCloudDisk() override;

private:
    void initUi();

    void initIndexLab();

    void initStackedWidget();

    void initUploadedSong();

    void initUploadingSong();

private slots:
    void on_uploaded_song_pushButton_clicked();

    void on_uploading_song_pushButton_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MusicCloudDisk *ui;
    std::unique_ptr<QButtonGroup>   m_buttonGroup{};
    //堆栈窗口
    std::unique_ptr<UploadedSong>   m_uploadedSong{};
    std::unique_ptr<UploadingSong>   m_uploadingSong{};
};


#endif //MUSICCLOUDDISK_H
