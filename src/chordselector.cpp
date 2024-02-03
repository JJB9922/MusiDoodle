#include "chordselector.h"

#include <iostream>
#include <QTextBrowser>
#include <QLabel>

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
        // HERE !
    } else {
        stackedWidget ->setCurrentIndex(stackedWidget->count()-1);
        chordBox->setReadOnly(false);
    }
}

QLabel* ChordSelector::createDragLabel(QString& text)
{
    QLabel *label = new QLabel(text, this);
    label->setAutoFillBackground(true);
    label->setFrameShape(QFrame::Panel);
    label->setFrameShadow(QFrame::Raised);
    return label;
}

void ChordSelector::putDragLabelOnScreen(QString* word){
    int x = 5;
    int y = 5;

    if (!chordBox->toPlainText().isEmpty()) {
        QLabel* wordLabel = createDragLabel(*word);
        wordLabel->setGeometry(x, y, wordLabel->width(), wordLabel->height());
        wordLabel->show();
        wordLabel->setAttribute(Qt::WA_DeleteOnClose);
        x += wordLabel->width() + 2;
        if (x >= 245) {
            x = 5;
            y += wordLabel->height() + 2;
            }
        }
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
    chordBox->setText(chosenNote + item->text());
    QString* chordText = new QString(chosenNote + item->text());
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

