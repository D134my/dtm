#include "parser/arg_parser.hpp"
#include <gtest/gtest.h>
#include <iostream>

int _argc;
char **_argv;

TEST(VALIDARGS, ARGS_PASSED_BY_USER) {
    auto result_of_if_args_passed_successfully = dtm::parsing::parser::get_args();
    EXPECT_TRUE(result_of_if_args_passed_successfully.has_value())
            << "./dtmapp udp port, tcp port, node number \n";
}

TEST(VALIDARGS, VALID_NUMBER) {

    auto result_of_validation_args =
            dtm::parsing::parser::validation_args(_argc, _argv);
    EXPECT_TRUE(result_of_validation_args) << "your argument has problem \n";
}

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);

    _argc = argc;
    _argv = argv;

    return RUN_ALL_TESTS();
}