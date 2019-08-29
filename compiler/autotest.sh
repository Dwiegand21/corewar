#!/usr/bin/env bash

ARGS=($(find all_srcs -name '*.s'))
#echo "${ARGS[@]}"
#exit

function compile_ref {
    for arg in "${ARGS[@]}"
    do
        ../subject/asm_2018 ${arg} 2> /dev/null 1> /dev/null
        compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
        mv ${compiled} tests/$(basename ${compiled} | sed 's/.cor$/.refcor/g') 2> /dev/null
    done
}

function compile_my {
    ./asm -s "${ARGS[@]}"
    for arg in "${ARGS[@]}"
    do
        #./asm ${arg} 2> /dev/null 1> /dev/null
        compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
        mv "${compiled}" tests/$(basename ${compiled} | sed 's/.cor$/.mycor/g') 2> /dev/null
    done
}

function VG_test {
    for arg in "${ARGS[@]}"
    do

        leaks=$(valgrind --log-fd=1 ./asm -s ${arg} | grep 'definitely')
        leaks=$(echo "$leaks" | awk '{print $4}')

        mv "${arg}" "tested_files"
        if (( leaks + 0 )); then
          printf "%s " "$arg"
          printf "%s\n" "$leaks"
        fi

        #compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
        #mv ${compiled} tests/$(basename ${compiled} | sed 's/.cor$/.mycor/g') 2> /dev/null
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
            printf "\x1B[31mMy not compiled. Ref compiled. ${arg}\x1B[0m\n"
            wrong_count=$(( ${wrong_count} + 1 ))
            continue
        fi
        if [[ ! -f "${ref}" ]] && [[ -f "${my}" ]]; then
            printf "\x1B[31mRef not compiled. My compiled. ${arg}\x1B[0m\n"
            wrong_count=$(( ${wrong_count} + 1 ))
            continue
        fi
        if [[ ! -f "${ref}" ]] && [[ ! -f "${my}" ]]; then
            printf "\x1B[32mBoth not compiled. ${arg}\x1B[0m\n"
            right_count=$(( ${right_count} + 1 ))
            continue
        fi
        diff_size=$(diff ${ref} ${my} | wc -l)
        if (( ${diff_size} )); then
            wrong_count=$(( ${wrong_count} + 1 ))
            printf "\x1B[31mNot same in file ${arg}\x1B[0m\n"
        else
            right_count=$(( ${right_count} + 1 ))
            printf "\x1B[32mOK ${arg}\x1B[0m\n"
        fi
    done
    percent=$(( ${right_count} * 100 / ${total} ))
    time_percent=$(echo "(${ref_time} - ${my_time}) * 100 / ${ref_time}" | bc)
    echo ""
    echo "Right is ${right_count}/${total} (${percent}%)"
    echo "Ref time is ${ref_time}"
    echo "My time is ${my_time}"
    echo "My is ${time_percent}% faster"
}

mkdir -p tests
rm -f tests/*
echo "Compiling ref"
ref_time=$( TIMEFORMAT="%R"; { time compile_ref; } 2>&1 )
echo "Compiling my"
my_time=$( TIMEFORMAT="%R"; { time compile_my; } 2>&1 )

#VG_test


echo ""
echo ""
compare
