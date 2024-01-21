#include "chordselector.h"

ChordSelector::ChordSelector(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    noteListWidget = new QListWidget(this);
    connect(noteListWidget, &QListWidget::itemClicked, this, &ChordSelector::onNoteClicked);

    typeListWidget = new QListWidget(this);
    connect(typeListWidget, &QListWidget::itemClicked, this, &ChordSelector::onTypeClicked);

    majorVariationListWidget = new QListWidget(this);

    minorVariationListWidget = new QListWidget(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(noteListWidget);
    stackedWidget->addWidget(typeListWidget);
    stackedWidget->addWidget(majorVariationListWidget);
    stackedWidget->addWidget(minorVariationListWidget);

    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &ChordSelector::onBackClicked);

    mainLayout->addWidget(stackedWidget);
    mainLayout->addWidget(backButton);

    initializeNotes();
    initializeTypes();
    initializeMajorVariations();
    initializeMinorVariations();
}

void ChordSelector::onNoteClicked(QListWidgetItem* item) {
    stackedWidget->setCurrentIndex(1);
}

void ChordSelector::onTypeClicked(QListWidgetItem* item) {
    if (item->text() == "Major") {
        stackedWidget->setCurrentIndex(2);
    } else if (item->text() == "Minor") {
        stackedWidget->setCurrentIndex(3);
    }
}

void ChordSelector::onBackClicked() {
    int currentIndex = stackedWidget->currentIndex();
    if (currentIndex > 0) {
        stackedWidget->setCurrentIndex(currentIndex - 1);
    }
}

void ChordSelector::initializeNotes() {
    QStringList notes = {"Ab", "A", "A#", "Bb", "B", "B#"};
    noteListWidget->addItems(notes);
}

void ChordSelector::initializeTypes() {
    QStringList types = {"Major", "Minor"};
    typeListWidget->addItems(types);
}

void ChordSelector::initializeMajorVariations() {
    QStringList majorVariations = {"maj", "maj7", "maj9"};
    majorVariationListWidget->addItems(majorVariations);
}

void ChordSelector::initializeMinorVariations() {
    QStringList minorVariations = {"m", "min7", "min9"};
    minorVariationListWidget->addItems(minorVariations);
}
