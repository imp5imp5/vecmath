#define __forceinline inline
#include "vecMath_test.h"
int main()
{
//  mathtest::base_test();
//  mathtest::advanced_test();
  mathtest::profile(20000005);
//  mathtest::profile(1);
  return 0;
}