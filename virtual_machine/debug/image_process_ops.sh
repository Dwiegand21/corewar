#!/usr/bin/env bash

# 5720
DUMP=5786

ORIGIN=$( ./origin_sources/corewar -v 4 -d $DUMP ./champs_bins/C248.cor ./champs_bins/O-Maley_Miaou.cor | \
 grep 'P ' | tr -s ' ' | cut -d ' ' -f -4 )

OUR=$( ../corewar_old -d $DUMP ./champs_bins/C248.cor ./champs_bins/O-Maley_Miaou.cor | grep 'P ' )

#echo $OUR

#OUR_DIFF=$( echo "$OUR" | sed 's/#.*$//g')
#
#
diff <( echo "${ORIGIN}" ) <( echo "${OUR}" )
#
#sed 's/#*//g'
#
#echo "$( echo $STR | head -1)"