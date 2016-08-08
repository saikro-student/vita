namespace vita
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

	  
    template<typename InputIterator>
    void find_max_subarray_using_brute_force(InputIterator first,
				             InputIterator last)
    {
      for(; first != last; ++first)
      {
	auto item = *first;
	for(other = first; other != last; ++other)
	{
	  
	}
      }
    }
  }
}
