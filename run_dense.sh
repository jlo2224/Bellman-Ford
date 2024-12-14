i=500
file="metrics/long_uniform_dense.txt"
#echo "V E Iterations Attempted_Relaxations Successful_Relaxations Depth"
#echo "-----------------------------------------------------------------"
for j in {1..5}; do
	while [ "$i" -le 10000 ]; do
		./bf "$i" 0.5 >> $file
		((i+=500))
	done
	i=0
	./bf 20000 0.5 >> $file
	./bf 40000 0.5 >> $file

done
