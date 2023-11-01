#ifndef WEB_H
#define WEB_H

#include <QWidget>

class Web : public QWidget {
  Q_OBJECT
public:
    explicit Web(QWidget *parent = nullptr);
    const int kWebRadius = 50;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint centerPoint_;
    bool isWebDrawing_ = false;

    void KeepCursorInWidget();
};

#endif  // WEB_H
