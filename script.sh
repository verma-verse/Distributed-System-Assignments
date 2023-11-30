#!/bin/bash

line_to_prepend="// ASHISH VERMA 20204041"

for file in *
do
    if [ -f "$file" ]; then
        # Prepend the line to each file
        echo "$line_to_prepend" | cat - "$file" > temp && mv temp "$file"
        echo "Prepended to $file"
    fi
done

