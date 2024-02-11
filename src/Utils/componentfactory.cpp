#include "componentfactory.h"

#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QStackedWidget>

/**
 * @brief Factory method for creating a new instance of a QLineEdit widget.
 *
 * This method is part of the LyricsComponentCreator class, which serves as a factory for creating
 * various widgets related to lyrics components. It specifically creates and returns a new instance of
 * a QLineEdit widget.
 *
 * @return A pointer to the newly created QLineEdit widget.
 */
QWidget* LyricsComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* ChordsComponentCreator::FactoryMethod() {
    return new DropWidget();
}

QWidget* NotebookComponentCreator::FactoryMethod() {
    return new QTextEdit();
}

QWidget* TabComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* SheetMusicComponentCreator::FactoryMethod() {
    return new QLineEdit();
}
