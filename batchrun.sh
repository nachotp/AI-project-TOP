END=100 ##00

for j in $(seq 1 $END); do
    ./top.exe < instances/p7.4.r.txt > /dev/null 2>> out/noincrease.out;
done;

