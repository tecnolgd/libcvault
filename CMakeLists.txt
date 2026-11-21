cmake_minimum_required(VERSION 3.16)
project(libcvault LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(libcvault STATIC main.cpp)
target_include_directories(libcvault PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    find_package(GTest QUIET)

    if(NOT GTest_FOUND)
        set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
        set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
        # Prevent overriding the parent project's compiler/linker settings on Windows
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        )
        FetchContent_MakeAvailable(googletest)
    endif()

    include(GoogleTest)

    file(GLOB LIBCVAULT_TEST_SOURCES CONFIGURE_DEPENDS tests/test_*.cpp)
    add_executable(libcvault_tests ${LIBCVAULT_TEST_SOURCES})
    target_link_libraries(libcvault_tests PRIVATE libcvault GTest::gtest GTest::gtest_main)
    target_include_directories(libcvault_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/tests
    )

    gtest_discover_tests(libcvault_tests)
endif()
