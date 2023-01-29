#include "header.h"
#include <iostream>
#include "ruster.h"
#include <chrono>

using namespace std;

#define TOTAL_RUNS 10000
#define WARM_UPS 100
namespace perf
{
     int8_t perf_var[2][2] = {{1, 2}, {3, 4}};
     void Package::printPackage()
     {
          std::cout << "[Package ["
                    << "u_eight: " << +this->u_eight << ", "
                    << "u_sixteen: " << this->u_sixteen << ", "
                    << "u_thirty_two: " << this->u_thirty_two << ", "
                    << "u_sixty_four: " << this->u_sixty_four << ", "
                    << "s_eight: " << +this->s_eight << ", "
                    << "s_sixteen: " << this->s_sixteen << ", "
                    << "s_thirty_two: " << this->s_thirty_two << ", "
                    << "s_sixty_four: " << this->s_sixty_four << ", "
                    << "slice state[0][0]: " << +this->arr_ptr[0][0] << "] ]"
                    << std::endl;
     }

     void __attribute__((noinline)) Package::mutate()
     {
          this->u_sixty_four += 3;
     }

     uint8_t inline Package::get_u_sixty_four()
     {
          return u_sixty_four;
     }

} // namespace perf

// main method
int main()
{

     chrono::system_clock::time_point start;
     chrono::system_clock::time_point stop;
     chrono::system_clock::duration diff;
     chrono::system_clock::duration min = chrono::system_clock::duration::max();
     chrono::system_clock::duration max = chrono::system_clock::duration::min();
     chrono::system_clock::duration avg = chrono::system_clock::duration::zero();

     int8_t var[2][2] = {{1, 2}, {3, 4}};
     perf::Package *pack = new perf::Package(var);

     // START: C++ perf block
     cout << endl
          << "### C++ ###" << endl;

     for (int i = 0; i < TOTAL_RUNS; i++)
     {
          start = chrono::high_resolution_clock::now();
          pack->mutate();
          stop = chrono::high_resolution_clock::now();
          if (i < WARM_UPS)
               continue;
          diff = chrono::duration_cast<chrono::nanoseconds>(stop - start);
          if (min > diff)
          {
               min = diff;
          }
          if (max < diff)
          {
               max = diff;
          }

          avg += diff;
     }

     avg = avg / (TOTAL_RUNS - WARM_UPS);

     cout
         << "Time taken by CPP call function: "
         << "MIN: " << min.count() << "ns "
         << "MAX: " << max.count() << "ns "
         << "AVG: " << avg.count() << "ns "
         << endl;

     // // START: RUST perf block
     cout << endl
          << "### RUST ###" << endl;

     min = chrono::system_clock::duration::max();
     max = chrono::system_clock::duration::min();
     avg = chrono::system_clock::duration::zero();

     for (int i = 0; i < 10000; i++)
     {
          start = chrono::high_resolution_clock::now();
          ruster_space::mutate(pack);
          stop = chrono::high_resolution_clock::now();
          if (i < 100)
               continue;
          diff = chrono::duration_cast<chrono::nanoseconds>(stop - start);
          if (min > diff)
          {
               min = diff;
          }
          if (max < diff)
          {
               max = diff;
          }

          avg += diff;
     }
     avg = avg / (TOTAL_RUNS - WARM_UPS);

     cout << "Time taken by rust call function: "
          << "MIN: " << min.count() << "ns "
          << "MAX: " << max.count() << "ns "
          << "AVG: " << avg.count() << "ns "
          << endl;
     // END: RUST perf block

     return pack->get_u_sixty_four();
}