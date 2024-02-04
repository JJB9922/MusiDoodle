#include "chordselector.h"

#include <iostream>
#include <QTextBrowser>
#include <QLabel>
#include <QtWidgets>

ChordSelector::ChordSelector(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    chordBox = new QTextBrowser(this);
    chordBox->setFixedSize(128, 32);

    noteListWidget = new QListWidget(this);
    connect(noteListWidget, &QListWidget::itemClicked, this, &ChordSelector::onNoteClicked);

    typeListWidget = new QListWidget(this);
    connect(typeListWidget, &QListWidget::itemClicked, this, &ChordSelector::onTypeClicked);

    majorVariationListWidget = new QListWidget(this);
    connect(majorVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    minorVariationListWidget = new QListWidget(this);

    blankListWidget = new QListWidget(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(noteListWidget);
    stackedWidget->addWidget(typeListWidget);
    stackedWidget->addWidget(majorVariationListWidget);
    stackedWidget->addWidget(minorVariationListWidget);
    stackedWidget->addWidget(blankListWidget);

    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &ChordSelector::onBackClicked);

    mainLayout->addWidget(chordBox);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(backButton);

    initializeNotes();
    initializeTypes();
    initializeMajorVariations();
    initializeMinorVariations();
    initializeBlankList();

    int x = 5;
    int y = 5;
}

void ChordSelector::onNoteClicked(QListWidgetItem* item) {
    if (item->text() != "CUSTOM") {
        stackedWidget->setCurrentIndex(1);
        chosenNote = item->text();
        chordBox->setText(chosenNote);

    } else {
        stackedWidget ->setCurrentIndex(stackedWidget->count()-1);
        chordBox->setReadOnly(false);
        putDragLabelOnScreen(chordBox->toPlainText());
    }
}

static QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }

QLabel* ChordSelector::createDragLabel(const QString& text, QWidget *parent)
{
    QLabel *label = new QLabel(text, this);
    label->setAutoFillBackground(true);
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Raised);
    return label;
}

void ChordSelector::putDragLabelOnScreen(const QString& word){
        int x = 150;
        int y = 10;

        if (currentDragLabel) {
            currentDragLabel->deleteLater();
            currentDragLabel = nullptr;
        }

        if (!chordBox->toPlainText().isEmpty()) {
            currentDragLabel = createDragLabel(word);
            currentDragLabel->setGeometry(x, y, currentDragLabel->width(), currentDragLabel->height());
            currentDragLabel->show();
            currentDragLabel->setAttribute(Qt::WA_DeleteOnClose);
        }

        setAcceptDrops(true);
}


void ChordSelector::dragEnterEvent(QDragEnterEvent *event)
{
        if (event->mimeData()->hasText()) {
            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();
            } else {
                event->acceptProposedAction();
            }
        } else {
            event->ignore();
        }
}

void ChordSelector::dropEvent(QDropEvent *event)
{
        if (event->mimeData()->hasText()) {
            const QMimeData *mime = event->mimeData();
            QStringList pieces = mime->text().split(QRegularExpression(QStringLiteral("\\s+")),
                                                    Qt::SkipEmptyParts);
            QPoint position = event->position().toPoint();
            QPoint hotSpot;

            QByteArrayList hotSpotPos = mime->data(hotSpotMimeDataKey()).split(' ');
            if (hotSpotPos.size() == 2) {
                hotSpot.setX(hotSpotPos.first().toInt());
                hotSpot.setY(hotSpotPos.last().toInt());
            }

            for (const QString &piece : pieces) {
                QLabel *newLabel = createDragLabel(piece, this);
                newLabel->move(position - hotSpot);
                newLabel->show();
                newLabel->setAttribute(Qt::WA_DeleteOnClose);

                position += QPoint(newLabel->width(), 0);
            }

            if (event->source() == this) {
                event->setDropAction(Qt::MoveAction);
                event->accept();
            } else {
                event->acceptProposedAction();
            }
        }
}

void ChordSelector::mousePressEvent(QMouseEvent *event)
{
        QLabel *child = qobject_cast<QLabel*>(childAt(event->position().toPoint()));
        if (!child)
            return;

        // Delete the previous dragLabel, if any
        if (currentDragLabel) {
            currentDragLabel->deleteLater();
            currentDragLabel = nullptr;
        }

        QPoint hotSpot = event->position().toPoint() - child->pos();

        QMimeData *mimeData = new QMimeData;
        mimeData->setText(child->text());
        mimeData->setData(hotSpotMimeDataKey(),
                          QByteArray::number(hotSpot.x()) + ' ' + QByteArray::number(hotSpot.y()));

        qreal dpr = window()->windowHandle()->devicePixelRatio();
        QPixmap pixmap(child->size() * dpr);
        pixmap.setDevicePixelRatio(dpr);
        child->render(&pixmap);

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(hotSpot);

        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

        if (dropAction == Qt::MoveAction)
            child->close();
}
void ChordSelector::onTypeClicked(QListWidgetItem* item) {

    if (item->text() == "Major") {
        stackedWidget->setCurrentIndex(2);
    } else if (item->text() == "Minor") {
        stackedWidget->setCurrentIndex(3);
    }
    //Need to do rest
}

void ChordSelector::onBackClicked() {
    int currentIndex = stackedWidget->currentIndex();
    if (currentIndex > 0 && currentIndex != stackedWidget->count() - 1) {
        stackedWidget->setCurrentIndex(currentIndex - 1);
    } else {
        stackedWidget->setCurrentIndex(0);
        chordBox->setReadOnly(true);

    }
}

void ChordSelector::initializeNotes() {
    QStringList notes = {"Ab", "A", "A#",
                         "Bb", "B", "B#",
                         "Cb", "C", "C#",
                         "Db", "D", "D#",
                         "Eb", "E", "E#",
                         "Fb", "F", "F#",
                         "Gb", "G", "G#", "CUSTOM"};
    noteListWidget->addItems(notes);
}

void ChordSelector::initializeTypes() {
    QStringList types = {"Major", "Minor", "Diminished",
                         "Dominant", "Suspended", "Augmented",
                         "Extended"};
    typeListWidget->addItems(types);
}

void ChordSelector::onVariationClicked(QListWidgetItem* item) {
    QString chordText = chosenNote + item->text();
    chordBox->setText(chordText);
    putDragLabelOnScreen(chordText);
}

void ChordSelector::initializeMajorVariations() {
    QStringList majorVariations = {"maj", "maj7", "maj9"};
    majorVariationListWidget->addItems(majorVariations);
}

void ChordSelector::initializeMinorVariations() {
    QStringList minorVariations = {"m", "m7", "m9"};
    minorVariationListWidget->addItems(minorVariations);
}

void ChordSelector::initializeBlankList() {
    QStringList blankList = {"Type a custom chord above."};
    blankListWidget->addItems(blankList);
}

