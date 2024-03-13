#!/bin/bash

function exit_on_error()
{
    echo "Error: $1"
    exit 1
}

function build()
{
    echo "Building $1"
    g++ -std=c++11 -llibero "$1.cpp" -o "$1.out"
}

find . -name "*.cpp" | while read -r file; do
    build "$(basename "$file" .cpp)" || exit_on_error "Failed to build $(basename "$file" .cpp)"
done

echo "Examples built successfully"