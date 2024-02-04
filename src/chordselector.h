#ifndef CHORDSELECTOR_H
#define CHORDSELECTOR_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QStackedWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QLabel>

class ChordSelector : public QWidget {
    Q_OBJECT

public:
    ChordSelector(QWidget* parent = nullptr);
    QStackedWidget* getStackedWidget() const { return stackedWidget; }
    QLineEdit* getChordBox() const { return chordBox; }
    friend class ChordSelectorTest;
    QString chosenNote;

public slots:
    void onNoteClicked(QListWidgetItem* item);

private slots:

    void onTypeClicked(QListWidgetItem* item);
    void onVariationClicked(QListWidgetItem* item);
    void onBackClicked();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void initializeNotes();
    void initializeTypes();
    void initializeVariations();
    void initializeBlankList();
    QLabel* createDragLabel(const QString& text, QWidget* parent = nullptr);
    void putDragLabelOnScreen(const QString& word);

    QLabel* currentDragLabel = nullptr;

    QListWidget* noteListWidget;
    QListWidget* typeListWidget;
    QListWidget* majorVariationListWidget;
    QListWidget* minorVariationListWidget;
    QListWidget* diminishedVariationListWidget;
    QListWidget* dominantVariationListWidget;
    QListWidget* suspendedVariationListWidget;
    QListWidget* augmentedVariationListWidget;
    QListWidget* extendedVariationListWidget;
    QListWidget* blankListWidget;
    QLineEdit* chordBox;
    QStackedWidget* stackedWidget;
    QPushButton* backButton;
};

#endif
