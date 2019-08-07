cp ../executable/corewar ./my
av=("$@")
echo ${av[0]}
./corewar -d ${av[0]} _.cor > res.ref
./my -d ${av[0]} _.cor > res.my
diff res.ref res.my
