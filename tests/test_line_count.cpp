#include <gtest/gtest.h>

#include <string>

#include "head.hpp"
#include "test_helpers.hpp"

TEST(LineCount, ReturnsMinusOneForMissingFile) {
    EXPECT_EQ(lineCount("/path/that/does/not/exist/libcvault_missing.txt"), -1L);
}

TEST(LineCount, ReturnsZeroForEmptyFile) {
    libcvault_test::TempDir tmp;
    const auto path = tmp.path / "empty.txt";
    libcvault_test::write_text_file(path, "");
    EXPECT_EQ(lineCount(path.string().c_str()), 0L);
}

TEST(LineCount, CountsSingleLineWithAndWithoutNewline) {
    libcvault_test::TempDir tmp;
    const auto no_newline = tmp.path / "single_no_nl.txt";
    const auto with_newline = tmp.path / "single_with_nl.txt";
    libcvault_test::write_text_file(no_newline, "hello");
    libcvault_test::write_text_file(with_newline, "hello\n");
    EXPECT_EQ(lineCount(no_newline.string().c_str()), 1L);
    EXPECT_EQ(lineCount(with_newline.string().c_str()), 1L);
}

TEST(LineCount, CountsMultipleLinesAndBlankLines) {
    libcvault_test::TempDir tmp;
    const auto unix = tmp.path / "multi.txt";
    const auto no_trailing = tmp.path / "multi_no_trailing.txt";
    const auto blanks = tmp.path / "blanks.txt";
    libcvault_test::write_text_file(unix, "one\ntwo\nthree\n");
    libcvault_test::write_text_file(no_trailing, "one\ntwo\nthree");
    libcvault_test::write_text_file(blanks, "a\n\nb\n");
    EXPECT_EQ(lineCount(unix.string().c_str()), 3L);
    EXPECT_EQ(lineCount(no_trailing.string().c_str()), 3L);
    EXPECT_EQ(lineCount(blanks.string().c_str()), 3L);
}
