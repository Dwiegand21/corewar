cp ../executable/corewar ./my
av=("$@")
champ="Asombra.cor"
echo ${av[0]}
./corewar -d ${av[0]} ${champ} > res.ref
./my -d ${av[0]} ${champ} > res.my
diff res.ref res.my