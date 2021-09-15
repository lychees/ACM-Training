./random     50    100 100000000 a >travel1.in
./random     50    100 100000000 b >travel2.in
./random    100    200 100000000 c >travel3.in
./random    100    200 100000000 d >travel4.in
./random    400    500 100000000 e >travel5.in
./random    400    800 100000000 f >travel6.in
./random   2000   2100 100000000 g >travel7.in
./random   2000   2500 100000000 h >travel8.in
./random   3000   6000 100000000 i >travel9.in
./random   3000 200000 100000000 j >travel10.in
./random   3000 200000         2 k >travel11.in
./random   3000 200000         3 l >travel12.in
./random  90000 190000         3 m >travel13.in
./random 100000 200000         4 n >travel14.in
./random  99900 199900         2 o >travel15.in
./random 100000 200000         3 p >travel16.in
./random  99999 199999         4 q >travel17.in
./random 100000 200000         2 r >travel18.in
./random  99999 199999         1 s >travel19.in
./random 100000 200000         1 t >travel20.in

for ((i = 1; i <= 20; i++))
do
	time ./travel <travel$i.in >travel$i.out
done
