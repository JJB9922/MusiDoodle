#ifndef CHORDSELECTOR_H
#define CHORDSELECTOR_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QLabel>

class ChordSelector : public QWidget {
    Q_OBJECT

public:
    ChordSelector(QWidget* parent = nullptr);


private slots:
    void onNoteClicked(QListWidgetItem* item);
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
    void initializeMajorVariations();
    void initializeMinorVariations();
    void initializeBlankList();
    QLabel* createDragLabel(const QString& text, QWidget* parent = nullptr);
    void putDragLabelOnScreen(const QString& word);

    QString chosenNote;

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
