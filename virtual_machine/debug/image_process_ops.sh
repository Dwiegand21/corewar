#!/usr/bin/env zsh

# 5720
DUMP=1000

#ORIGIN=$( ./origin_sources/corewar -v 4 -d $DUMP ./champs_bins/C248.cor ./champs_bins/O-Maley_Miaou.cor | \
# grep 'P ' | tr -s ' ' | cut -d ' ' -f -4 )

ORIGIN=$( ./origin_sources/corewar -v 6 -d $DUMP ./champs_bins/C248.cor ./champs_bins/O-Maley_Miaou.cor | grep -v '0x\|->' | tr -d '\n' | sed 's/It/#It/g' | tr '#' '\n' | sed 's/P/ P/g' | tr -s ' ' | cut -d ' ' -f 5- | awk '{if (NF > 1) {print $0}}'  | grep -v "'" | sed 's/P/#P/g' | tr '#' '\n' | grep -v 'Cycle' \
  | awk '{if ($4 == "gg") {$5=$6=$7=$8=$9=""} print $0}' | tr -s ' ' | sed 's/ $//g' | \
  sed -E 's/^[0-9]+$/#&/g' | tr -d '\n' | tr '#' '\n' | tr -d '|' | sed 's/P/ | P/g' | sed 's/(.*)//g' | \
  sed 's/ $//g'
 )

OUR=$( ../corewar_old -d $DUMP ./champs_bins/C248.cor ./champs_bins/O-Maley_Miaou.cor \
  | grep -v '0x\|NUMBER' | grep '[0-9]' | grep -v '*' | sed -E 's/^[0-9]+/#&/g' | tr -d '\n' | tr '#' '\n' | awk '{if (NF > 1) {print $0}}' | sed 's/P/#P/g' | tr '#' '\n' | tr -s ' ' | sed 's/ $//g' | \
  sed -E 's/^[0-9]+$/#&/g' | tr -d '\n' | tr '#' '\n' | tr -d '|' | sed 's/P/ | P/g'
  )

#  | grep -v '0x\|NUMBER' | grep '[0-9]' | grep -v '*' | sed 's/P/#P/g' | tr -d '\n' | tr '#' '\n' | sed -E 's/[a-z]+/&#/g' | sed 's/#$//g' | tr '#' '\n' )

#echo ${ORIGIN}
#echo ${OUR}
#exit


#OUR_DIFF=$( echo "$OUR" | sed 's/#.*$//g')
#
#
diff <( echo "${ORIGIN}" ) <( echo "${OUR}" )
#
#sed 's/#*//g'
#
#echo "$( echo $STR | head -1)"