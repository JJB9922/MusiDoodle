#ifndef NEWCOMPONENTPICKER_H
#define NEWCOMPONENTPICKER_H

#include <QDialog>

namespace Ui {
class NewComponentPicker;
}

class NewComponentPicker : public QDialog
{
    Q_OBJECT

public:
    explicit NewComponentPicker(QWidget *parent = nullptr);
    ~NewComponentPicker();

private:
    Ui::NewComponentPicker *ui;
};

#endif // NEWCOMPONENTPICKER_H
