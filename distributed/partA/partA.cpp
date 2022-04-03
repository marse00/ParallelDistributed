#include <iostream>
#include <string>    
#include <cstring>
#include "mpi.h"
#include <thread>
#include <sys/sysinfo.h>

int main(int argc, char** argv) {
  int com_size, rank, namelen;
  MPI_Init(NULL,NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  
  
  
  MPI_Comm_size(MPI_COMM_WORLD, &com_size); // get the number of nodes assigned to the communicator
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get rank of the node
  memset(node_name, 0, MPI_MAX_PROCESSOR_NAME); // get the name of the node
  
  struct sysinfo ramInfo;
  sysinfo (&ramInfo); //get the object with the ram for the node
  long ram = (long)ramInfo.totalram * ramInfo.mem_unit /1024/1024/1024 ; //get the ram size for the node from the object and convert it to gigabytes
  
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);
  auto core_count = std::thread::hardware_concurrency();
  if (rank==0) {
    // Startup informative text
    std::cout << "Nodes Count: " << com_size << std::endl << " Number of Cores of the head node: " << core_count <<  " System RAM of the head node: "<< ram << "GB"<<std::endl;
  }
  
  std::cout << "rank: " << rank << "Hostname: " << node_name << 
  " Number of Cores: " << core_count << " System ram: " << ram << "GB "<< std::endl; 
   system("lscpu | egrep 'CPU MHz'");
 
  MPI_Finalize();
  return 0;
}