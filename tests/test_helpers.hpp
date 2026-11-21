#ifndef LIBCVAULT_TEST_HELPERS_HPP
#define LIBCVAULT_TEST_HELPERS_HPP

#include <chrono>
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unistd.h>

namespace fs = std::filesystem;

namespace libcvault_test {

inline fs::path make_temp_dir(const std::string& prefix = "libcvault_test_") {
    auto base = fs::temp_directory_path();
    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937_64 rng(static_cast<unsigned long long>(now) ^ static_cast<unsigned long long>(::getpid()));
    for (int attempt = 0; attempt < 100; ++attempt) {
        std::ostringstream oss;
        oss << prefix << ::getpid() << "_" << now << "_" << rng();
        fs::path candidate = base / oss.str();
        std::error_code ec;
        if (fs::create_directories(candidate, ec)) {
            return candidate;
        }
    }
    throw std::runtime_error("failed to create temporary directory");
}

struct TempDir {
    fs::path path;
    explicit TempDir(const std::string& prefix = "libcvault_test_") : path(make_temp_dir(prefix)) {}
    ~TempDir() {
        std::error_code ec;
        fs::remove_all(path, ec);
    }
    TempDir(const TempDir&) = delete;
    TempDir& operator=(const TempDir&) = delete;
};

inline void write_text_file(const fs::path& path, const std::string& content) {
    std::error_code ec;
    fs::create_directories(path.parent_path(), ec);
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("failed to open file for writing: " + path.string());
    }
    out << content;
    if (!out) {
        throw std::runtime_error("failed to write file: " + path.string());
    }
}

inline void write_bytes_file(const fs::path& path, std::size_t size, char value = 'a') {
    std::error_code ec;
    fs::create_directories(path.parent_path(), ec);
    std::ofstream out(path, std::ios::binary);
    if (!out) {
        throw std::runtime_error("failed to open file for writing: " + path.string());
    }
    std::string chunk(4096, value);
    std::size_t remaining = size;
    while (remaining > 0) {
        std::size_t n = remaining < chunk.size() ? remaining : chunk.size();
        out.write(chunk.data(), static_cast<std::streamsize>(n));
        if (!out) {
            throw std::runtime_error("failed to write file: " + path.string());
        }
        remaining -= n;
    }
}

} // namespace libcvault_test

#endif // libcvault_TEST_HELPERS_HPP
