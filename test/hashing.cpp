#include <gtest/gtest.h>
#include "dtm.hpp"


TEST(ADD_TO_HASH_TABLE_CHECK, IS_THROWING) {
    dtm::hash::hash_table h(9);
    EXPECT_THROW(h.add_to_hash_table(222, 4), std::invalid_argument) << " bad arg";
}

TEST(FETCH_VALUE_FROM_HT, IS_THROWING) {
    dtm::hash::hash_table h;
    h.add_to_hash_table(4, 2);
    EXPECT_ANY_THROW(h.display_hash_table()) << " display is working";
}