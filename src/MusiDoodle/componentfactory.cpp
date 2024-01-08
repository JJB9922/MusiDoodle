#include "componentfactory.h"
#include "component.h"

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
}

Component* TabComponentCreator::FactoryMethod() {
    return new TabComponent();
}

Component* SheetMusicComponentCreator::FactoryMethod() {
    return new SheetMusicComponent();
}
