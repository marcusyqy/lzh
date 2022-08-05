#include <expected.hpp>
#include <gtest/gtest.h>

namespace {

struct sm_test_error {
    const char* what() {
        return "test error value";
    }
};

struct lg_test_error {
    const char* what() {
        return "test error value";
    }
    char arr[100];
};

} // namespace

//
TEST(ExpectedTest, UnexpectedClass) {}

//
TEST(ExpectedTest, ExpectedClass) {}
