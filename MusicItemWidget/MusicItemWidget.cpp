#include "MusicItemWidget.h"
#include<QLabel>
#include<QToolButton>
#include<QVBoxLayout>
#include<QSpacerItem>
#include<QFile>
#include<QTimer>
#include <QCursor>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QGuiApplication>
#include <QPainterPath>
#include <QtMath>
#include <QPointF>
#include <utility>

//图片大小
#define PIX_SIZE 50
//图片圆角
#define PIX_RADIUS 9
// 创建一个宏来截取 __FILE__ 宏中的目录部分
#define GET_CURRENT_DIR (QString(__FILE__).first(qMax(QString(__FILE__).lastIndexOf('/'), QString(__FILE__).lastIndexOf('\\'))))
QPixmap roundedPix(const QPixmap &src, QSize size, int radius) {
    QPixmap scaled = src.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap dest(size);
    dest.fill(Qt::transparent);

    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(0, 0, size.width(), size.height(), radius, radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, scaled);

    return dest;
}
MusicItemWidget::MusicItemWidget(SongInfor  infor, QWidget *parent)
    :QFrame(parent)
    ,m_information(std::move(infor))
    ,m_menu(new MyMenu(this))
    ,timer(new QTimer(this))
{

    this->m_index           = m_information.index;
    this->m_name            = m_information.songName;
    this->m_duration        = m_information.duration;
    this->m_cover           = m_information.cover;
    this->m_singer          = m_information.signer;
    //qDebug()<<"m_index: "<<m_index<<" name: "<<m_name<<" duration: "<<m_duration<<
    //    " cover: "<<m_cover<<"m_singer: "<<m_singer;
    this->m_indexLab        = new QLabel(QString("%1").arg(this->m_index, 2, 10, QChar('0')), this);
    this->m_coverLab        = new QLabel(this);
    this->m_coverLab->setAlignment(Qt::AlignCenter);
    this->m_coverLab->setFixedSize(PIX_SIZE,PIX_SIZE);
    this->m_coverLab->setPixmap(roundedPix(this->m_cover,this->m_coverLab->size(),PIX_RADIUS));
    this->m_nameLab         = new QLabel(this->m_name,this);
    this->m_singerLab       = new QLabel(this->m_singer,this);
    this->m_spacerItem1     = new QSpacerItem(40,20,QSizePolicy::Expanding);
    this->m_spacerItem2     = new QSpacerItem(40,20,QSizePolicy::Fixed);
    this->m_durationLab     = new QLabel(this->m_duration,this);
    this->m_playToolBtn     = new QToolButton(this);
    this->m_playNextToolBtn = new QToolButton(this);
    this->m_downloadToolBtn = new QToolButton(this);
    this->m_collectToolBtn  = new QToolButton(this);
    this->m_moreToolBtn     = new QToolButton(this);

    this->setObjectName(QStringLiteral("window"));
    this->m_indexLab->setObjectName(QStringLiteral("indexLab"));
    this->m_coverLab->setObjectName(QStringLiteral("coverLab"));
    this->m_nameLab->setObjectName(QStringLiteral("nameLab"));
    this->m_singerLab->setObjectName(QStringLiteral("singerLab"));
    this->m_durationLab->setObjectName(QStringLiteral("durationLab"));
    this->m_playToolBtn->setObjectName(QStringLiteral("playToolBtn"));
    this->m_playNextToolBtn->setObjectName(QStringLiteral("playNextToolBtn"));
    this->m_downloadToolBtn->setObjectName(QStringLiteral("downloadToolBtn"));
    this->m_collectToolBtn->setObjectName(QStringLiteral("collectToolBtn"));
    this->m_moreToolBtn->setObjectName(QStringLiteral("moreToolBtn"));
    //设置样式
    QFile file(GET_CURRENT_DIR + QStringLiteral("/item.css"));
    if (file.open(QIODevice::ReadOnly)) {
        this->setStyleSheet(file.readAll());
    } else {
        qDebug() << "样式表打开失败QAQ";
        return;
    }

    timer->setInterval(timeInterval); // 设置定时器时间间隔
    max_radius = static_cast<int>(qSqrt(width() * width() + height() * height())); // 计算最大半径

    initUi();

    connect(this->m_playToolBtn,&QToolButton::clicked,this,&MusicItemWidget::onPlayToolBtnClicked);
    connect(this->m_playNextToolBtn,&QToolButton::clicked,this,&MusicItemWidget::onPlayNextToolBtnClicked);
    connect(this->m_downloadToolBtn,&QToolButton::clicked,this,&MusicItemWidget::onDownloadToolBtnClicked);
    connect(this->m_collectToolBtn,&QToolButton::clicked,this,&MusicItemWidget::onCollectToolBtnClicked);
    connect(this->m_moreToolBtn,&QToolButton::clicked,this,&MusicItemWidget::onMoreToolBtnClicked);
}

void MusicItemWidget::setInterval(const int &timeinterval) {
    timer->setInterval(timeinterval);
}

void MusicItemWidget::setFillColor(const QColor &fillcolor) {
    fill_color = fillcolor;
}

void MusicItemWidget::setRadius(int radius_) {
    frame_radius = radius_;
}

void MusicItemWidget::setInformation(const SongInfor &info) {
    this->m_index = info.index;
    this->m_name = info.songName;
    this->m_duration = info.duration;
    this->m_cover = info.cover;
    this->m_singer = info.signer;
    this->m_indexLab->setText(QString("%1").arg(this->m_index, 2, 10, QChar('0')));
    this->m_coverLab->setPixmap(roundedPix(this->m_cover, this->m_coverLab->size(), PIX_RADIUS));
    this->m_nameLab->setText(this->m_name);
    this->m_singerLab->setText(this->m_singer);
    this->m_durationLab->setText(this->m_duration);
    update(); // 重绘
}

void MusicItemWidget::setPlayState(const bool &state) {
    this->m_isPlaying = state;
    if(this->m_isPlaying) {
        //发送进入事件
        // 创建一个进入事件
        QEvent enterEvent(QEvent::Enter);
        // 发送离开事件
        QCoreApplication::sendEvent(this, &enterEvent);
    }
    else {
        //发送离开事件
        // 创建一个离开事件
        QEvent leaveEvent(QEvent::Leave);
        // 发送离开事件
        QCoreApplication::sendEvent(this, &leaveEvent);
    }
}

void MusicItemWidget::getMenuPosition(const QPoint& pos) {
    this->m_window = this->window();
    if(pos.isNull()) {
        this->m_menuPosition = this->m_window->mapFromGlobal(mapToGlobal(this->m_moreToolBtn->pos()));
    }
    else {
        this->m_menuPosition = this->m_window->mapFromGlobal(mapToGlobal(pos));
    }
    this->m_menuPosition += QPoint(10,10);
    /*// 获取屏幕的尺寸
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // 计算菜单右侧的全局位置
    QPoint menuGlobalPos = this->mapToGlobal(m_menuPosition);
    int menuRightPos  = menuGlobalPos.x() + m_menu->width();
    int menuBottomPos = menuGlobalPos.y() + m_menu->height();

    // 如果菜单右侧超出屏幕右侧
    if (menuRightPos > screenGeometry.right()) {
        // 动态调整菜单位置，使其在屏幕内显示
        int offset = menuRightPos - screenGeometry.right() + 10;
        m_menuPosition.setX(m_menuPosition.x() - offset);
    }
    // 如果菜单下侧超出屏幕下侧
    if (menuBottomPos > screenGeometry.bottom()) {
        // 动态调整菜单位置，使其在屏幕内显示
        int offset = menuBottomPos - screenGeometry.bottom() + 10;
        m_menuPosition.setY(m_menuPosition.y() - offset);
    }
*/
}

void MusicItemWidget::enterEvent(QEnterEvent *event) {
    QFrame::enterEvent(event);

    mouse_point = event->position(); // 记录鼠标进入坐标
    timer->disconnect(); // 断开可能的timer的所有连接
    connect(timer, &QTimer::timeout, this, [=]{ // 定时器触发，半径增大
        radius += radius_var;
        if (radius > max_radius) {
            timer->stop(); // 达到最大半径，定时器停止
            return;
        }
        update(); // 调用绘制事件
    });
    timer->start(); // 定时器开始
}

void MusicItemWidget::leaveEvent(QEvent *event) {
    QFrame::leaveEvent(event);
    if(!this->m_isPlaying) {
        mouse_point = mapFromGlobal(QCursor::pos());
        timer->disconnect();
        connect(timer, &QTimer::timeout, this, [=]{ // 定时器触发半径减小
            radius -= radius_var;
            if (radius < 0) {
                timer->stop(); // 减小到小于0时定时器停止
                radius = 0; // 确保半径不为负
                return;
            }
            update();
        });
        timer->start();
    }
}

void MusicItemWidget::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    if (!mouse_point.isNull() && radius > 0)
    {
        QPainter painter(this);
        QPainterPath path;
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(QBrush(fill_color));
        painter.setPen(Qt::NoPen);
        path.addRoundedRect(rect(), frame_radius, frame_radius);
        painter.setClipPath(path);
        painter.drawEllipse(mouse_point, radius, radius); // 画圆
    }
}

void MusicItemWidget::resizeEvent(QResizeEvent *event) {
    QFrame::resizeEvent(event);
    max_radius = static_cast<int>(qSqrt(width() * width() + height() * height())); // 重新计算最大半径
    //设置弹簧宽度
    this->m_spacerItem2->changeSize(this->width()/5,20,QSizePolicy::Fixed);
}

void MusicItemWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QFrame::mouseDoubleClickEvent(event);
    this->m_playToolBtn->clicked();
}

void MusicItemWidget::mousePressEvent(QMouseEvent *event) {
    // 判断是否为右键点击
    if (event->button() == Qt::RightButton) {
        qDebug()<<"右键";
        getMenuPosition(event->pos());
        this->m_menu->move(this->m_menuPosition);
        this->m_menu->show();
    }
    //QFrame::mousePressEvent(event);要注释掉这一行，否则会不显示
}

void MusicItemWidget::onPlayToolBtnClicked() {
    emit playRequest();
}

void MusicItemWidget::onPlayNextToolBtnClicked() {
}

void MusicItemWidget::onDownloadToolBtnClicked() {
}

void MusicItemWidget::onCollectToolBtnClicked() {
}

void MusicItemWidget::onMoreToolBtnClicked() {
    getMenuPosition();
    this->m_menu->move(this->m_menuPosition);
    this->m_menu->show();
}

void MusicItemWidget::initUi()
{
    this->m_playToolBtn     ->setIcon(QIcon(QStringLiteral("://Res/tabIcon/play3-gray.svg")));
    this->m_playNextToolBtn ->setIcon(QIcon(QStringLiteral("://Res/tabIcon/add-music-list-gray.svg")));
    this->m_downloadToolBtn ->setIcon(QIcon(QStringLiteral("://Res/window/download.svg")));
    this->m_collectToolBtn  ->setIcon(QIcon(QStringLiteral("://Res/window/collect.svg")));
    this->m_moreToolBtn     ->setIcon(QIcon(QStringLiteral("://Res/tabIcon/more2-gray.svg")));

    this->m_playToolBtn     ->setCursor(Qt::PointingHandCursor);
    this->m_playNextToolBtn ->setCursor(Qt::PointingHandCursor);
    this->m_downloadToolBtn ->setCursor(Qt::PointingHandCursor);
    this->m_collectToolBtn  ->setCursor(Qt::PointingHandCursor);
    this->m_moreToolBtn     ->setCursor(Qt::PointingHandCursor);

    this->m_menu->hide();

    auto hlayout = new QHBoxLayout(this);
    hlayout->addWidget(this->m_indexLab);
    hlayout->addWidget(this->m_coverLab);
    auto vlayout = new QVBoxLayout;
    vlayout->addWidget(this->m_nameLab);
    vlayout->addWidget(this->m_singerLab);
    hlayout->addLayout(vlayout);
    hlayout->addSpacerItem(this->m_spacerItem1);
    hlayout->addWidget(this->m_durationLab);
    hlayout->addSpacerItem(this->m_spacerItem2);
    hlayout->addWidget(this->m_playToolBtn);
    hlayout->addWidget(this->m_playNextToolBtn);
    hlayout->addWidget(this->m_downloadToolBtn);
    hlayout->addWidget(this->m_collectToolBtn);
    hlayout->addWidget(this->m_moreToolBtn);

    this->m_durationLab->move(this->width()*5/6,(this->height() - this->m_durationLab->height()) / 2);
}
