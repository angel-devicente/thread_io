
# Table of Contents

1.  [MPI I/O with threads](#orga008421)
    1.  [Compilation of test code](#orgcb6c14d)
    2.  [Usage](#orgf53bf4e)
    3.  [To do](#org4f2c2e1)



<a id="orga008421"></a>

# MPI I/O with threads

Test code to implement I/O in MPI via a dedicated thread in process 0.

The idea here is that process 0 creates a thread that is continuously in a loop
waiting for messages from all processes (including process 0 itself, in the
original thread), that might arrive at any time and not necessarily the same
number of them from every process.


<a id="orgcb6c14d"></a>

## Compilation of test code

    $ mpicc  -o test_t thread_io.c test.c


<a id="orgf53bf4e"></a>

## Usage

    mpirun -np 16 ./test_t

or if run in a cluster, see file *submit.sh*

This will generate *n\_messages* from each process into *stdout*, *stderr* and
also in the file *test.log*. The messages will not be sorted by rank, but no
messages will be lost. The number of messages don't have to be the same from
each process (and process 0, thread 0, has no information about the number of
messages to expect), but for simplicity they are at the moment (see *To do*).


<a id="org4f2c2e1"></a>

## To do

Parameterize number of messages printed from every process and add an option to
perform random "sleeps" in processes to study the behaviour of possible
race conditions.

