#include "chordselector.h"

#include <QTextBrowser>

ChordSelector::ChordSelector(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    chordBox = new QTextBrowser(this);
    chordBox->setFixedSize(128, 32);

    noteListWidget = new QListWidget(this);
    connect(noteListWidget, &QListWidget::itemClicked, this, &ChordSelector::onNoteClicked);

    typeListWidget = new QListWidget(this);
    connect(typeListWidget, &QListWidget::itemClicked, this, &ChordSelector::onTypeClicked);

    majorVariationListWidget = new QListWidget(this);
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
}

void ChordSelector::onNoteClicked(QListWidgetItem* item) {
    if (item->text() != "CUSTOM") {
        stackedWidget->setCurrentIndex(1);
        chordBox->setText(item->text());
    } else {
        stackedWidget ->setCurrentIndex(stackedWidget->count()-1);
        chordBox->setReadOnly(false);
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

