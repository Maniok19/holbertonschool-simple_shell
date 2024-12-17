#!/bin/bash

run_test() {
    local command="$1"
    local expected_output="$2"
    local output

    output=$(echo "$command" | ./shell | sed 's/\$ //g')

    if [ "$output" == "$expected_output" ]; then
        echo "Test passed"
    else
        echo "Test failed"
        echo "Expected: $expected_output"
        echo "Got: $output"
    fi
}

run_test "ls" "$(ls)"