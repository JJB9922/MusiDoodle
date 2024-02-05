#include "chordselector.h"
#include "musicdata.h"

#include <iostream>
#include <QTextBrowser>
#include <QLabel>
#include <QtWidgets>

MusicData& musicData = MusicData::getInstance();
QMap<QString, int> typeIndexMap;
QString hotSpotMimeDataKey() { return QStringLiteral("application/x-hotspot"); }
QRegularExpression regex(QStringLiteral("\\s+"));

/**
 * @brief ChordSelector::ChordSelector
 *
 * Constructs a ChordSelector widget.
 *
 * Initializes the ChordSelector widget with a vertical layout, QLineEdit for chord display,
 * QListWidgets for note, type, and variation selection, a QStackedWidget to manage different
 * selection views, and a QPushButton to reset the widget to its default state.
 *
 * Connects signals from QListWidgets to corresponding slots for handling item clicks.
 *
 * Calls initializeChordSelector() to populate QListWidgets with predefined data.
 *
 * @param parent The parent widget.
 */
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
    connect(backButton, &QPushButton::clicked, this, &ChordSelector::onResetClicked);

    mainLayout->addWidget(chordBox);
    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(backButton);

    initializeChordSelector();
}

/**
 * @brief ChordSelector::initializeChordSelector
 *
 * Initialises the chord selector, which is a stacked widget.
 *
 * Adds each item (notes, types and variations) to the appropriate parts of the widget.
 */
void ChordSelector::initializeChordSelector() {
    noteListWidget->addItems(musicData.notes);
    typeListWidget->addItems(musicData.types);

    majorVariationListWidget->addItems(musicData.majorVariations);
    minorVariationListWidget->addItems(musicData.minorVariations);
    diminishedVariationListWidget->addItems(musicData.diminishedVariations);
    dominantVariationListWidget->addItems(musicData.dominantVariations);
    suspendedVariationListWidget->addItems(musicData.suspendedVariations);
    augmentedVariationListWidget->addItems(musicData.augmentedVariations);
    extendedVariationListWidget->addItems(musicData.extendedVariations);

    QStringList blankList = {"Type a custom chord above."};
    blankListWidget->addItems(blankList);
}

/**
 * @brief ChordSelector::onResetClicked
 *
 * Will reset the stacked widget back to it's default state.
 *
 * Also clears the chord box.
 */
void ChordSelector::onResetClicked() {
    stackedWidget->setCurrentIndex(0);
    chordBox->clear();
    chordBox->setReadOnly(true);

    if (currentDragLabel) {
        currentDragLabel->deleteLater();
        currentDragLabel = nullptr;
    }
}

/**
 * @brief ChordSelector::onNoteClicked
 *
 * Advances the stacked widget to the types list if a note is clicked.
 *
 * Sends user to "custom" note page if "CUSTOM" is picked.
 *
 * @param note The item (note) that was clicked
 */
void ChordSelector::onNoteClicked(QListWidgetItem* note) {
    if (note->text() != "CUSTOM") {
        stackedWidget->setCurrentIndex(1);
        chosenNote = note->text();
        chordBox->setText(chosenNote);

    } else {
        stackedWidget ->setCurrentIndex(stackedWidget->count()-1);
        chordBox->setReadOnly(false);
        putDragLabelOnScreen(chordBox->text());
    }
}

/**
 * @brief ChordSelector::onTypeClicked
 *
 * Handles the event when a chord type is clicked in the ChordSelector widget.
 *
 * Assigns numerical indices to chord types using a QMap, then sets the current index
 * of the QStackedWidget based on the selected chord type. This method is connected
 * to the QListWidget's itemClicked signal for chord type selection.
 *
 * @param item The QListWidgetItem representing the clicked chord type.
 */
void ChordSelector::onTypeClicked(QListWidgetItem* item) {
    int j = 2;
    for (const QString& type : musicData.types) {
        typeIndexMap.insert(type, j++);
    }

    const QString& itemType = item->text();

    if (typeIndexMap.contains(itemType)) {
        stackedWidget->setCurrentIndex(typeIndexMap.value(itemType));
    }
}

/**
 * @brief ChordSelector::onVariationClicked
 *
 * Combines the chosen note with the selected chord variation to form a complete chord text.
 * Updates the chord display QLineEdit with the newly formed chord text.
 * Calls putDragLabelOnScreen to visualize the chord in a draggable label.
 *
 * This method is connected to the QListWidget's itemClicked signal for chord variation selection.
 *
 * @param item The QListWidgetItem representing the clicked chord variation.
 */
void ChordSelector::onVariationClicked(QListWidgetItem* item) {
    QString chordText = chosenNote + item->text();
    chordBox->setText(chordText);
    putDragLabelOnScreen(chordText);
}

/**
 * Creates a draggable QLabel for visualizing chord variations during drag-and-drop operations.
 *
 * @param text The text content of the label, representing the chord variation.
 * @param parent The parent widget for the created QLabel.
 * @return A pointer to the newly created QLabel.
 */
QLabel* ChordSelector::createDragLabel(const QString& text, QWidget *parent)
{
    QLabel* label = new QLabel(text, this);
    label->setAutoFillBackground(true);
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Raised);
    return label;
}

/**
 * @brief ChordSelector::putDragLabelOnScreen
 *
 * Displays a draggable label on the screen to visualize a chord variation during drag-and-drop operations.
 *
 * If a previous drag label exists, it is deleted before creating a new one.
 * If the chord display is not empty, a new QLabel is created using the createDragLabel method
 * with the provided chord variation text. The QLabel is then positioned on the screen.
 * Finally, setAcceptDrops is called to enable dropping operations on the ChordSelector widget - this is for testing at the mo, and won't be included later.
 *
 * @param word The text content of the chord variation to be visualized.
 */
void ChordSelector::putDragLabelOnScreen(const QString& word){
        int DRAG_LABEL_X = 150;
        int DRAG_LABEL_Y = 5;

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

/**
 * @brief ChordSelector::dragEnterEvent
 *
 * Handles the drag enter event for the ChordSelector widget during drag-and-drop operations.
 *
 * Determines whether the dragged data contains text. If true:
 * - If the source of the drag event is this widget, sets the drop action to Qt::MoveAction and accepts the event.
 * - If the source is not this widget, accepts the proposed action.
 * If the dragged data does not contain text, ignores the event.
 *
 * @param event The QDragEnterEvent representing the drag enter event.
 */
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

/**
 * @brief ChordSelector::dropEvent
 *
 * Handles the drop event for the ChordSelector widget during drag-and-drop operations.
 *
 * Checks if the dropped data contains text. If true:
 * - Retrieves the MIME data and splits it into pieces using the provided regex pattern.
 * - Processes the position and hot spot of the drop event.
 * - Creates QLabel widgets for each piece of text, positions them accordingly, and displays them.
 * - If the source of the drop event is this widget, sets the drop action to Qt::MoveAction and accepts the event.
 * - If the source is not this widget, accepts the proposed action.
 *
 * @param event The QDropEvent representing the drop event.
 */
void ChordSelector::dropEvent(QDropEvent *event)
{

        if (event->mimeData()->hasText()) {
            const QMimeData *mime = event->mimeData();
            QStringList pieces = mime->text().split(regex, Qt::SkipEmptyParts);
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

/**
 * @brief ChordSelector::mousePressEvent
 *
 * Handles the mouse press event for the ChordSelector widget.
 *
 * Retrieves the child QLabel at the mouse press position. If no child is found, the method returns.
 * Deletes the existing currentDragLabel if present.
 * Computes the hot spot position based on the difference between the mouse position and the child's position.
 * Creates a unique QMimeData object with the text content of the child and the hot spot information.
 * Renders the child QLabel into a QPixmap to use as the drag pixmap.
 * Creates a unique QDrag object, sets its properties, and executes the drag operation.
 * If the drop action is Qt::MoveAction, closes the child QLabel.
 *
 * @param event The QMouseEvent representing the mouse press event.
 */
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


