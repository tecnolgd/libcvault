#include <gtest/gtest.h>

#include <string>

#include "head.hpp"
#include "test_helpers.hpp"

TEST(Sorting, SortFileOnByteOrdersAscending) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "ten.bin", 10);
    libcvault_test::write_bytes_file(tmp.path / "one.bin", 1);
    libcvault_test::write_bytes_file(tmp.path / "five.bin", 5);
    libcvault_test::write_bytes_file(tmp.path / "three.bin", 3);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    sortFileOnByte();

    ASSERT_EQ(getFileCount(), 4);
    EXPECT_EQ(getFileSize(0), 1LL);
    EXPECT_EQ(getFileSize(1), 3LL);
    EXPECT_EQ(getFileSize(2), 5LL);
    EXPECT_EQ(getFileSize(3), 10LL);
    EXPECT_STREQ(getFileName(0), "one.bin");
    EXPECT_STREQ(getFileName(3), "ten.bin");
}

TEST(Sorting, SortFileOnByteHandlesEmptyAndSingle) {
    libcvault_test::TempDir empty;
    ASSERT_EQ(populateData(empty.path.string().c_str()), 0);
    sortFileOnByte();
    EXPECT_EQ(getFileCount(), 0);

    libcvault_test::TempDir single;
    libcvault_test::write_bytes_file(single.path / "only.bin", 7);
    ASSERT_EQ(populateData(single.path.string().c_str()), 0);
    sortFileOnByte();
    ASSERT_EQ(getFileCount(), 1);
    EXPECT_EQ(getFileSize(0), 7LL);
    EXPECT_STREQ(getFileName(0), "only.bin");
}

TEST(Sorting, SortFileOnNameOrdersAlphabetically) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "charlie.txt", 1);
    libcvault_test::write_bytes_file(tmp.path / "alpha.txt", 1);
    libcvault_test::write_bytes_file(tmp.path / "bravo.txt", 1);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    sortFileOnName();

    ASSERT_EQ(getFileCount(), 3);
    EXPECT_STREQ(getFileName(0), "alpha.txt");
    EXPECT_STREQ(getFileName(1), "bravo.txt");
    EXPECT_STREQ(getFileName(2), "charlie.txt");
}

TEST(Sorting, SortFileOnNameHandlesEmptyAndSingle) {
    libcvault_test::TempDir empty;
    ASSERT_EQ(populateData(empty.path.string().c_str()), 0);
    sortFileOnName();
    EXPECT_EQ(getFileCount(), 0);

    libcvault_test::TempDir single;
    libcvault_test::write_bytes_file(single.path / "only.txt", 1);
    ASSERT_EQ(populateData(single.path.string().c_str()), 0);
    sortFileOnName();
    ASSERT_EQ(getFileCount(), 1);
    EXPECT_STREQ(getFileName(0), "only.txt");
}
