//
// Created by WeiWang on 25-1-27.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DownloadedSong.h" resolved

#include "DownloadedSong.h"
#include "ui_DownloadedSong.h"
#include "MyMenu.h"

#include <QFile>
#include <QScreen>

#define GET_CURRENT_DIR (QString(__FILE__).first(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))

DownloadedSong::DownloadedSong(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownloadedSong)
    , m_searchAction(new QAction(this))
{
    ui->setupUi(this);
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/downloadedsong.css"));
        if (file.open(QIODevice::ReadOnly)) {
            this->setStyleSheet(file.readAll());
        } else {
            qDebug() << "样式表打开失败QAQ";
            return;
        }

    }
    initUi();
}

DownloadedSong::~DownloadedSong() {
    delete ui;
}

void DownloadedSong::initUi() {
    ui->local_play_toolButton->setIcon(QIcon(QStringLiteral(":/Res/tabIcon/play3-white.svg")));
    //使用 addAction 添加右侧图标
    this->m_searchAction->setIcon(QIcon(QStringLiteral(":/Res/menuIcon/search-black.svg")));
    this->m_searchAction->setIconVisibleInMenu(false); // 仅显示图标
    ui->local_search_lineEdit->addAction(this->m_searchAction, QLineEdit::TrailingPosition);
    ui->local_search_lineEdit->setWidth(150);
    QToolButton* searchButton = nullptr;
    foreach (QToolButton* btn, ui->local_search_lineEdit->findChildren<QToolButton*>()) {
        if (btn->defaultAction() == this->m_searchAction) {
            searchButton = btn;
            break;
        }
    }
    // 安装事件过滤器
    if (searchButton) {
        searchButton->installEventFilter(this);
    }
    //初始化menu
    const auto menu = new MyMenu(MyMenu::MenuKind::SortOption, this);
    this->m_sortOptMenu = menu->getMenu<SortOptionMenu>();

}

void DownloadedSong::getMenuPosition(const QPoint &pos) {
    this->m_menuPosition = pos;
    // 获取屏幕的尺寸
    const QScreen *screen = QGuiApplication::primaryScreen();
    const QRect screenGeometry = screen->geometry();

    // 计算菜单右侧的全局位置
    //int menuLeftPos = pos.x() - m_menu->width();
    const int menuRightPos = pos.x() + m_sortOptMenu->width();
    const int menuBottomPos = pos.y() + m_sortOptMenu->height();
    //int menuTopPos = pos.y() - m_menu->height();
    // 若菜单左侧超出屏幕左侧 (不存在)
    //if(menuLeftPos < 0) {
    //    // 动态调整菜单位置，使其在屏幕内显示
    //    m_menuPosition.setX(10);
    //}
    // 如果菜单右侧超出屏幕右侧
    if (menuRightPos > screenGeometry.right()) {
        // 动态调整菜单位置，使其在屏幕内显示
        const int offset = menuRightPos - screenGeometry.right() + 5;
        m_menuPosition.setX(pos.x() - offset);
    }
    // 如果菜单下侧超出屏幕下侧
    if (menuBottomPos > screenGeometry.bottom()) {
        // 动态调整菜单位置，使其在屏幕内显示
        const int offset = menuBottomPos - screenGeometry.bottom() + 5;
        m_menuPosition.setY(pos.y() - offset);
    }
    // 如果菜单下侧超出屏幕下侧（不存在）
    //if(menuTopPos < 0) {
    //    // 动态调整菜单位置，使其在屏幕内显示
    //    m_menuPosition.setY(10);
    //}
}

void DownloadedSong::on_local_sort_toolButton_clicked() {
    getMenuPosition(QCursor::pos());
    this->m_sortOptMenu->move(this->m_menuPosition);
    this->m_sortOptMenu->show();
}

bool DownloadedSong::eventFilter(QObject *watched, QEvent *event) {
    const auto button = qobject_cast<QToolButton*>(watched);
    if (button && button->defaultAction() == this->m_searchAction) {
        if (event->type() == QEvent::Enter) {
            this->m_searchAction->setIcon(QIcon(QStringLiteral(":/Res/menuIcon/search-blue.svg")));
        } else if (event->type() == QEvent::Leave) {
            this->m_searchAction->setIcon(QIcon(QStringLiteral(":/Res/menuIcon/search-black.svg")));
        }
    }
    return QObject::eventFilter(watched, event);
}
