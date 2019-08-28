#!/usr/bin/env bash

DUMPS_DIR="dumps"
BINS_DIR="champs_bins"
ARGS=($(find ../../subject -name '*.s'))
BAD_CHAMPS=(Car.cor mandragore.cor wave.cor bee_gees.cor Octobre_Rouge_V4.2.cor 42.cor barriere.cor)
DUMPS=(0 5000 10000 15000 20000 25000)

function find_in_array {
    for i in "${BAD_CHAMPS[@]}"
    do
        if [[ "${i}" == "$(basename ${lhs})" ]] ; then
            echo 1
        fi
        if [[ "${i}" == "$(basename ${rhs})" ]] ; then
            echo 1
        fi
    done
    echo 0
}

function compile_ref {
    mkdir -p ${BINS_DIR}
    for arg in ${ARGS[@]}
    do
        ../../subject/asm ${arg} 2> /dev/null 1> /dev/null
        compiled=$(echo ${arg} | sed 's/.s$/.cor/g')
        mv ${compiled} ${BINS_DIR}/$(basename ${compiled}) 2> /dev/null
    done
}

function compare_dumps {
    mkdir -p ${DUMPS_DIR}
    echo "" > ./invalide_diffs
    ARGS=($(find ${BINS_DIR} -name '*.cor'))
    for lhs in ${ARGS[@]}
    do
        for rhs in ${ARGS[@]}
        do
            if [[ $(find_in_array) == "0" ]]; then
                for n in ${DUMPS[@]}
                do
                    ../../subject/corewar ${lhs} ${rhs} -d ${n} > "${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_ref"
                    ./corewar -d ${n} ${lhs} ${rhs} > "${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_my"
                    diff_res=$(diff \
                        "${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_ref" \
                        "${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_my" | wc -l)
                    rm -f "${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_ref"
                    rm -f "${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_my"
                    if (( ${diff_res} )); then
                        printf "\x1b[31m ERROR in ${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_ref \x1b[0m\n"
                        printf " -d ${n} ${lhs} ${rhs}\n" >> ./invalide_diffs
                    else
                        printf "\x1b[32m OK in ${DUMPS_DIR}/$(basename ${lhs})_vs_$(basename ${rhs})-${n}_ref \x1b[0m\n"

                    fi
                done
            fi
        done
    done
    rm -rf ${DUMPS_DIR}
}

compile_ref
compare_dumps
