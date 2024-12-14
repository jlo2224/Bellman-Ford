i=500
file="metrics/long_bernoulli_sparse.txt"
#echo "V E Iterations Attempted_Relaxations Successful_Relaxations Depth"
#echo "-----------------------------------------------------------------"
for j in {1..10}; do
	while [ "$i" -le 10000 ]; do
		./bf "$i" 5 "$i" >> $file
		((i+=500))
	done
	i=0
	./bf 20000 5 20000 >> $file
	./bf 40000 5 40000 >> $file

done
