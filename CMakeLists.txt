cmake_minimum_required(VERSION 3.17)  # FetchContent is available in 3.14+
project(MyBenchmarkProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fPIE")

include(FetchContent)

# Download and set up Google Benchmark
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        main
)
FetchContent_GetProperties(benchmark)
if(NOT benchmark_POPULATED)
  FetchContent_Populate(benchmark)
  set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON CACHE INTERNAL "" FORCE)
  add_subdirectory(${benchmark_SOURCE_DIR} ${benchmark_BINARY_DIR})
endif()

# Your own includes
include_directories(${PROJECT_SOURCE_DIR}/OpenRAND/include)
include_directories(${PROJECT_SOURCE_DIR}/random123/include)

# Your own source files
add_executable(mybenchmark cpubench.cpp)

# Link against Google Benchmark
target_link_libraries(mybenchmark benchmark::benchmark pthread)
