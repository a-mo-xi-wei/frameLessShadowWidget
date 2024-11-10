#include "MyShadowWidget.h"
#include <QPainter>

#define SHADOW_WIDTH 15

QPixmap ninePatchScalePixmap(QString picName, int iHorzSplit, int iVertSplit, int DstWidth, int DstHeight)
{
    QPixmap* pix = new QPixmap(picName);

    int pixWidth = pix->width();
    int pixHeight = pix->height();

    QPixmap pix_1 = pix->copy(0, 0, iHorzSplit, iVertSplit);
    QPixmap pix_2 = pix->copy(iHorzSplit, 0, pixWidth - iHorzSplit * 2, iVertSplit);
    QPixmap pix_3 = pix->copy(pixWidth - iHorzSplit, 0, iHorzSplit, iVertSplit);

    QPixmap pix_4 = pix->copy(0, iVertSplit, iHorzSplit, pixHeight - iVertSplit * 2);
    QPixmap pix_5 = pix->copy(iHorzSplit, iVertSplit, pixWidth - iHorzSplit * 2, pixHeight - iVertSplit * 2);
    QPixmap pix_6 = pix->copy(pixWidth - iHorzSplit, iVertSplit, iHorzSplit, pixHeight - iVertSplit * 2);

    QPixmap pix_7 = pix->copy(0, pixHeight - iVertSplit, iHorzSplit, iVertSplit);
    QPixmap pix_8 = pix->copy(iHorzSplit, pixHeight - iVertSplit, pixWidth - iHorzSplit * 2, pixWidth - iHorzSplit * 2);
    QPixmap pix_9 = pix->copy(pixWidth - iHorzSplit, pixHeight - iVertSplit, iHorzSplit, iVertSplit);

    pix_2 = pix_2.scaled(DstWidth - iHorzSplit * 2, iVertSplit, Qt::IgnoreAspectRatio);//保持高度拉宽;
    pix_4 = pix_4.scaled(iHorzSplit, DstHeight - iVertSplit * 2, Qt::IgnoreAspectRatio);//保持宽度拉高;
    pix_5 = pix_5.scaled(DstWidth - iHorzSplit * 2, DstHeight - iVertSplit * 2, Qt::IgnoreAspectRatio);//宽高都缩放;
    pix_6 = pix_6.scaled(iHorzSplit, DstHeight - iVertSplit * 2, Qt::IgnoreAspectRatio);//保持宽度拉高;
    pix_8 = pix_8.scaled(DstWidth - iHorzSplit * 2, iVertSplit);//保持高度拉宽;


    QPixmap resultImg(DstWidth, DstHeight);
    // 需设置背景透明;
    resultImg.fill(Qt::transparent);
    QPainter painter =QPainter(&resultImg);
    if (!resultImg.isNull()) {
        painter.drawPixmap(0, 0, pix_1);
        painter.drawPixmap(iHorzSplit, 0, pix_2);
        painter.drawPixmap(DstWidth - iHorzSplit, 0, pix_3);

        painter.drawPixmap(0, iVertSplit, pix_4);
        painter.drawPixmap(iHorzSplit, iVertSplit, pix_5);
        painter.drawPixmap(DstWidth - iHorzSplit, iVertSplit, pix_6);

        painter.drawPixmap(0, DstHeight - iVertSplit, pix_7);
        painter.drawPixmap(iHorzSplit, DstHeight - iVertSplit, pix_8);
        painter.drawPixmap(DstWidth - iHorzSplit, DstHeight - iVertSplit, pix_9);
        painter.end();
    }

    return resultImg;
}

MyShadowWidget::MyShadowWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(QSize(600, 400));

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void MyShadowWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), m_shadowBackPixmap);
    painter.fillRect(QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, this->height() - 2 * SHADOW_WIDTH), QBrush(Qt::white));
  
    return;

//     painter.fillRect(this->rect().adjusted(SHADOW_WIDTH, SHADOW_WIDTH, -SHADOW_WIDTH, -SHADOW_WIDTH), QBrush(Qt::white));
//     QColor color(50, 50, 50, 30);
//     for (int i = 0; i < SHADOW_WIDTH; i++)
//     {
//         color.setAlpha(120 - qSqrt(i) * 40);
//         painter.setPen(color);
//         // 方角阴影边框;
//      //   painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
//         // 圆角阴影边框;
//         painter.drawRoundedRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2, 4, 4);
//     }
}

void MyShadowWidget::resizeEvent(QResizeEvent *event)
{
    m_shadowBackPixmap = ninePatchScalePixmap("://Resources/ShadowImage.png",
        SHADOW_WIDTH, SHADOW_WIDTH, this->width(), this->height());

    return QWidget::resizeEvent(event);
}
