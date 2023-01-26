#include <benchmark/benchmark.h>
#include "header.h"
#include "ruster.h"

int8_t var[2][2] = {{1, 2}, {3, 4}};

static void BM_InvokeDirectCpp(benchmark::State &state)
{
    for (auto _ : state)
    {
        perf::Package *another = new perf::Package(var);

        another->mutate_c();
    }
}
// Register the function as a benchmark
BENCHMARK(BM_InvokeDirectCpp);

// Benchmark invoke rust func from cpp
static void BM_InvokeRustFromCpp(benchmark::State &state)
{
    for (auto _ : state)
    {
        perf::Package *pack = new perf::Package(var);

        ruster_space::mutate(pack);
    }
}
// Register the function as a benchmark
BENCHMARK(BM_InvokeRustFromCpp);

BENCHMARK_MAIN();