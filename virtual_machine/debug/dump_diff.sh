#!/usr/bin/env bash

#ORIGIN_EXE="./origin_sources/champs/championships/2018/corewar"
ORIGIN_EXE="./origin_sources/corewar"
#OUR_EXE="../corewar"
OUR_EXE="../corewar_old"

TMP_DIFFS="./diffs_dir/"

if [[ ! -d ${TMP_DIFFS} ]]; then
    echo "mkdir!"
    mkdir -p ${TMP_DIFFS}
fi

${ORIGIN_EXE} -d $1 $2 $3 > "${TMP_DIFFS}origin_output"
${OUR_EXE} -d $1 $2 $3 > "${TMP_DIFFS}our_output"

diff_res=$(diff "${TMP_DIFFS}origin_output" "${TMP_DIFFS}our_output" | wc -l)
if (( ${diff_res} )); then
    echo "< origin"
    echo "> our"
    echo "$(diff "${TMP_DIFFS}origin_output" "${TMP_DIFFS}our_output")"
else
    echo "1"
fi

rm -f ${TMP_DIFFS}*