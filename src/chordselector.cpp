#include "chordselector.h"

#include <iostream>
#include <QTextBrowser>
#include <QLabel>
#include <QtWidgets>

static const QString HOTSPOT_MIME_TYPE = QStringLiteral("application/x-hotspot");
static const int DRAG_LABEL_X = 150;
static const int DRAG_LABEL_Y = 5;

static const QStringList notes = {"Ab", "A", "A#",
                                  "Bb", "B", "B#",
                                  "Cb", "C", "C#",
                                  "Db", "D", "D#",
                                  "Eb", "E", "E#",
                                  "Fb", "F", "F#",
                                  "Gb", "G", "G#", "CUSTOM"};

static const QStringList types = {"Major", "Minor", "Diminished",
                                  "Dominant", "Suspended", "Augmented",
                                  "Extended"};

const QStringList majorVariations = {"4", "6", "7", "7-9", "9", "maj", "maj7", "maj9"};
const QStringList minorVariations = {"m", "m4", "m6", "m7", "m7-9", "m9", "m", "m7", "m9"};
const QStringList diminishedVariations = {"dim", "dim7"};
const QStringList dominantVariations = {"7", "7b5", "7#5", "9", "11", "13", "7sus4"};
const QStringList suspendedVariations = {"sus2", "sus4", "sus7", "sus9"};
const QStringList augmentedVariations = {"aug", "aug7", "aug9"};
const QStringList extendedVariations = {"9", "11", "13", "maj9", "maj11", "maj13", "m9", "m11", "m13"};

QMap<QString, int> typeIndexMap;

ChordSelector::ChordSelector(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    chordBox = new QLineEdit(this);
    chordBox->setFixedSize(128, 32);
    chordBox->setReadOnly(true);

    noteListWidget = new QListWidget(this);
    connect(noteListWidget, &QListWidget::itemClicked, this, &ChordSelector::onNoteClicked);

    typeListWidget = new QListWidget(this);
    connect(typeListWidget, &QListWidget::itemClicked, this, &ChordSelector::onTypeClicked);

    majorVariationListWidget = new QListWidget(this);
    connect(majorVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    minorVariationListWidget = new QListWidget(this);
    connect(minorVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    dominantVariationListWidget = new QListWidget(this);
    connect(dominantVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    diminishedVariationListWidget = new QListWidget(this);
    connect(diminishedVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    suspendedVariationListWidget = new QListWidget(this);
    connect(suspendedVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    augmentedVariationListWidget = new QListWidget(this);
    connect(augmentedVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    extendedVariationListWidget = new QListWidget(this);
    connect(extendedVariationListWidget, &QListWidget::itemClicked, this, &ChordSelector::onVariationClicked);

    blankListWidget = new QListWidget(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(noteListWidget);
    stackedWidget->addWidget(typeListWidget);
    stackedWidget->addWidget(majorVariationListWidget);
    stackedWidget->addWidget(minorVariationListWidget);
    stackedWidget->addWidget(diminishedVariationListWidget);
    stackedWidget->addWidget(dominantVariationListWidget);
    stackedWidget->addWidget(suspendedVariationListWidget);
    stackedWidget->addWidget(augmentedVariationListWidget);
    stackedWidget->addWidget(extendedVariationListWidget);
    stackedWidget->addWidget(blankListWidget);

    backButton = new QPushButton("Reset", this);
    connect(backButton, &QPushButton::clicked, this, &ChordSelector::onBackClicked);

    mainLayout->addWidget(chordBox);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(backButton);

    initializeNotes();
    initializeTypes();
    initializeVariations();
    initializeBlankList();
}

void ChordSelector::onNoteClicked(QListWidgetItem* item) {
    if (item->text() != "CUSTOM") {
        stackedWidget->setCurrentIndex(1);
        chosenNote = item->text();
        chordBox->setText(chosenNote);

    } else {
        stackedWidget ->setCurrentIndex(stackedWidget->count()-1);
        chordBox->setReadOnly(false);
        putDragLabelOnScreen(chordBox->text());
    }
}

static QString hotSpotMimeDataKey() { return HOTSPOT_MIME_TYPE; }

QLabel* ChordSelector::createDragLabel(const QString& text, QWidget *parent)
{
    std::unique_ptr<QLabel> label = std::make_unique<QLabel>(text, this);
    label->setAutoFillBackground(true);
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Raised);
    return label.release();
}

void ChordSelector::putDragLabelOnScreen(const QString& word){
        if (currentDragLabel) {
            currentDragLabel->deleteLater();
            currentDragLabel = nullptr;
        }

        if (!chordBox->text().isEmpty()) {
            currentDragLabel = createDragLabel(word);
            currentDragLabel->setGeometry(DRAG_LABEL_X, DRAG_LABEL_Y, currentDragLabel->width(), currentDragLabel->height());
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

        if (currentDragLabel) {
            currentDragLabel->deleteLater();
            currentDragLabel = nullptr;
        }

        QPoint hotSpot = event->position().toPoint() - child->pos();

        std::unique_ptr<QMimeData> mimeData = std::make_unique<QMimeData>();
        mimeData->setText(child->text());
        mimeData->setData(hotSpotMimeDataKey(),
                          QByteArray::number(hotSpot.x()) + ' ' + QByteArray::number(hotSpot.y()));

        qreal dpr = window()->windowHandle()->devicePixelRatio();
        QPixmap pixmap(child->size() * dpr);
        pixmap.setDevicePixelRatio(dpr);
        child->render(&pixmap);

        std::unique_ptr<QDrag> drag = std::make_unique<QDrag>(this);
        drag->setMimeData(mimeData.release());
        drag->setPixmap(pixmap);
        drag->setHotSpot(hotSpot);

        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

        if (dropAction == Qt::MoveAction)
            child->close();
}

void ChordSelector::onTypeClicked(QListWidgetItem* item) {
        int j = 2;
        for (const QString& type : types) {
            typeIndexMap.insert(type, j++);
        }

        const QString& itemType = item->text();

        if (typeIndexMap.contains(itemType)) {
            stackedWidget->setCurrentIndex(typeIndexMap.value(itemType));
        }
}

void ChordSelector::onBackClicked() {
    stackedWidget->setCurrentIndex(0);
    chordBox->clear();
    chordBox->setReadOnly(true);
}

void ChordSelector::initializeNotes() {
    noteListWidget->addItems(notes);
}

void ChordSelector::initializeTypes() {
    typeListWidget->addItems(types);
}

void ChordSelector::onVariationClicked(QListWidgetItem* item) {
    QString chordText = chosenNote + item->text();
    chordBox->setText(chordText);
    putDragLabelOnScreen(chordText);
}

void ChordSelector::initializeVariations() {
    majorVariationListWidget->addItems(majorVariations);
    minorVariationListWidget->addItems(minorVariations);
    diminishedVariationListWidget->addItems(diminishedVariations);
    dominantVariationListWidget->addItems(dominantVariations);
    suspendedVariationListWidget->addItems(suspendedVariations);
    augmentedVariationListWidget->addItems(augmentedVariations);
    extendedVariationListWidget->addItems(extendedVariations);
}


void ChordSelector::initializeBlankList() {
    QStringList blankList = {"Type a custom chord above."};
    blankListWidget->addItems(blankList);
}

