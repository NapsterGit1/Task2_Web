#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QPen>

#include "web.h"

Web::Web(QWidget *parent) : QWidget{parent} {}

void Web::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (isWebDrawing_ == true) {
        QPainter painter(this);
        int numLines = 12;
        double radiusWeb = 0.75;
        QVector<QPoint> centerPoints;

        for (int i = 0; i < numLines; i++) {
            double angleInDegrees = i * 360 / numLines;
            QPoint pointOnCircle(centerPoint_.x() + kWebRadius * qCos(qDegreesToRadians(angleInDegrees)),
                                 centerPoint_.y() + kWebRadius * qSin(qDegreesToRadians(angleInDegrees)));
            QPoint centerLine(centerPoint_.x() + (kWebRadius * qCos(qDegreesToRadians(angleInDegrees))) * radiusWeb,
                              centerPoint_.y() + (kWebRadius * qSin(qDegreesToRadians(angleInDegrees))) * radiusWeb);
            centerPoints.append(centerLine);

            painter.setPen(QPen(Qt::black, 3));
            painter.drawLine(centerPoint_, pointOnCircle);
            painter.drawPoint(centerLine);
        }

        for (int i = 0; i < numLines; i++){
            int nextIndex = (i + 1) % numLines;
            painter.drawLine(centerPoints[i], centerPoints[nextIndex]);
        }
    }
}

void Web::mousePressEvent(QMouseEvent *event) {

    if(event->button() == Qt::LeftButton) {
        centerPoint_ = event->pos();
        isWebDrawing_ = true;
        setCursor(Qt::CrossCursor);
        update();
    }
}

void Web::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    isWebDrawing_ = false;
    setCursor(Qt::ArrowCursor);
    update();
}

void Web::mouseMoveEvent(QMouseEvent *event) {

    if(isWebDrawing_ == true) {
        centerPoint_ = event->pos();
        KeepCursorInWidget();
        update();
    }
}

void Web::KeepCursorInWidget() {
    if (centerPoint_.x() < kWebRadius) centerPoint_.setX(kWebRadius);

    if (centerPoint_.x() > width() - kWebRadius) centerPoint_.setX(width() - kWebRadius);

    if (centerPoint_.y() < kWebRadius) centerPoint_.setY(kWebRadius);

    if (centerPoint_.y() > height() - kWebRadius) centerPoint_.setY(height() - kWebRadius);
}
