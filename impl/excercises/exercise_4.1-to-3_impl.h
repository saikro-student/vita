#include <iterator>
#include <limits>
#include <tuple>

namespace vita
{
namespace exercise_4_1__3
{
namespace impl
{
    /*
    // Excercise 4.1-1
    It returns subarray where our losses are minimal.
    */
    
    
    /*
    // Excercise 4.1-2
    FIND-MAXIMUM-SUBARRAY_USING_BRUTE_FORCE(A,low,high)
      max = -infinity
      left = unknown_index
      right = unknown_index

      // 1 ->   n
      // 2 ->   n-1
      // ...
      // n-1 -> 2
      // n   -> 1
      // __________
      //        n*(1 + n)/2
      for(i = low; i <= high; i = i + 1)
	sum = 0
	for(j = i; j <= high; j = j + 1)
	  sum = sum + A[j]
          if(sum > max)
	    max = sum
	    left = i
	    rigth = j

      return (left, right, max)
    */


    // Excercise 4.1-3 (brute-force implementation)
    template<typename InputIterator>
    auto find_max_subarray_using_brute_force(InputIterator first,
				             InputIterator last)
    {
      InputIterator left = last;
      InputIterator right = last;
      using ValueType = std::iterator_traits<InputIterator>::value_type;
      auto max = std::numeric_limits<ValueType>::min();
      
      for(; first != last; ++first)
      {
	      ValueType sum = 0;
	      for(auto other = first; other != last; ++other)
	      {
	        sum += *other;
	        if(sum > max)
          {
	          max = sum;
	          left = first;
            right = other;
            ++right;
	        }
	      }
      }

      return std::make_tuple(left, right, max);
    }

    
    // Excercise 4.1-3(b) (recursive implementation)
    template<typename InputIterator>
    auto find_max_crossing_subarray(InputIterator first,
                                    InputIterator last,
				    InputIterator middle)
    {
      using ValueType = std::iterator_traits<InputIterator>::value_type;
      auto left_max = std::numeric_limits<ValueType>::min();
      auto left = last;

      auto left_first = std::make_reverse_iterator(middle);
      auto left_last  = std::make_reverse_iterator(first);      
      for(ValueType sum = 0;
	  left_first != left_last;
	  ++left_first)
      {
	sum += *left_first;
	if(sum >= left_max)
	{
	  left_max = sum;
	  
	  left = left_first.base();
	  --left; // to account the work with a reverse_iterator
	}
      }

      // right part
      auto right_max = std::numeric_limits<ValueType>::min();
      auto right = last;
      
      for(ValueType sum = 0; middle != last; ++middle)
      {
	sum += *middle;
	if(sum >= right_max)
	{
	  right_max = sum;

	  right = middle;
	  ++right; // to account c++ not closed ranged
	}
      }

      return std::make_tuple(left, right, left_max + right_max);
    }
        
    template<typename InputIterator>
    auto find_max_subarray_recursively(InputIterator first,
			               InputIterator last)
    {
      using ValueType = std::iterator_traits<InputIterator>::value_type;
      
      auto size = std::distance(first, last);
      if(size < 1)
      {
	return std::make_tuple(last, last,
			       std::numeric_limits<ValueType>::min());
      }

      if(size == 1)
      {
	return std::make_tuple(first, last, *first);	
      }

      auto middle = first;
      std::advance(middle, size/2);
      
      auto left_result  = find_max_subarray_recursively(first, middle);
      auto cross_result = find_max_crossing_subarray(first, last, middle);
      auto right_result = find_max_subarray_recursively(middle, last);

      constexpr size_t MAX_SUM_IDX = 2;
      auto left_max  = std::get<MAX_SUM_IDX>(left_result);
      auto cross_max = std::get<MAX_SUM_IDX>(cross_result);
      auto right_max = std::get<MAX_SUM_IDX>(right_result);

      if(left_max >= cross_max && left_max >= right_max)
	return left_result;
      if(cross_max >= left_max && cross_max >= right_max)
	return cross_result;
      return right_result;
    }
}  // namespce impl
}  //  exercise_4_1__3
}  // namespace vita
