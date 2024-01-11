#include "componentfactory.h"
#include "component.h"

#include <iostream>
#include <qlineedit.h>
#include <qtextedit.h>

//To create a component:
// ComponentFactory* componentCreator = new LyricsComponentCreator();
// componentCreator->CreateComponent();

Component* LyricsComponentCreator::FactoryMethod() {
    return new LyricsComponent();
}

Component* ChordsComponentCreator::FactoryMethod() {
    return new ChordsComponent();
}

Component* NotebookComponentCreator::FactoryMethod() {
    return new NotebookComponent();
    QTextEdit *notebookEditor = new QTextEdit();
}

Component* TabComponentCreator::FactoryMethod() {
    return new TabComponent();
}

Component* SheetMusicComponentCreator::FactoryMethod() {
    return new SheetMusicComponent();
}
