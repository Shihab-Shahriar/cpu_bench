#include <benchmark/benchmark.h>
#include <phillox.h>
#include <tyche.h>
#include <squares.h>
#include <threefry.h>
#include <random>

#include <Random123/threefry.h>
#include <Random123/aes.h>
#include <Random123/philox.h>

template <typename RNG>
static void bench_rng(benchmark::State& state) {
  for (auto _ : state){
        RNG rng(12345, 0);
        for(int i = 0; i < state.range(0); ++i)
            benchmark::DoNotOptimize(rng.template draw<uint32_t>());
  }
}


static void bench_r123_philox(benchmark::State& state) {
  for (auto _ : state){
        philox4x32_ukey_t uk={{12345, 0}};
        philox4x32_key_t k = philox4x32keyinit(uk);
        philox4x32_ctr_t c = {{}}; // start counter from 0
        for(int i = 0; i < state.range(0); ++i){
            c.v[0] = i;
            benchmark::DoNotOptimize(philox4x32(c, k));
        }      
    }
}


template <typename RNG>
static void bench_cpp(benchmark::State& state) {
  for (auto _ : state){
      RNG rng(12345);
      for(int i = 0; i < state.range(0); ++i)
        benchmark::DoNotOptimize(rng());
  }
    //benchmark::ClobberMemory();
}


#define TUnit benchmark::kNanosecond

// Register the function as a benchmark
BENCHMARK(bench_rng<Phillox>)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);
BENCHMARK(bench_rng<Tyche>)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);
BENCHMARK(bench_rng<Squares>)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);
BENCHMARK(bench_rng<Threefry>)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK(bench_r123_philox)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);
//BENCHMARK(bench_r123_threefry)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK(bench_cpp<std::mt19937>)->Unit(TUnit)->Arg(10)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);


BENCHMARK_MAIN();
