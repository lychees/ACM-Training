for ((i = 1; i <= 100; i++))
do
	echo testcase $i
	echo $i | ./random_data >E.in
	./E_orz <E.in >E.ans
	./E <E.in >E.out
	diff E.out E.ans
	if [ $? -ne 0 ]
	then exit 1
	fi
done
