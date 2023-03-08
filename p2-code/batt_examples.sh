#!/bin/bash

# echo '> gcc lcd_update.c lcd_clock.c lcd_clock_main.c'
# gcc lcd_update.c lcd_clock.c lcd_clock_main.c

echo '> make batt_main'
make batt_main
echo

data="3942 3800 3765 3601 3513 3333 3298 3107 3074 3015 3000 2982"

for t in $data; do
    t=$((t*2))
    printf "==========Voltage FOR %d==========\n" "$t"
    echo '> ./batt_main' $t "V"
    ./batt_main $t "V"
    echo
    echo
    printf "==========Percent FOR %d==========\n" "$t"
    echo '> ./batt_main' $t "P"
    ./batt_main $t "P"
    echo
    echo
done

