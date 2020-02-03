#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include "def.h"
#include "thread_io.h"

int main(int argc, char *argv[]) {

  int n_messages = 70;
  int rank, nprocs, l, thread_support;
  char buf[IO_MAX_LEN];
    
  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &thread_support);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

  if (thread_support != MPI_THREAD_MULTIPLE) {
    if (rank == 0) printf("MPI library does not support MPI_THREAD_MULTIPLE.\n");
    return 1;
  } else {
    if (rank == 0) printf("MPI library does support MPI_THREAD_MULTIPLE.\n");
  }

  init_io_comm(MPI_COMM_WORLD,&io_comm);

  for (int i=0; i < n_messages; i++) {
    l = sprintf(buf,"Writing [stdout] message n. %d with T_IO\n",i);
    print_t0(io_comm,buf,l+1,SOUT_IO); 

    l = sprintf(buf,"Writing [stderr] message n. %d with T_IO\n",i);
    print_t0(io_comm,buf,l+1,SERR_IO); 

    l = sprintf(buf,"Writing [log] message n. %d with T_IO\n",i);
    print_t0(io_comm,buf,l+1,SLOG_IO); 
  }


  end_io_comm(&io_comm);

  MPI_Finalize();   
  return 0;
}
