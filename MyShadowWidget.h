#pragma once

#include <QWidget>

class MyShadowWidget : public QWidget
{
    Q_OBJECT

public:
    MyShadowWidget(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event);

    void resizeEvent(QResizeEvent *event);

private:
    QPixmap m_shadowBackPixmap;
    
};
