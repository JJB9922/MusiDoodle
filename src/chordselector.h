#ifndef CHORDSELECTOR_H
#define CHORDSELECTOR_H

#include "dropwidget.h"

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
    friend class ChordSelectorTest;
    QString chosenNote;


public slots:
    void onNoteClicked(QListWidgetItem* note);

private slots:
    void onTypeClicked(QListWidgetItem* item);
    void onVariationClicked(QListWidgetItem* item);
    void onResetClicked();
    void deleteLabel(const QString &text);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void ConnectWidgets();
    void InitializeChordSelector();
    QLabel* CreateDragLabel(const QString& text, QWidget* parent = nullptr);
    void PutDragLabelOnScreen(const QString& word);


    QLabel* currentDragLabel = nullptr;

    DropWidget* dropWidget;
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
