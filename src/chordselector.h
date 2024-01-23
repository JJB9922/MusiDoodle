#ifndef CHORDSELECTOR_H
#define CHORDSELECTOR_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QTextBrowser>

class ChordSelector : public QWidget {
    Q_OBJECT

public:
    ChordSelector(QWidget* parent = nullptr);

private slots:
    void onNoteClicked(QListWidgetItem* item);
    void onTypeClicked(QListWidgetItem* item);
    void onBackClicked();

private:
    void initializeNotes();
    void initializeTypes();
    void initializeMajorVariations();
    void initializeMinorVariations();
    void initializeBlankList();

    QListWidget* noteListWidget;
    QListWidget* typeListWidget;
    QListWidget* majorVariationListWidget;
    QListWidget* minorVariationListWidget;
    QListWidget* blankListWidget;
    QTextBrowser* chordBox;
    QStackedWidget* stackedWidget;
    QPushButton* backButton;
};

#endif
