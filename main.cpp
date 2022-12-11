#include "header.h"
#include <iostream>
#include "ruster.h"
#include <chrono>

using namespace std;

namespace perf
{
    void Package::printPackage()
    {
        std::cout << "[Package ["
                  << "ueight: " << +this->ueight << ", "
                  << "usixteen: " << this->usixteen << ", "
                  << "uthirtytwo: " << this->uthirtytwo << ", "
                  << "usixtyfour: " << this->usixtyfour << ", "
                  << "seight: " << +this->seight << ", "
                  << "ssixteen: " << this->ssixteen << ", "
                  << "sthirtytwo: " << this->sthirtytwo << ", "
                  << "ssixtyfour: " << this->ssixtyfour << ", "
                  << "slice state[0][0]: " << +this->arr_ptr[0][0] << "] ]"
                  << std::endl;
    }

    void inline Package::mutate_c()
    {
        this->ueight *= 2;
        this->usixteen *= 2;
        this->uthirtytwo *= 2;
        this->usixtyfour *= 2;
        this->seight *= 2;
        this->ssixteen *= 2;
        this->sthirtytwo *= 2;
        this->ssixtyfour *= 2;
        this->arr_ptr[0][0] += 10;
    }
} // namespace perf

// main method
int main()
{

    chrono::system_clock::time_point start;
    chrono::system_clock::time_point stop;
    chrono::system_clock::duration duration;

    int8_t var[2][2] = {{1, 2}, {3, 4}};

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

    return 0;
}