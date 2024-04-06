#include <gtest/gtest.h>
#include <soundex/soundex.hpp>

TEST(SoundexHashTest, BasicTest) {
    EXPECT_EQ(soundex_hash("kitten"), 808792907);
    EXPECT_EQ(soundex_hash("sitting"), 842347347);
    EXPECT_EQ(soundex_hash("riding"), 842347346);
    EXPECT_EQ(soundex_hash("stranger"), 892744531);
}

TEST(SoundexHashTest, VowelTest) {
    EXPECT_EQ(soundex_hash("hello"), 808465480);
    EXPECT_EQ(soundex_hash("world"), 859059799);
    EXPECT_EQ(soundex_hash("wonder"), 909325655);
    EXPECT_EQ(soundex_hash("amazing"), 892482881);
}

TEST(SoundexHashTest, SpecialCharactersTest) {
    EXPECT_EQ(soundex_hash("h2o"), 808464968);
    EXPECT_EQ(soundex_hash("whisper"), 909193815);
    EXPECT_EQ(soundex_hash("whiskey"), 808464983);
    EXPECT_EQ(soundex_hash("whistle"), 875770455);
}
