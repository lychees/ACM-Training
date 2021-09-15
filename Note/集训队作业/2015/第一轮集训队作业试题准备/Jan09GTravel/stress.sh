for ((i = 1; i <= 1000; i++))
do
	echo "testcase $i"
	./random 400 500 2 $i >travel.in
	./travel <travel.in >travel.out
	./travel_orz <travel.in >travel.ans
	
	if ! diff travel.out travel.ans
	then exit 1
	fi
done
