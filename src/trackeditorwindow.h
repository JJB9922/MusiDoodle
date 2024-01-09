#ifndef TRACKEDITORWINDOW_H
#define TRACKEDITORWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QtWidgets>

#include "componentfactory.h"

namespace Ui {
class TrackEditorWindow;
}

class TrackEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrackEditorWindow(QWidget *parent = nullptr);
    ~TrackEditorWindow();

public slots:
    void saveToFile();
    void createComponent(ComponentFactory* componentCreator);

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();

    void on_addComponentButton_clicked();

private:
    Ui::TrackEditorWindow *ui;
    QAction *actionSave_As;
};

#endif // TRACKEDITORWINDOW_H
