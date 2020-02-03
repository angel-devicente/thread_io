#ifndef THREAD_IO_H
#define THREAD_IO_H  

#define EXIT_IO_TAG 0

void *io_processor(void *io_comm);
void init_io_comm (MPI_Comm comm, MPI_Comm *io_comm);
void print_t0(MPI_Comm io_comm, char* b, int bs, int stream);
void end_io_comm(MPI_Comm *io_comm);

#endif
