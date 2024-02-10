#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>
#include <QPainter>

class DropWidget : public QWidget {
    Q_OBJECT
public:
    explicit DropWidget(QWidget *parent = nullptr);
    void setBackgroundColor(const QColor &color);

signals:
    void labelDropped(const QString &text);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint m_dragStartPosition;
    QLabel *m_draggedLabel;
    QColor m_backgroundColor;
};

#endif // DROPWIDGET_H
