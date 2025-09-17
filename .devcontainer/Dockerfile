FROM ubuntu:24.04

# Install dependencies for GCC and C++ development
RUN apt-get update && \
    apt-get install -y build-essential g++ cmake && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /sudoko

# Default command
CMD ["bash"]
