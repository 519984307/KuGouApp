//
// Created by WeiWang on 24-11-15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SongListWidget.h" resolved

#include "SongListWidget.h"
#include "ui_SongListWidget.h"

#include <QFile>

#define GET_CURRENT_DIR (QString(__FILE__).first(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))

SongListWidget::SongListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SongListWidget)
{
    ui->setupUi(this);
    {
        QFile file(GET_CURRENT_DIR + QStringLiteral("/song.css"));
        if (file.open(QIODevice::ReadOnly)) {
            this->setStyleSheet(file.readAll());
        } else {
            qDebug() << "样式表打开失败QAQ";
            return;
        }
    }
    initUi();
}

SongListWidget::~SongListWidget() {
    delete ui;
}

void SongListWidget::initUi() {
    //批量操作按钮
    ui->batch_toolButton->setIcon(QIcon(QStringLiteral(":/Res/tabIcon/batch-operation-gray.svg")));
    //搜索栏
    ui->search_lineEdit->setPlaceholderText(QStringLiteral("搜索"));
    ui->search_lineEdit->setWidth(200);
    // 创建动作并设置图标
    this->m_searchAction = new QAction(QIcon(":/Res/menuIcon/search-black.svg"), "搜索",ui->search_lineEdit);

    ui->search_lineEdit->addAction(this->m_searchAction, QLineEdit::TrailingPosition); // 右侧显示
    QToolButton* searchButton = nullptr;
    foreach (QToolButton* btn, ui->search_lineEdit->findChildren<QToolButton*>()) {
        if (btn->defaultAction() == this->m_searchAction) {
            searchButton = btn;
            break;
        }
    }

    // 安装事件过滤器
    if (searchButton) {
        searchButton->installEventFilter(this);
    }
    //  连接 hovered 信号
    // connect(searchAction, &QAction::hovered, this, [=]() {
    //
    //     searchAction->setIcon(QIcon(":/Res/menuIcon/search-blue.svg")); // 设置为手形指针
    //
    //  });
    // 连接点击事件
    //connect(this->m_searchAction, &QAction::triggered, [](){
    //    qDebug() << "按钮被点击";
    //});
    initBlock();
}

void SongListWidget::initBlock() const {
    const auto lay = new QHBoxLayout(ui->table_widget);
    lay->setSpacing(10);
    ui->table_widget->setLayout(lay);
    const QString arr[] = {" 我喜欢"," 默认收藏"," 默认列表"};
    for (int i = 0; i < 3; ++i) {
        const auto block = new SongListBlockWidget(ui->table_widget);
        block->setTitleText(arr[i]);
        if (i == 0)block->setCoverPix(QStringLiteral(":/Res/tabIcon/like.jpg"));
        else block->setCoverPix(QStringLiteral(":/Res/tabIcon/playlist.jpg"));
        lay->addWidget(block);
    }
    lay->addStretch();
}

bool SongListWidget::eventFilter(QObject *watched, QEvent *event) {
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
