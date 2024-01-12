#ifndef NEWCOMPONENTPICKER_H
#define NEWCOMPONENTPICKER_H

#include <QDialog>
#include <QString>  // Include this header for QString

namespace Ui {
class NewComponentPicker;
}

class NewComponentPicker : public QDialog
{
    Q_OBJECT

public:
    explicit NewComponentPicker(QWidget *parent = nullptr);
    ~NewComponentPicker();

    QString getSelectedComponentType() const;

private slots:
    void on_lyricComponentButton_clicked();
    void on_chordComponentButton_clicked();
    void on_notebookComponentButton_clicked();
    void on_tabComponentButton_clicked();
    void on_sheetMusicComponentButton_clicked();

private:
    Ui::NewComponentPicker *ui;
    QString selectedComponentType;
};

#endif // NEWCOMPONENTPICKER_H
