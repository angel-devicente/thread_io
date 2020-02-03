#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "def.h"
#include "thread_io.h"

static pthread_t thread_id;
static FILE* tlog;

/*******************************************************/

void *io_processor(void *io_comm) {
  char buf[IO_MAX_LEN];
  MPI_Status status;
  while (1) {
    MPI_Recv(&buf,IO_MAX_LEN,MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG,
	     *((MPI_Comm*)io_comm), &status);

    if (status.MPI_TAG == EXIT_IO_TAG) return 0;
    
    if (status.MPI_TAG == SOUT_IO) {
      fprintf(stdout,"[%d] %s",status.MPI_SOURCE,buf);
    }  else if (status.MPI_TAG == SERR_IO) {
      fprintf(stderr,"[%d] %s",status.MPI_SOURCE,buf);
    } else if (status.MPI_TAG == SLOG_IO) {
      if (fprintf(tlog,"[%d] %s",status.MPI_SOURCE,buf) < 0) {
    	fprintf(stderr, "STACK ERROR: cannot write to log-file");
      };
    }
  }
  return 0;
}

void init_io_comm (MPI_Comm comm, MPI_Comm *io_comm) {
  int rank;
  MPI_Comm_dup_with_info(comm,MPI_INFO_NULL, io_comm);
  MPI_Comm_rank(comm,&rank);
  if (rank ==0) {
    pthread_create(&thread_id, NULL, io_processor, io_comm);
    tlog = fopen(LOG_FILENAME,"w");
  }
  MPI_Barrier(comm);
}

void print_t0(MPI_Comm io_comm, char* b, int bs, int stream) {
  MPI_Ssend(b,bs,MPI_CHAR,0,stream,io_comm);
}

void end_io_comm(MPI_Comm *io_comm) {
  int rank;
  MPI_Barrier(*io_comm);
  MPI_Comm_rank(*io_comm, &rank);
  if (rank == 0) {
    MPI_Ssend(MPI_BOTTOM,0,MPI_CHAR,0,EXIT_IO_TAG,*io_comm);
    pthread_join(thread_id,NULL);
    fclose(tlog);
  }
  MPI_Comm_free(io_comm);
}

