#!/bin/bash

SFILES=($(find ../origin_sources/champs -name '*.s'))

if [[ ! -d core_files ]]
then
    mkdir -p core_files
fi

for arg in ${SFILES[@]}
do
    ../origin_sources/asm ${arg} 2>/dev/null 1>/dev/null
    compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
    mv ${compiled} core_files/$(basename ${compiled}) 2> /dev/null
done