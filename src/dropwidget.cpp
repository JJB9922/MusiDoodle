#include "dropwidget.h"
#include <QPainter>

DropWidget::DropWidget(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true);
    setBackgroundColor(QColor(74, 74, 74, 255));
}

void DropWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        event->acceptProposedAction();
    }
}

void DropWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        QString text = event->mimeData()->text();

        int centerY = height() / 4;
        bool labelExists = false;
        foreach (QObject *child, children()) {
            QLabel *existingLabel = qobject_cast<QLabel*>(child);
            if (existingLabel && existingLabel->geometry().contains(event->position().toPoint())) {
                labelExists = true;
                break;
            }
        }

        if (!labelExists) {
            QLabel *label = new QLabel(text, this);
            label->move(event->position().toPoint().x(), centerY);
            label->show();
            event->acceptProposedAction();
        }
    }
}

void DropWidget::setBackgroundColor(const QColor &color) {
    m_backgroundColor = color;
    update();
}

void DropWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), m_backgroundColor);
    update();
}
