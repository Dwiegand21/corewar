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
    wrong_count=0
    right_count=0
    total=0
    for arg in ${ARGS[@]}
    do
        ref=./tests/$(basename ${arg} | sed 's/.s$/.refcor/g')
        my=./tests/$(basename ${arg} | sed 's/.s$/.mycor/g')

        total=$(( ${total} + 1 ))
        if [[ -f "${ref}" ]] && [[ ! -f "${my}" ]]; then
            echo "My not compiled. Ref compiled. ${arg}"
            wrong_count=$(( ${wrong_count} + 1 ))
            continue
        fi
        if [[ ! -f "${ref}" ]] && [[ -f "${my}" ]]; then
            echo "Ref not compiled. My compiled. ${arg}"
            wrong_count=$(( ${wrong_count} + 1 ))
            continue
        fi
        if [[ ! -f "${ref}" ]] && [[ ! -f "${my}" ]]; then
            echo "Both not compiled. ${arg}"
            right_count=$(( ${right_count} + 1 ))
            continue
        fi
        diff_size=$(diff ${ref} ${my} | wc -l)
        if (( ${diff_size} )); then
            wrong_count=$(( ${wrong_count} + 1 ))
            echo "Not same in file ${arg}"
        else
            right_count=$(( ${right_count} + 1 ))
            echo "OK ${arg}"
        fi
    done
    percent=$(( ${right_count} * 100 / ${total} ))
    echo ""
    echo "Right is ${right_count}/${total} (${percent}%)"
}

rm -f tests/*
echo "Ref time is:"
time compile_ref
echo "My time is:"
time compile_my
echo ""
echo ""
compare
