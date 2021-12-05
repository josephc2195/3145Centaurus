#include <mpi.h>
#include <unistd.h>
#include <iostream>

int main(int argc, char*argv[]) {
    
    MPI_Init (&argc, &argv);
    
    int pid, total;
    
    MPI_Comm_size(MPI_COMM_WORLD, &total);
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    
    char host[256];
    int result = gethostname(host, sizeof(host));
    
    int i = getpid();
    std::cout <<"I am process " <<i<<" out of "<<total<< ". I am running on "<<host<<"\n";
    MPI_Finalize();
}