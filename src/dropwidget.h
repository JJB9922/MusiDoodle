#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>

class DropWidget : public QWidget {
    Q_OBJECT
public:
    explicit DropWidget(QWidget *parent = nullptr);
    void setBackgroundColor(const QColor &color);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QColor m_backgroundColor;
};

#endif // DROPWIDGET_H
