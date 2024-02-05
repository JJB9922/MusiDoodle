#ifndef MUSICDATA_H
#define MUSICDATA_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

class MusicData {
public:
    static MusicData& getInstance() {
        static MusicData instance;
        return instance;
    }

    const QStringList notes = {"Ab", "A", "A#",
                               "Bb", "B", "B#",
                               "Cb", "C", "C#",
                               "Db", "D", "D#",
                               "Eb", "E", "E#",
                               "Fb", "F", "F#",
                               "Gb", "G", "G#", "CUSTOM"};

    const QStringList types = {"Major", "Minor", "Diminished",
                               "Dominant", "Suspended", "Augmented",
                               "Extended"};

    const QStringList majorVariations = {"4", "6", "7", "7-9", "9", "maj", "maj7", "maj9"};
    const QStringList minorVariations = {"m", "m4", "m6", "m7", "m7-9", "m9", "m", "m7", "m9"};
    const QStringList diminishedVariations = {"dim", "dim7"};
    const QStringList dominantVariations = {"7", "7b5", "7#5", "9", "11", "13", "7sus4"};
    const QStringList suspendedVariations = {"sus2", "sus4", "sus7", "sus9"};
    const QStringList augmentedVariations = {"aug", "aug7", "aug9"};
    const QStringList extendedVariations = {"9", "11", "13", "maj9", "maj11", "maj13", "m9", "m11", "m13"};

private:
    MusicData() = default;

    MusicData(const MusicData&) = delete;
    MusicData& operator=(const MusicData&) = delete;
};

#endif // MUSICDATA_H
