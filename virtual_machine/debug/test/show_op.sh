av=("$@")
end=${av[0]}
begin=$(($end - 1))
champ="Hidden.cor terminator.cor"
corewar -v 4 -d $begin ${champ} > gg.begin
corewar -v 4 -d $end ${champ} > gg.end
diff gg.begin gg.end
