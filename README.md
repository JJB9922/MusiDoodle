# MusiDoodle
MusiDoodle is a comprehensive and user-friendly application designed for creating and editing musical compositions. The main interface revolves around an intuitive environment for users to build and modify their music, which are loaded and saved as tracks.

Upon launching the program, users are greeted with a title screen allowing them to start a track, load a track or quit. They also have a "Recent Tracks" tree. The other main view is the track editor window, that serves as the central hub for composing music. The window offers various functionalities, including the ability to add music track components in a very modular fashion - including such as lyrics, chords, and a notebook. Users can easily access these components through a dedicated component picker modal dialog, triggered by a "+" button. There is further scope for "tab" and "sheet music" components, however they're a bit further off.

The program will also attempt to guide users through music theory. E.g., there is a chord picker box that allows users to discover chords at its most basic functionality. Eventually, the program could highlight what chords "fit" together, providing some gentle theory-backed nudging toward theoretical cohesion when building a track. However, it is very important that none of this is strict - it is meant to increase speed, but not hamper creativity and experimentation.

Creating a component manages the layout and visibility of the newly created component, ensuring a cohesive and visually appealing arrangement. Additionally, it hides the triggering button and introduces a new button beneath the added component, allowing users to effortlessly continue building their composition with a simplistic UI/UX.

The program leverages the power of Qt, a powerful C++ framework, to create a responsive and interactive user interface. With features like drag-and-drop functionality, the application streamlines the creative process for users. Any further streamlining is top priority. Efficiency and speedy notation of music is the main aim of this program.

## Stack
C++ & Qt.
CMake for builds.
Doxygen for documentation.
Gtest for testing.
