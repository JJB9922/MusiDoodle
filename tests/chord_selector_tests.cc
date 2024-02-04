#include <gtest/gtest.h>
#include "../src/chordselector.h"

class ChordSelectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        chordSelector = new ChordSelector();
    }

    void TearDown() override {
        delete chordSelector;
    }

    ChordSelector* chordSelector;
};

TEST_F(ChordSelectorTest, NoteClickedNonCustom) {
    QListWidgetItem* item = new QListWidgetItem("A");
    chordSelector->onNoteClicked(item);

    EXPECT_EQ(chordSelector->getStackedWidget()->currentIndex(), 1);

    EXPECT_EQ(chordSelector->chosenNote, "A");

    EXPECT_EQ(chordSelector->getChordBox()->text(), "A");
}

TEST_F(ChordSelectorTest, NoteClickedCustom) {
    QListWidgetItem* item = new QListWidgetItem("CUSTOM");
    chordSelector->onNoteClicked(item);

    EXPECT_EQ(chordSelector->getStackedWidget()->currentIndex(), chordSelector->getStackedWidget()t->count() - 1);

    EXPECT_TRUE(chordSelector->getChordBox()->isReadOnly());
}