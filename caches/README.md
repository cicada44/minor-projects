# Caches

This repository contains the implementation of two different types of caches: the 2Q cache and the ideal cache.

## Overview

1. **2Q Cache**: The 2Q cache is a type of cache replacement algorithm that maintains two separate queues to manage frequently and recently used items efficiently.

2. **Ideal Cache**: The ideal cache is a theoretical cache model that assumes infinite cache capacity and perfect knowledge of the future item requests. This cache is used as a benchmark to compare the performance of other cache algorithms.

## Usage

Follow this steps:

### Build
    cmake --preset release
    cmake --build --preset release

### Run
    ./build/release/bin/app
    ./build/release/bin/idealCache

### Tests
    ./build/release/bin/tests

## I/O data format

The I/O data format is:

    Input:
    <size of cache elements> <amount of elements>
    <elements>

    Output:
    <number of hits>
