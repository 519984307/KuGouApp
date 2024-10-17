#ifndef TABLEWIDGET_H_
#define TABLEWIDGET_H_

#include<QHBoxLayout>
#include<QGridLayout>
#include<memory>

#include"SMaskWidget.h"

class QLabel;
class QToolButton;
class QPaintEvent;
class QEnterEvent;
class QEvent;
class QLine;
class ItemBlockWidget;
class QTimer;

class TableWidget : public QWidget
{
    Q_OBJECT
public:
    enum KIND{
        BlockList,
        ItemList
    };
    explicit TableWidget(const QString& title ,KIND kind,QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent* ev)override;
    void enterEvent(QEnterEvent* ev)override;
    void leaveEvent(QEvent* ev)override;
    void resizeEvent(QResizeEvent* event)override;
private:
    void initUi();
    //初始化BlockCover
    void initBlockCover();
    //打乱BlockCover
    void shuffleBlockCover();
    //初始化ListCover
    void initListCover();
    //打乱ListCover
    void shuffleListCover();
    //1.大图标TabWidget
    void initItemBlockWidget();
    //2.小图标TabListWidget
    void initItemListWidget();

signals:
    void hideTitle();

    void gridChange(int len);

public slots:
    void onGridChange(int len);
    void onRefreshBtnClicked();
    void onRefreshTimeout();
private:
    std::unique_ptr<QHBoxLayout>m_tabHLayout;
    std::unique_ptr<QGridLayout>m_gridLayout;
    std::unique_ptr<QWidget>m_gridContainer;
    QLabel* m_titleLab{};
    KIND m_kindList;
    QToolButton* m_play_ToolBtn{};
    QToolButton* m_adjust_ToolBtn{};
    QLabel* line1{};
    QToolButton* m_refresh_ToolBtn{};
    QLabel* m_more_Lab{};
    int m_showCol = 5;
    //存储图片
    QVector<QString>m_blockCoverPaths;
    QVector<QString>m_listCoverPaths;
    //隐藏列数
    bool m_hide_col_6 = true;
    bool m_hide_col_7 = true;
    //设置定时器，防止刷新次数太多，导致显示问题
    QTimer* m_refreshTimer;
};

class ItemBlockWidget : public QWidget{
    Q_OBJECT
public:
    ItemBlockWidget(const QString& path,QWidget* parent = nullptr);
    void setTipLabText(const QString& text);
    void setPopularBtnText(const QString& text);

protected:
    void paintEvent(QPaintEvent* ev)override;
    void enterEvent(QEnterEvent* ev)override;
    void leaveEvent(QEvent* ev)override;
    void resizeEvent(QResizeEvent *event) override;
private:
    void initUi();

private:
    QWidget* m_bacWidget{};
    std::unique_ptr<SMaskWidget>m_mask;
    QLabel* m_describeLab{};
    QLabel* m_tipLab{};
    QToolButton* m_popularBtn{};
    bool m_isHoverCoverLab = false;
};


class ItemListWidget : public QWidget{
    Q_OBJECT
public:
    ItemListWidget(QPixmap coverPix,const QString& name,const QString& author,QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* ev)override;
    void enterEvent(QEnterEvent* ev)override;
    void leaveEvent(QEvent* ev)override;
    void resizeEvent(QResizeEvent *event) override;
private:
    void initUi();
public slots:
    void onHide();
private:
    std::unique_ptr<SMaskWidget>m_mask;
    QLabel* m_coverLab{};
    QLabel* m_nameLab{};
    QLabel* m_authorLab{};
    QToolButton* m_play_add_ToolBtn{};
    QToolButton* m_like_ToolBtn{};
    QToolButton* m_more_ToolBtn{};
    bool m_isHoverCoverLab = false;
    int m_aspectRatio = 6;
};



#endif // TABLEWIDGET_H_
