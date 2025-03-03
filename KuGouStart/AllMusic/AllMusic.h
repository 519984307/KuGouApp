//
// Created by WeiWang on 24-11-15.
//

#ifndef ALLMUSIC_H
#define ALLMUSIC_H

#include "AllWidget.h"
#include "AllLove.h"
#include "AllSongList.h"
#include "AllRecent.h"
#include "AllLocal.h"
#include "AllPaid.h"
#include "AllCloudDisk.h"
#include "SortOptionMenu.h"

#include <QWidget>

class QButtonGroup;

// 添加导出宏定义
#if defined(ALLMUSIC_LIBRARY)
#define ALLMUSIC_EXPORT Q_DECL_EXPORT
#else
#define ALLMUSIC_EXPORT Q_DECL_IMPORT
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class AllMusic; }
QT_END_NAMESPACE

class ALLMUSIC_EXPORT AllMusic : public QWidget {
Q_OBJECT

public:
    explicit AllMusic(QWidget *parent = nullptr);

    ~AllMusic() override;

private:
    void initUi();

    void initIndexLab();

    void initStackedWidget();

    void initAllWidget();

    void initAllLove();

    void initAllSongList();

    void initAllRecent();

    void initAllLocal();

    void initAllPaid();

    void initAllCloudDisk();

    void getMenuPosition(const QPoint &pos);

private slots:
    void on_all_pushButton_clicked();

    void on_love_pushButton_clicked();

    void on_song_list_pushButton_clicked();

    void on_recent_pushButton_clicked();

    void on_local_pushButton_clicked();

    void on_paid_pushButton_clicked();

    void on_cloud_disk_pushButton_clicked();

    void on_all_sort_toolButton_clicked();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::AllMusic *ui;
    std::unique_ptr<QButtonGroup>   m_buttonGroup{};
    //堆栈窗口
    std::unique_ptr<AllWidget>      m_allWidget{};
    std::unique_ptr<AllLove>        m_allLove{};
    std::unique_ptr<AllSongList>    m_allSongList{};
    std::unique_ptr<AllRecent>      m_allRecent{};
    std::unique_ptr<AllLocal>       m_allLocal{};
    std::unique_ptr<AllPaid>        m_allPaid{};
    std::unique_ptr<AllCloudDisk>   m_allCloudDisk{};
    QAction *m_searchAction; //专门为了设置图片

    //菜单相关
    SortOptionMenu *m_sortOptMenu{};
    QPoint m_menuPosition;
};


#endif //ALLMUSIC_H
