# Pthread and MPI lab with calculate Pixels in circle

# Compile
```
make
```

# Execute
```
srun [flags] ./lab1 r k
```
    
[flags]:
- N: number of nodes
- n: number of processes
- c: CPUs per process
- t: additional time limit
- J: name of Job
- r : the radius of circle, integer
- k : since the output pixels may be very large, we get remainder instead, integer

e.g.

```
srun -c4 -n1 ./lab2_pthread 5 100
```
```
srun -c4 -n1 ./lab2_omp 5 100
```
```
srun -c4 -n1 ./lab2_hybrid 5 100
```
