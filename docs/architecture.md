classDiagram
  class App {
    + start()
  }

  class HomePage {
    + createTrack()
    + loadTrack()
    + viewRecentTracks()
    + quit()
  }

  class NewTrackScreen {
    + showComponentsModal()
  }

  interface ComponentFactory {
    + createComponent(type: ComponentType) : Component
  }

  enum ComponentType {
    LYRIC
    NOTEBOOK
    CHORDS
    TABS
    SHEET_MUSIC
  }

  class Component {
    + display()
  }

  class LyricsComponent {
    + display()
  }

  class NotebookComponent {
    + display()
  }

  class ChordsComponent {
    + display()
  }

  class TabsComponent {
    + display()
  }

  class SheetMusicComponent {
    + display()
  }

  App --> HomePage
  App --> NewTrackScreen
  NewTrackScreen --> ComponentFactory
  NewTrackScreen --> Component
  ComponentFactory --> Component
  Component --> LyricsComponent
  Component --> NotebookComponent
  Component --> ChordsComponent
  Component --> TabsComponent
  Component --> SheetMusicComponent
