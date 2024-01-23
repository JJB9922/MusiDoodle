#include "componentfactory.h"
#include "chordselector.h"

#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>

QWidget* LyricsComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* ChordsComponentCreator::FactoryMethod() {
    return new QLineEdit();
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
