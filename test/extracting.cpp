#include "dtm.hpp"
#include <gtest/gtest.h>


TEST(EXTRACT, EXTRACT_PUT_KEY) {
    auto result_put_key = dtm::hash::hash_table::extract_key_from_put_request("put(2,3) [2001] {2}");
    EXPECT_EQ(result_put_key, 2) << "extract put key doesn't work correctly";
}

TEST(EXTRACT, EXTRACT_PUT_VALUE) {
    auto result_put_value = dtm::hash::hash_table::extract_value_from_put_request("put(3,1) [2001] {1}");
    EXPECT_EQ(result_put_value, 1) << "extract put value doesn't work correctly";
}

TEST(EXTRACT, EXTRACT_GET_KEY) {
    auto result_get_key = dtm::hash::hash_table::extract_key_from_get_request("get(2) [2001] {4}");
    EXPECT_EQ(result_get_key, 2) << "extract get key doesn't work correctly";
}

TEST(EXTRACT, EXTRACT_PORT) {
    auto result_port = dtm::hash::hash_table::extract_port("get(2) [2001] {3}");
    EXPECT_EQ(result_port, 2001) << "extract port doesn't work correctly";
}

TEST(EXTRACT, EXTRACT_NODE) {
    auto result_node = dtm::hash::hash_table::extract_node("get(2) [2001] {3}");
    EXPECT_EQ(result_node, 3 ) << "extract node doesn't work correctly";
}