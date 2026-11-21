#include <gtest/gtest.h>

#include "head.hpp"
#include "test_helpers.hpp"

TEST(FileMetrics, EmptyStateReportsZeroCountsAndBytes) {
    libcvault_test::TempDir tmp;
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
    EXPECT_EQ(getFileCount(), 0);
    EXPECT_EQ(getTotalBytes(), 0LL);
    EXPECT_EQ(maxFile(), -1LL);
}

TEST(FileMetrics, TotalBytesSumsAllFiles) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "one.bin", 1);
    libcvault_test::write_bytes_file(tmp.path / "two.bin", 22);
    libcvault_test::write_bytes_file(tmp.path / "three.bin", 333);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
    EXPECT_EQ(getFileCount(), 3);
    EXPECT_EQ(getTotalBytes(), 356LL);
}

TEST(FileMetrics, MaxFileReturnsLargestSize) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "small.bin", 2);
    libcvault_test::write_bytes_file(tmp.path / "largest.bin", 99);
    libcvault_test::write_bytes_file(tmp.path / "medium.bin", 15);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
    EXPECT_EQ(maxFile(), 99LL);
}

TEST(FileMetrics, MaxFileOnSingleFile) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "only.bin", 42);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);
    EXPECT_EQ(maxFile(), 42LL);
}
