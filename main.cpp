#include "header.h"
#include <iostream>
#include "ruster.h"
#include <chrono>

using namespace std;

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

     void inline Package::mutate_c()
     {
          this->u_eight *= 2;
          this->u_sixteen *= 2;
          this->u_thirty_two *= 2;
          this->u_sixty_four *= 2;
          this->s_eight *= 2;
          this->s_sixteen *= 2;
          this->s_thirty_two *= 2;
          this->s_sixty_four *= 2;
          this->arr_ptr[0][0] += 10;
     }

     std::unique_ptr<Package> new_package()
     {
          return std::make_unique<Package>(perf_var);
     }
} // namespace perf

// main method
int main()
{

     chrono::system_clock::time_point start;
     chrono::system_clock::time_point stop;
     chrono::system_clock::duration duration;

     int8_t var[2][2] = {{1, 2}, {3, 4}};

     // START: RUST perf block
     cout << endl
          << "### RUST ###" << endl;
     perf::Package *pack = new perf::Package(var);
     pack->printPackage();

     start = chrono::high_resolution_clock::now();
     ruster_space::mutate(pack);
     stop = chrono::high_resolution_clock::now();
     duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

     pack->printPackage();
     cout << "Time taken by rust call function: "
          << duration.count() << " nanoseconds" << endl
          << endl;
     // END: RUST perf block

     // START: C++ perf block
     cout << endl
          << "### C++ ###" << endl;
     perf::Package *another = new perf::Package(var);
     another->printPackage();

     start = chrono::high_resolution_clock::now();
     another->mutate_c();
     stop = chrono::high_resolution_clock::now();
     duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

     another->printPackage();
     cout << "Time taken by native call function: "
          << duration.count() << " nanoseconds" << endl
          << endl;
     // END: C++ perf block


     // check pinned object shared from C++ to rust and sent back to C++
     auto num = ruster_space::demonstrate_pinned();
     cout << "Number I got from ruster: "
          << +*num << " " << endl
          << endl;

     return 0;
}