#include "componentfactory.h"
#include "component.h"

#include <QLineEdit>

QWidget* LyricsComponentCreator::FactoryMethod() {
    return new QLineEdit();
}

QWidget* ChordsComponentCreator::FactoryMethod() {

}

QWidget* NotebookComponentCreator::FactoryMethod() {

}

QWidget* TabComponentCreator::FactoryMethod() {

}

QWidget* SheetMusicComponentCreator::FactoryMethod() {

}
