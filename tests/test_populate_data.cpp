#include <gtest/gtest.h>

#include <filesystem>
#include <string>

#include "head.hpp"
#include "test_helpers.hpp"

namespace fs = std::filesystem;

TEST(PopulateData, ReturnsErrorForMissingPath) {
    EXPECT_EQ(populateData("/path/that/does/not/exist/libcvault_missing"), -1);
}

TEST(PopulateData, ReturnsErrorForFilePath) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_text_file(tmp.path / "file.txt", "hello");
    EXPECT_EQ(populateData((tmp.path / "file.txt").string().c_str()), -2);
}

TEST(PopulateData, LoadsRegularFilesRecursivelyWithRelativeNames) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "a.txt", 3);
    libcvault_test::write_bytes_file(tmp.path / "sub" / "b.bin", 5);
    libcvault_test::write_bytes_file(tmp.path / "sub" / "nested" / "c.dat", 7);

    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
    EXPECT_EQ(getFileCount(), 3);
    EXPECT_EQ(getTotalBytes(), 15LL);

    EXPECT_EQ(searchFile("a.txt"), 3LL);
    EXPECT_EQ(searchFile((fs::path("sub") / "b.bin").string().c_str()), 5LL);
    EXPECT_EQ(searchFile((fs::path("sub") / "nested" / "c.dat").string().c_str()), 7LL);
}

TEST(PopulateData, ClearsPreviousResultsOnNewScan) {
    libcvault_test::TempDir first;
    libcvault_test::write_bytes_file(first.path / "old.txt", 10);
    ASSERT_EQ(populateData(first.path.string().c_str()), 0);
    EXPECT_EQ(getFileCount(), 1);
    EXPECT_EQ(searchFile("old.txt"), 10LL);

    libcvault_test::TempDir second;
    libcvault_test::write_bytes_file(second.path / "new.txt", 4);
    ASSERT_EQ(populateData(second.path.string().c_str()), 0);
    EXPECT_EQ(getFileCount(), 1);
    EXPECT_EQ(getTotalBytes(), 4LL);
    EXPECT_EQ(searchFile("new.txt"), 4LL);
    EXPECT_EQ(searchFile("old.txt"), -3LL);
}

TEST(PopulateData, HandlesEmptyDirectory) {
    libcvault_test::TempDir tmp;
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
    EXPECT_EQ(getFileCount(), 0);
    EXPECT_EQ(getTotalBytes(), 0LL);
}
