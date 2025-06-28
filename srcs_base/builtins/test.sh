#!/bin/bash

echo_test() {
    desc="$1"
    shift
    echo "== $desc =="
    
    echo -n "Original:   "
    /bin/echo "$@" | hexdump -C

    echo -n "Custom:     "
    ./my_echo "$@" | hexdump -C

    echo
}

# Test cases
echo_test "No args"
echo_test "Single word" "hello"
echo_test "Multiple words" "hello world 42"
echo_test "With -n option" "-n" "no newline"
echo_test "With unsupported option -e" "-e" "hello\nworld"
echo_test "With literal -n as argument" "hello" "-n" "world"

