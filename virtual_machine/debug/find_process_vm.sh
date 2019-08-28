
CW="./origin_sources/corewar"
CHAMPS="./champs_bins/C248.cor ./champs_bins/O-Maley_Miaou.cor"
av=("$@")
prc=${av[0]}
reg=${av[1]}

${CW} -v 4 ${CHAMPS} | tr -s ' ' | tr -d '\n' | sed 's/P /#P /g' | \
  tr '#' '\n' | grep "P ${prc}" | grep "r${reg} "