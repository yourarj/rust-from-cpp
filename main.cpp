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
                  << "ueight: " << this->ueight << ", "
                  << "usixteen: " << this->usixteen << ", "
                  << "uthirtytwo: " << this->uthirtytwo << ", "
                  << "usixtyfour: " << this->usixtyfour << ", "
                  << "seight: " << this->seight << ", "
                  << "ssixteen: " << this->ssixteen << ", "
                  << "sthirtytwo: " << this->sthirtytwo << ", "
                  << "ssixtyfour: " << this->ssixtyfour << "] ]"
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
    }
} // namespace perf

// main method
int main()
{
    perf::Package *another = new perf::Package();

    auto start2 = chrono::high_resolution_clock::now();
    another->mutate_c();

    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(stop2 - start2);

    cout << "Time taken by native call function: "
         << duration2.count() << " nanoseconds" << endl;

    perf::Package *pack = new perf::Package();

    auto start = chrono::high_resolution_clock::now();
    ruster_space::mutate(pack);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cout << "Time taken by rust call function: "
         << duration.count() << " nanoseconds" << endl;
    return 0;
}