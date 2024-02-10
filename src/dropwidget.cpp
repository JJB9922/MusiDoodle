#include "dropwidget.h"
#include <QMouseEvent>

DropWidget::DropWidget(QWidget *parent) : QWidget(parent) {
    setAcceptDrops(true);
    setBackgroundColor(QColor(74, 74, 74, 255));
}

void DropWidget::mousePressEvent(QMouseEvent *event) {
    QLabel *labelUnderMouse = qobject_cast<QLabel*>(childAt(event->position().toPoint()));

    if (event->button() == Qt::RightButton) {
        if (labelUnderMouse) {
            labelUnderMouse->clear();
        }
    } else {
        if (labelUnderMouse) {
            m_dragStartPosition = event->position().toPoint() - labelUnderMouse->pos();
            m_draggedLabel = labelUnderMouse;
        }
    }
}

void DropWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_draggedLabel && event->buttons() & Qt::LeftButton) {
        QPoint newPos = event->position().toPoint() - m_dragStartPosition;
        m_draggedLabel->move(newPos);
    }
}

void DropWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (m_draggedLabel && event->button() == Qt::LeftButton) {
        int centerY = height() / 4;
        m_draggedLabel->move(event->position().toPoint().x(), centerY);
        m_draggedLabel = nullptr;
    }
}

void DropWidget::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        QString text = event->mimeData()->text();
        int centerY = height() / 4;
        QLabel *label = new QLabel(text, this);
        label->move(event->position().toPoint().x(), centerY);
        label->show();
        event->acceptProposedAction();

        emit labelDropped(text);
    }
}

void DropWidget::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat("text/plain")) {
        event->acceptProposedAction();
    }
}

void DropWidget::setBackgroundColor(const QColor &color) {
    m_backgroundColor = color;
    update();
}

void DropWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), m_backgroundColor);
}
