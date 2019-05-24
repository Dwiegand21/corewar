.name "Write"
.comment "gg"

ld %80, r10
add r1, r10, r10
aff r10
live %-2
ldi %100, %100, r16
zjmp %0
