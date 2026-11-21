#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "head.hpp"
#include "test_helpers.hpp"

namespace fs = std::filesystem;

TEST(SearchFile, FindsFilesByRelativeName) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "root.txt", 12);
    libcvault_test::write_bytes_file(tmp.path / "dir" / "nested.txt", 34);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    EXPECT_EQ(searchFile("root.txt"), 12LL);
    const std::string nested = (fs::path("dir") / "nested.txt").string();
    EXPECT_EQ(searchFile(nested.c_str()), 34LL);
}

TEST(SearchFile, ReturnsNotFoundForMissingOrNull) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "present.txt", 5);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    EXPECT_EQ(searchFile("missing.txt"), -3LL);
    EXPECT_EQ(searchFile(nullptr), -3LL);
}

TEST(SearchFile, WorksAfterSortingFileList) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "b.txt", 20);
    libcvault_test::write_bytes_file(tmp.path / "a.txt", 10);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    sortFileOnByte();
    EXPECT_EQ(searchFile("a.txt"), 10LL);
    EXPECT_EQ(searchFile("b.txt"), 20LL);

    sortFileOnName();
    EXPECT_EQ(searchFile("a.txt"), 10LL);
    EXPECT_EQ(searchFile("b.txt"), 20LL);
}
