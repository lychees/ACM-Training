for ((i = 1; i <= 1000; i++))
do
	echo "testcase $i"
	./random 1000000000000000000  5  1     1 $i >random.in
	./C <random.in >random.ans
	./other/dhh <random.in >random.out
	if ! diff random.out random.ans
	then exit 1
	fi
done
