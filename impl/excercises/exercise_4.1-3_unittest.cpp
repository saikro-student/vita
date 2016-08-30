#include "public/excercises/exercise_4.1-3.h"

#include <vector>
#include "gtest/gtest.h"

namespace {

class Exercise_4_1__3Test:
    public ::testing::Test {
 protected:
  static const size_t RANGE_FIRST_IDX = 0;
  static const size_t RANGE_LAST_IDX = 1;
  static const size_t MAX_SUM_IDX = 2;
  static const int    SUM_ABSENCE_SIGN =
      std::numeric_limits<int>::min();
  
  std::vector<int> empty_set_;
  std::vector<int> one_elem_set_{7};

  std::vector<int> book_set_{13, -3, -25, 20, -3, -16, -23, 18, 20,
                             -7, 12, -5, -22, 15, -4, 7};
  static const int    BEST_RANGE_RESULT = 43;
  static const size_t BEST_RANGE_FIRST_OFFSET = 7;
  static const size_t BEST_RANGE_LAST_OFFSET  = 11;  
};

TEST_F(Exercise_4_1__3Test, BruteForceVersion) {
  using vita::exercise_4_1__3::find_max_subarray_using_brute_force;
  
  auto empty_set_result =
      find_max_subarray_using_brute_force(std::begin(empty_set_),
					  std::end(empty_set_));
  EXPECT_EQ(std::get<RANGE_FIRST_IDX>(empty_set_result),
	    std::end(empty_set_));
  EXPECT_EQ(std::get<RANGE_LAST_IDX>(empty_set_result),
	    std::end(empty_set_));
  EXPECT_EQ(std::get<MAX_SUM_IDX>(empty_set_result),
	    SUM_ABSENCE_SIGN);

  
  auto one_elem_set_result =
      find_max_subarray_using_brute_force(std::begin(one_elem_set_),
					  std::end(one_elem_set_));
  EXPECT_EQ(std::get<RANGE_FIRST_IDX>(one_elem_set_result),
	    std::begin(one_elem_set_));
  EXPECT_EQ(std::get<RANGE_LAST_IDX>(one_elem_set_result),
	    std::end(one_elem_set_));
  EXPECT_EQ(std::get<MAX_SUM_IDX>(one_elem_set_result),
	    *std::begin(one_elem_set_));

  
  auto book_set_result =
      find_max_subarray_using_brute_force(std::begin(book_set_),
					  std::end(book_set_));
  auto best_range_first = std::get<RANGE_FIRST_IDX>(book_set_result);
  auto best_range_last = std::get<RANGE_LAST_IDX>(book_set_result);
  
  EXPECT_EQ(std::distance(std::begin(book_set_), best_range_first),
			  BEST_RANGE_FIRST_OFFSET);
  EXPECT_EQ(std::distance(std::begin(book_set_), best_range_last),
			  BEST_RANGE_LAST_OFFSET);
  EXPECT_EQ(std::get<MAX_SUM_IDX>(book_set_result),
	    BEST_RANGE_RESULT);  
}
  
}  // namespace
