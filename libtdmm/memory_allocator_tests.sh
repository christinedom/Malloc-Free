#!/bin/bash

for strategy in first-fit best-fit worst-fit buddy; do
    ./test_tdmm $strategy >> output.txt
done