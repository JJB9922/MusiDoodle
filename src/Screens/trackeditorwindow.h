#ifndef TRACKEDITORWINDOW_H
#define TRACKEDITORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include "newcomponentpicker.h"
#include "../Utils/componentfactory.h"
#include "../QTUiFiles/ui_trackeditorwindow.h"
#include "../Components/chordselector.h"
#include "../Utils/tracksavedata.h"

namespace Ui {
class TrackEditorWindow;
}

class TrackEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    TrackEditorWindow(QWidget *parent = nullptr);
    ~TrackEditorWindow();
    void loadTrackData(QDataStream file);

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();
    void showNewComponentPicker();

    void on_actionMain_Menu_triggered();

private:
    void saveToFile();
    void createComponent(QWidget *componentToUse, QString selectedComponentType);
    void assignAndCreateSelectedComponent(QString selectedComponentType);

    Ui::TrackEditorWindow *ui;
    QWidget* componentToUse;
    QMainWindow *mainWindow;
    std::vector<QString> addedWidgets;
    QVector<QWidget*> addedComponents;
};

#endif // TRACKEDITORWINDOW_H
