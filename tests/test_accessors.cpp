#include <gtest/gtest.h>

#include <cstddef>
#include <set>
#include <string>
#include <utility>

#include "head.hpp"
#include "test_helpers.hpp"

TEST(Accessors, GetFileNameAndSizeReflectLoadedEntries) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "alpha.bin", 5);
    libcvault_test::write_bytes_file(tmp.path / "beta.bin", 8);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    std::set<std::pair<std::string, long long>> actual;
    for (int i = 0; i < getFileCount(); ++i) {
        actual.insert({std::string(getFileName(i)), getFileSize(i)});
    }
    const std::set<std::pair<std::string, long long>> expected{{"alpha.bin", 5LL}, {"beta.bin", 8LL}};
    EXPECT_EQ(actual, expected);
}

TEST(Accessors, GetFilesReturnsNullAndZeroWhenEmpty) {
    libcvault_test::TempDir tmp;
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    size_t count = 99;
    const fileStructure* data = getFiles(&count);
    EXPECT_EQ(data, nullptr);
    EXPECT_EQ(count, static_cast<size_t>(0));

    const fileStructure* data_no_count = getFiles(nullptr);
    EXPECT_EQ(data_no_count, nullptr);
}

TEST(Accessors, GetFilesExposesInternalBuffer) {
    libcvault_test::TempDir tmp;
    libcvault_test::write_bytes_file(tmp.path / "a.bin", 1);
    libcvault_test::write_bytes_file(tmp.path / "b.bin", 2);
    libcvault_test::write_bytes_file(tmp.path / "c.bin", 3);
    ASSERT_EQ(populateData(tmp.path.string().c_str()), 0);

    size_t count = 0;
    const fileStructure* data = getFiles(&count);
    ASSERT_NE(data, nullptr);
    ASSERT_EQ(count, static_cast<size_t>(getFileCount()));

    for (size_t i = 0; i < count; ++i) {
        EXPECT_STREQ(data[i].name.c_str(), getFileName(static_cast<int>(i)));
        EXPECT_EQ(data[i].byte_size, getFileSize(static_cast<int>(i)));
    }

    const fileStructure* data_no_count = getFiles(nullptr);
    EXPECT_NE(data_no_count, nullptr);

    sortFileOnByte();
    const fileStructure* sorted = getFiles(&count);
    ASSERT_NE(sorted, nullptr);
    ASSERT_EQ(count, static_cast<size_t>(3));
    EXPECT_EQ(sorted[0].byte_size, 1LL);
    EXPECT_EQ(sorted[1].byte_size, 2LL);
    EXPECT_EQ(sorted[2].byte_size, 3LL);
}
