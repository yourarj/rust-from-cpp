#include "header.h"
#include <iostream>
#include "ruster.h"
#include <chrono>

using namespace std;

namespace perf
{
     uint64_t raise_to_power(uint64_t num, uint64_t pow)
     {
          while (pow > 1)
          {
               num *= num;
               pow -= 1;
          }
          return num;
     }
} // namespace perf

// main method
int main()
{

     chrono::system_clock::time_point start;
     chrono::system_clock::time_point stop;
     chrono::system_clock::duration duration;

     // START: RUST perf block
     cout << endl
          << "### RUST ###" << endl;

     start = chrono::high_resolution_clock::now();
     uint64_t powed_num = ruster_space::raise_to_power(3, 25);
     stop = chrono::high_resolution_clock::now();
     duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

     cout << "Time taken by [rust: ruster_space::raise_to_power]: "
          << duration.count() << " nanoseconds" << endl
          << endl;
     // END: RUST perf block

     // START: C++ perf block
     cout << endl
          << "### C++ ###" << endl;
     start = chrono::high_resolution_clock::now();
     uint64_t powed_num2 = perf::raise_to_power(3, 25);
     stop = chrono::high_resolution_clock::now();
     duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

     uint64_t sum = powed_num + powed_num2;

     cout << "Time taken by native [cpp: perf::raise_to_power]: "
          << duration.count() << " nanoseconds" << endl
          << endl;

     cout << "Sum: " << sum << endl;
     // END: C++ perf block
     return 0;
}