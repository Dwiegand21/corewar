#!/usr/bin/env bash

ARGS=($(find ../subject -name '*.s'))

function compile_ref {
    for arg in ${ARGS[@]}
    do
        ../subject/asm ${arg} 2> /dev/null 1> /dev/null
        compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
        mv ${compiled} tests/$(basename ${compiled} | sed 's/.cor$/.refcor/g') 2> /dev/null
    done
}

function compile_my {
    for arg in ${ARGS[@]}
    do
        ./asm ${arg} 2> /dev/null 1> /dev/null
        compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
        mv ${compiled} tests/$(basename ${compiled} | sed 's/.cor$/.mycor/g') 2> /dev/null
    done
}

function compare {
    for arg in ${ARGS[@]}
    do
        ref=./tests/$(basename ${arg} | sed 's/.s$/.refcor/g')
        my=./tests/$(basename ${arg} | sed 's/.s$/.mycor/g')

        if [[ -f "${ref}" ]] && [[ ! -f "${my}" ]]; then
            echo "My not compiled. Ref compiled. ${arg}"
            continue
        fi
        if [[ ! -f "${ref}" ]] && [[ -f "${my}" ]]; then
            echo "Ref not compiled. My compiled. ${arg}"
            continue
        fi
        if [[ ! -f "${ref}" ]] && [[ ! -f "${my}" ]]; then
            echo "Both not compiled. ${arg}"
            continue
        fi
        diff_size=$(diff ${ref} ${my} | wc -l)
        if (( ${diff_size} )); then
            echo "Not same in file ${arg}"
        else
            echo "OK ${arg}"
        fi
    done
}

rm -f tests/*
echo "Ref time is:"
time compile_ref
echo "My time is:"
time compile_my
echo ""
echo ""
compare
