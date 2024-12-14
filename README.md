bf.c contains an implementation for Bellman-Ford on the CPU.

The outputs will be V, E, # of Iterations, # of Attempted Relaxations, # of Successful Relaxations, and Depth of the Shortest Path Tree, in that order.

Using a low p (sparse graph), it is not guaranteed for Bellman-Ford to reach every vertex (by the nature of the algorithm, not due to bugs), since an incoming edge may not exist for any given vertex. Likewise, it is also possible for the program to terminate immediately if there are no outgoing edges from the source vertex.

```
gcc -o bf bf.c
```

Compile the code using the command above. You can also customize the weight distribution used in the populate_matrix function by replacing the line:

```
matrix[i * v + j] = uniform()
```

You are given two bash scripts: run_sparse.sh, and run_dense.sh. As the name implies, they are used to run Bellman-Ford on two different types of graphs. Create a metrics/ directory first before running the python file to view these metrics on a chart.
