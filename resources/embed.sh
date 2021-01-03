#!/bin/bash

# this script is used to regenerate the resources.h file
# execute in bash or git-bash from resources folder

outfile="../include/resources.h"

# reset output file and print header 
echo "#ifndef resources_h_" > ${outfile}
echo "#define resources_h_" >> ${outfile}

for file in *.txt
do
    echo "Processing \"$file\""
    filebname="${file%.txt}"
    echo "static double " $filebname "[] = {" >> ${outfile}

    while IFS= read -r line
    do
      echo "${line}," >> ${outfile}
    done < "$file"
    echo "};" >> ${outfile}

done

echo "#endif" >> ${outfile}

