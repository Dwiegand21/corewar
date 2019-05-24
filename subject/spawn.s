.name "Spawn"
.comment "gg"

ld %1, r2
ld %-1, r3
st r2, 410
st r3, 411
fork %400
live %-1
