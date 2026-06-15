#!/usr/bin/env 	bash

for file in *; do
	if [ -f "$file" ]; then
		echo "file: " "$file"
	elif [ -d "$file" ]; then
		echo "dir: " "$file"
		for sub_file in "$file"; do 
			echo "$file" "/" "$sub_file"
		done
	fi
done
