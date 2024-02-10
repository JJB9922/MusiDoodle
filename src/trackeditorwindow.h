#ifndef TRACKEDITORWINDOW_H
#define TRACKEDITORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidget>
#include "newcomponentpicker.h"
#include "componentfactory.h"
#include "iserializable.h"

namespace Ui {
class TrackEditorWindow;
}

class TrackEditorWindow : public QMainWindow, public ISerializable
{
    Q_OBJECT

public:
    TrackEditorWindow(QWidget *parent = nullptr);
    ~TrackEditorWindow();
    void serialize(QDataStream& out) const override {
        out << "Test";
    }

private slots:
    void on_actionQuit_triggered();
    void on_actionSave_As_triggered();
    void showNewComponentPicker();  // Declaration of the new slot

private:
    void saveToFile();
    void createComponent(QWidget *componentToUse, QString selectedComponentType);

    Ui::TrackEditorWindow *ui;
    QWidget* componentToUse;
};

#endif // TRACKEDITORWINDOW_H
