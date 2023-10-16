# Use a base image
FROM ubuntu:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
  g++ \
  cmake \
  make \
  git

# Copy your code into the image
COPY . /app
WORKDIR /app

# Build your code
RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

# Run your benchmark
CMD ["./build/mybenchmark", "--benchmark_out_format=csv", "--benchmark_out=/app/out.csv"]

