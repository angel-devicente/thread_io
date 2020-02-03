
# Table of Contents

1.  [MPI I/O with threads](#org68e9220)
    1.  [Compilation of test code](#org2b8d1bc)
    2.  [Usage](#org7168e31)
    3.  [To do](#org733f654)



<a id="org68e9220"></a>

# MPI I/O with threads

Test code to implement I/O in MPI via a dedicated thread in process 0.

The idea here is that process 0 creates a thread that is continuously in a loop
waiting for messages from all processes (including process 0 itself, in the
original thread), that might arrive at any time and not necessarily the same
number of them from every process.


<a id="org2b8d1bc"></a>

## Compilation of test code

    $ mpicc  -o test_t thread_io.c test.c


<a id="org7168e31"></a>

## Usage

    mpirun -np 16 ./test_t

or if run in a cluster, see file *submit.sh*


<a id="org733f654"></a>

## To do

Parameterize number of messages printed from every process and add an option to
perform random "sleeps" in processes to study the behaviour of possible
race conditions.

