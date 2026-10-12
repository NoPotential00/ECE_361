#!/bin/sh
# Run the supplied regression inputs against the modular HW02 program.
fail=0
for input in hw02_starter/data/*.txt; do
    name=$(basename "$input")
    if ./readings < "$input" | diff - "hw02_starter/expected/$name" > /dev/null; then
        echo "PASS  regression $name"
    else
        echo "FAIL  regression $name"
        fail=1
    fi
done
if ./readings 25 < hw02_starter/data/edge.txt | diff - hw02_starter/expected/edge_25.txt > /dev/null; then
    echo "PASS  regression edge.txt, threshold 25"
else
    echo "FAIL  regression edge.txt, threshold 25"
    fail=1
fi
exit $fail
