echo Alice 29995 0     | ./data >skyscraper1.in
echo Alice 10    1     | ./data >skyscraper2.in
echo Alice 15    1     | ./data >skyscraper3.in
echo Alice 50    20    | ./data >skyscraper4.in
echo Alice 100   27    | ./data >skyscraper5.in
echo Alice 500   28    | ./data >skyscraper6.in
echo Alice 1000  30    | ./data >skyscraper7.in
echo Alice 10000 20    | ./data >skyscraper8.in
echo Alice 20000 25    | ./data >skyscraper9.in
echo Alice 30000 30    | ./data >skyscraper10.in
echo Bob   29995 0     | ./data >skyscraper11.in
echo Bob   10    1     | ./data >skyscraper12.in
echo Bob   15    1     | ./data >skyscraper13.in
echo Bob   50    20    | ./data >skyscraper14.in
echo Bob   100   27    | ./data >skyscraper15.in
echo Bob   500   28    | ./data >skyscraper16.in
echo Bob   1000  30    | ./data >skyscraper17.in
echo Bob   10000 20    | ./data >skyscraper18.in
echo Bob   20000 25    | ./data >skyscraper19.in
echo Bob   30000 30    | ./data >skyscraper20.in

for ((i = 1; i <= 20; i++))
do
	./E <skyscraper$i.in >skyscraper$i.out
done
