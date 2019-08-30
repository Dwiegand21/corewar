av=("$@")
end=${av[1]}
begin=$((av[0]))
champ="C248.cor O-Maley_Miaou.cor"
#../origin_sources/champs/championships/2018/corewar -v 4 -d $begin ${champ} > gg.begin
#../origin_sources/champs/championships/2018/corewar -v 4 -d $end ${champ} > gg.end
../origin_sources/corewar -v 4 -d $begin ${champ} > gg.begin
../origin_sources/corewar -v 4 -d $end ${champ} > gg.end
diff gg.begin gg.end
