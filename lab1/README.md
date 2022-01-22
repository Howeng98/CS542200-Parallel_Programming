# MPI lab with calculate Pixels in circle

# Compile
```
cd sample
make
```

# Execute
    srun -Nnode -nproc ./lab1 r k
    - node: number of nodes
    - proc: number of MPI processes
    - r : the radius of circle, integer
    - k : since the output pixels may be very large, we get remainder instead, integer

e.g.

```
srun -N4 -n12 ./lab1 5 100
```
