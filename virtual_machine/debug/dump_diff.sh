#!/usr/bin/env bash

ORIGIN_EXE="./origin_sources/corewar"
OUR_EXE="./executable/corewar"

TMP_DIFFS="./diffs/"

if [[ ! -d ${TMP_DIFFS} ]]; then
    echo "mkdir!"
    mkdir -p ${TMP_DIFFS}
fi

${ORIGIN_EXE} -d $1 $2 $3 > "${TMP_DIFFS}origin_output"
${OUR_EXE} -d $1 $2 $3 > "${TMP_DIFFS}our_output"

diff_res=$(diff "${TMP_DIFFS}origin_output" "${TMP_DIFFS}our_output" | wc -l)
if (( ${diff_res} )); then
    echo "0"
else
    echo "1"
fi

rm -f ${TMP_DIFFS}*