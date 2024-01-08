#include "component.h"
#include <iostream>

Component::Component() {
    std::cout << "Component Created!" << std::endl;
}

LyricsComponent::LyricsComponent() {
    std::cout << "Lyrics Component Created!" << std::endl;
}

ChordsComponent::ChordsComponent() {
    std::cout << "Chords Component Created!" << std::endl;
}

NotebookComponent::NotebookComponent() {
    std::cout << "Notebook Component Created!" << std::endl;
}

TabComponent::TabComponent() {
    std::cout << "Tab Component Created!" << std::endl;
}

SheetMusicComponent::SheetMusicComponent() {
    std::cout << "Sheet Music Component Created!" << std::endl;
}
