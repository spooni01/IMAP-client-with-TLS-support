#include <iostream>
#include <benchmark/benchmark.h>

void testFunc() {
    std::cout << "Hello, ISA project!" << std::endl;
}

static void BM_testFunc(benchmark::State& state) {
    for (auto _ : state) {
        testFunc();
    }
}

BENCHMARK_MAIN();