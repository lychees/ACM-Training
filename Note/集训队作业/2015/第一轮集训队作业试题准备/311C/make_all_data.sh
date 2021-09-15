echo "testcase 1"
./random                  80     30     70    13 >room1.in
echo "testcase 2"
./random                  90     40     90    23 >room2.in
echo "testcase 3"
./random                 100     40     90    37 >room3.in
echo "testcase 4"
./random                 100     50    100    61 >room4.in
echo "testcase 5"
./random 1000000000000000000  90000  90000     1 >room5.in
echo "testcase 6"
./random 1000000000000000000  95000  95000     1 >room6.in
echo "testcase 7"
./random 1000000000000000000  96000  96000     1 >room7.in
echo "testcase 8"
./random 1000000000000000000  98000  98000     1 >room8.in
echo "testcase 9"
./random 1000000000000000000 100000 100000     1 >room9.in
echo "testcase 10"
./random 1000000000000000000 100000 100000     1 >room10.in
echo "testcase 11"
./random 1000000000000000000     90     90     3 >room11.in
echo "testcase 12"
./random 1000000000000000000    100    100     4 >room12.in
echo "testcase 13"
./random 1000000000000000000    100    100     7 >room13.in
echo "testcase 14"
./random 1000000000000000000    100    100     8 >room14.in
echo "testcase 15"
./random 1000000000000000000    100    100     9 >room15.in
echo "testcase 16"
./random 1000000000000000000     90     90    10 >room16.in
echo "testcase 17"
./random 1000000000000000000    100    100    10 >room17.in
echo "testcase 18"
./random 1000000000000000000  90000  90000  9000 >room18.in
echo "testcase 19"
./random 1000000000000000000 100000 100000  9090 >room19.in
echo "testcase 20"
./random 1000000000000000000 100000 100000 10000 >room20.in

for ((i = 1; i <= 20; i++))
do
	echo "testcase $i"
	time ./C <room$i.in >room$i.out
done
