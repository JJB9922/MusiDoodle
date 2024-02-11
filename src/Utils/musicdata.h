#ifndef MUSICDATA_H
#define MUSICDATA_H

#include <QString>
#include <QStringList>
#include <QRegularExpression>

/**
 * The {@code MusicData} class provides a singleton instance containing static
 * data related to music notes, types, and variations.
 * It follows the singleton pattern to ensure a single instance of the class.
 */
class MusicData {
public:
    /**
     * Gets the singleton instance of the {@code MusicData} class.
     *
     * @return The singleton instance.
     */
    static MusicData& getInstance() {
        static MusicData instance;
        return instance;
    }

    /**
     * List of musical notes including natural and altered notes.
     */
    const QStringList notes = {"Ab", "A", "A#",
                               "Bb", "B", "B#",
                               "Cb", "C", "C#",
                               "Db", "D", "D#",
                               "Eb", "E", "E#",
                               "Fb", "F", "F#",
                               "Gb", "G", "G#", "CUSTOM"};

    /**
     * List of musical types such as Major, Minor, Diminished, etc.
     */
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
    /**
     * Private default constructor to enforce singleton pattern.
     */
    MusicData() = default;

    /**
     * Disable copy constructor.
     */
    MusicData(const MusicData&) = delete;

    /**
     * Disable assignment operator.
     */
    MusicData& operator=(const MusicData&) = delete;
};

#endif // MUSICDATA_H
