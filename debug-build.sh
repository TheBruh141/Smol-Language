#!/bin/bash

make debug

# Set the path to your compiled program
EXECUTABLE="./build/debug/smolc_debug.out"

# Directory containing test cases
TEST_DIR="./tests"

# Directory to store actual output
OUTPUT_DIR="./actual_output"

# Directory to store logs
LOG_DIR="./logs"

# Create output and log directories if they don't exist
mkdir -p "$OUTPUT_DIR"
mkdir -p "$LOG_DIR"

# Function to run a test case
run_test() {
    input_file="$1"
    output_file="$OUTPUT_DIR/$(basename "$input_file").out"
    log_file="$LOG_DIR/$(basename "$input_file").log"

    # Run the program with the input file and store the output and error in log
    # echo $input_file + "\t" + $output_file + "\t" $log_file
    
"${EXECUTABLE}" "${input_file}" > "$output_file" 2> "$log_file"

    # Compare the actual output with the expected output
    # if diff -q "$output_file" "${input_file%.smol}_expected.out" > /dev/null; then
    #     echo "Test case $(basename "$input_file") passed."
    # else
    #     echo "Test case $(basename "$input_file") failed. See $log_file for details."
    # fi
}

# Iterate over all input files in the test directory
for input_file in "$TEST_DIR"/*.smol; do
    run_test "$input_file"
done

echo "All tests completed."
