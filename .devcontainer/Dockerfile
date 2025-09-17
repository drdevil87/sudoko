FROM ubuntu:24.04

# Install dependencies for GCC and C++ development
RUN apt-get update && \
    apt-get install -y build-essential g++ && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /sudoku

# Remove CR characters from build_and_run.sh if present
RUN if [ -f /sudoku/build_and_run.sh ]; then sed -i 's/\r$//' /sudoku/build_and_run.sh; fi

# Default command
CMD ["bash"]
