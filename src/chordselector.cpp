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
}

void ChordSelector::onNoteClicked(QListWidgetItem* item) {
    if (item->text() != "CUSTOM") {
        stackedWidget->setCurrentIndex(1);
        chosenNote = item->text();
        chordBox->setText(chosenNote);
    } else {
        stackedWidget ->setCurrentIndex(stackedWidget->count()-1);
        chordBox->setReadOnly(false);
    }
}

void ChordSelector::onTypeClicked(QListWidgetItem* item) {
    QString text = item->text();
    switch (text) {
      case "Major":
        stackedWidget->setCurrentIndex(2);
        break;
      case "Minor":
        stackedWidget->setCurrentIndex(3);
        break;
      case "Diminished":
        stackedWidget->setCurrentIndex(4);
        break;
      case "Dominant":
        stackedWidget->setCurrentIndex(5);
        break;
      case "Suspended":
        stackedWidget->setCurrentIndex(6);
        break;
      case "Augmented":
        stackedWidget->setCurrentIndex(7);
        break;
      case "Extended":
        stackedWidget->setCurrentIndex(8);
        break;
      default:
        std::cerr << "Wtf? chordselector initial sel" << std::endl;
        break;
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
}

void ChordSelector::initializeMajorVariations() {
    QStringList majorVariations = {"maj", "maj6", "maj7", "maj9", "maj7-9", "4", "7", "7-9" };
    majorVariationListWidget->addItems(majorVariations);
}

void ChordSelector::initializeMinorVariations() {
    QStringList minorVariations = {"m", "m7", "m9", "m7-9"};
    minorVariationListWidget->addItems(minorVariations);
}

void ChordSelector::initializeBlankList() {
    QStringList blankList = {"Type a custom chord above."};
    blankListWidget->addItems(blankList);
}

