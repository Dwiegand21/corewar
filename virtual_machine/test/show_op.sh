av=("$@")
end=${av[0]}
begin=$(($end - 1))
./corewar -v 4 -d $begin _.cor > gg.begin
./corewar -v 4 -d $end _.cor > gg.end
diff gg.begin gg.end
