#!/bin/bash
#
#SBATCH -J test
#SBATCH -N 5
#SBATCH -n 51
#SBATCH -t 00:07:00
#SBATCH -o test-%j.out
#SBATCH -e test-%j.err
#SBATCH -D .

module purge
module load gnu/7.2.0
module load szip/gnu/2.1.1           
module load openmpi/gnu/3.0.1        

time mpirun  --mca coll_hcoll_enable 0 -np 51 ./test_t
