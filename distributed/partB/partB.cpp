#include <iostream>
#include <string>    
#include <cstring>
#include "mpi.h"
#include <thread>
#include <sys/sysinfo.h>

typedef struct {
  float list[15];
  int size;
  char letter;
  double number;
  int x;
  int y;
}ExampleStruct1;

typedef struct {
  int playerlist[30];
  int playerlistSize;
  char levelName[50];
  int levelNameSize;
  long double randVar;
  int gameBoardWidth;
  int gameBoardHeight;
}ExampleStruct2;

typedef struct {
  char playerName[100];
  int playerNameSize;
  float playerHealth;
  float playerMana;
  char itemList[50];
  int itemListSize;
  double warewolfPercentage;
}ExampleStruct3;

MPI::Datatype  createMpiOneType(){
    //how many variables in the struct
    const int count = 6; 
    //type of every variable in the struct
    MPI::Datatype typesInStruct[count] = {MPI::FLOAT,MPI::INT,MPI::CHAR,MPI::DOUBLE,MPI::INT,MPI::INT};
    //how many elements per variable
    int arrayBlockLengths [count] = {15,1,1,1,1,1};
    // Relative memory address for each variable in the struct
    MPI::Aint objAddress, address1,address2,address3,address4,address5,address6;
    MPI::Aint arrayDisplacements[count];	
    ExampleStruct1 sbuf;
    objAddress = MPI::Get_address(&sbuf);
    address1 = MPI::Get_address(&sbuf.list);
    address2 = MPI::Get_address(&sbuf.size);
    address3 = MPI::Get_address(&sbuf.letter);
    address4 = MPI::Get_address(&sbuf.number);
    address5 = MPI::Get_address(&sbuf.x);
    address6 = MPI::Get_address(&sbuf.y);
    arrayDisplacements[0] = address1 - objAddress;
    arrayDisplacements[1] = address2 - objAddress;
    arrayDisplacements[2] = address3 - objAddress;
    arrayDisplacements[3] = address4 - objAddress;
    arrayDisplacements[4] = address5 - objAddress;
    arrayDisplacements[5] = address6 - objAddress;
    //Create equivalent MPI Datatype
    MPI::Datatype mpiOneStruct;
    mpiOneStruct = MPI::Datatype::Create_struct(count,arrayBlockLengths,arrayDisplacements,typesInStruct);
    //Commit MPI datatype to be used by the cluster
    mpiOneStruct.Commit();
    return mpiOneStruct;
  }

MPI::Datatype  createMpiTwoType(){
    //how many variables in the struct
    const int count = 7  ; 
    //type of every variable in the struct
    MPI::Datatype typesInStruct[count] = {MPI::INT,MPI::INT,MPI::CHAR,MPI::INT,MPI::LONG_DOUBLE,MPI::INT,MPI::INT};
    //how many elements per variable
    int arrayBlockLengths [count] = {30,1,50,1,1,1,1};
    // Relative memory address for each variable in the struct
    MPI::Aint objAddress, address1,address2,address3,address4,address5,address6,address7;
    MPI::Aint arrayDisplacements[count];	
    ExampleStruct2 sbuf;
    objAddress = MPI::Get_address(&sbuf);
    address1 = MPI::Get_address(&sbuf.playerlist);
    address2 = MPI::Get_address(&sbuf.playerlistSize);
    address3 = MPI::Get_address(&sbuf.levelName);
    address4 = MPI::Get_address(&sbuf.levelNameSize);
    address5 = MPI::Get_address(&sbuf.randVar);
    address6 = MPI::Get_address(&sbuf.gameBoardWidth);
    address7 = MPI::Get_address(&sbuf.gameBoardHeight);
    arrayDisplacements[0] = address1 - objAddress;
    arrayDisplacements[1] = address2 - objAddress;
    arrayDisplacements[2] = address3 - objAddress;
    arrayDisplacements[3] = address4 - objAddress;
    arrayDisplacements[4] = address5 - objAddress;
    arrayDisplacements[5] = address6 - objAddress;
    arrayDisplacements[6] = address7 - objAddress;
    //Create equivalent MPI Datatype
    MPI::Datatype mpiTwoStruct;
    mpiTwoStruct = MPI::Datatype::Create_struct(count,arrayBlockLengths,arrayDisplacements,typesInStruct);
    //Commit MPI datatype to be used by the cluster
    mpiTwoStruct.Commit();
    return mpiTwoStruct;
  }
  
MPI::Datatype  createMpiThreeType(){
    //how many variables in the struct
    const int count = 7; 
    //type of every variable in the struct
    MPI::Datatype typesInStruct[count] = {MPI::CHAR,MPI::INT,MPI::FLOAT,MPI::FLOAT,MPI::CHAR,MPI::INT,MPI::DOUBLE};
    //how many elements per variable
    int arrayBlockLengths [count] = {100,1,1,1,50,1,1};
    // Relative memory address for each variable in the struct
    MPI::Aint objAddress, address1,address2,address3,address4,address5,address6,address7;
    MPI::Aint arrayDisplacements[count];	
    ExampleStruct3 sbuf;
    objAddress = MPI::Get_address(&sbuf);
    address1 = MPI::Get_address(&sbuf.playerName);
    address2 = MPI::Get_address(&sbuf.playerNameSize);
    address3 = MPI::Get_address(&sbuf.playerHealth);
    address4 = MPI::Get_address(&sbuf.playerMana);
    address5 = MPI::Get_address(&sbuf.itemList);
    address6 = MPI::Get_address(&sbuf.itemListSize);
    address7 = MPI::Get_address(&sbuf.warewolfPercentage);
    arrayDisplacements[0] = address1 - objAddress;
    arrayDisplacements[1] = address2 - objAddress;
    arrayDisplacements[2] = address3 - objAddress;
    arrayDisplacements[3] = address4 - objAddress;
    arrayDisplacements[4] = address5 - objAddress;
    arrayDisplacements[5] = address6 - objAddress;
    arrayDisplacements[6] = address7 - objAddress;
    //Create equivalent MPI Datatype
    MPI::Datatype mpiThreeStruct;
    mpiThreeStruct = MPI::Datatype::Create_struct(count,arrayBlockLengths,arrayDisplacements,typesInStruct);
    //Commit MPI datatype to be used by the cluster
    mpiThreeStruct.Commit();
    return mpiThreeStruct;
  };
  


int main(int argc, char** argv) {
  int com_size, rank, namelen;
  MPI_Init(NULL,NULL);
  char node_name[MPI_MAX_PROCESSOR_NAME];
  
  
  MPI_Comm_size(MPI_COMM_WORLD, &com_size); // get the number of nodes assigned to the communicator
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); // get rank of the node
  memset(node_name, 0, MPI_MAX_PROCESSOR_NAME); // get the name of the node
  
  MPI_Get_processor_name(node_name, &namelen);
  memset(node_name+namelen,0,MPI_MAX_PROCESSOR_NAME-namelen);
  
  int src = 0;
  int dest = 1;
    
  MPI::Datatype mpiOneStruct = createMpiOneType();
  MPI::Datatype mpiTwoStruct = createMpiTwoType();
  MPI::Datatype mpiThreeStruct = createMpiThreeType();
  
  ExampleStruct1 one;
  ExampleStruct2 two;
  ExampleStruct3 three;
  
  //Populating the structs' instances' attributes
  //one
  for(int i = 0; i < 15; i++) one.list[i] = i;
  one.letter = 's';
  one.size = 15;
  one.number = 2.1;
  one.x = 76;
  one.y = -14;
  
  //two
  two.playerlistSize = 30;
  for(int i = 0; i < two.playerlistSize; i++) two.playerlist[i] = i;
  strcpy(two.levelName,"levelNameExample");
  two.levelNameSize = sizeof(two.levelName);
  two.randVar = rand() % 30;
  two.gameBoardWidth = 8;
  two.gameBoardHeight = 8;
  
  //three
  strcpy(three.playerName,"this is a player name example");
  three.playerNameSize = sizeof(three.playerName);
  three.playerHealth = 43;
  three.playerMana = 77;
  strcpy(three.itemList,"itemlist???");
  three.itemListSize = sizeof(three.itemList);
  three.warewolfPercentage = 0.42;
  
  
  ExampleStruct1 oneReceived;
  ExampleStruct2 twoReceived;
  ExampleStruct3 threeReceived;
  if (rank == src) {   
    std::cout << "> " <<node_name<<" Sent to  node"<< dest+1 << std::endl;
    //Send the structs' instances to the dest node
    MPI_Send(&one, 1, mpiOneStruct, dest, 0, MPI_COMM_WORLD);
    MPI_Send(&two, 1, mpiTwoStruct, dest, 0, MPI_COMM_WORLD);
    MPI_Send(&three, 1, mpiThreeStruct, dest, 0, MPI_COMM_WORLD);
  }
  if(rank == dest){
    std::cout << " Receiving Node: "<< node_name<< std::endl;
    
    //Receive the structs' instances
    //Receive One
    MPI_Recv(&oneReceived, 1, mpiOneStruct, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "> " << node_name << " Received ExampleStruct1 instance: " << std::endl << "letter: " << oneReceived.letter << std::endl 
    << "number: " << oneReceived.number << std::endl << "x: " << oneReceived.x << std::endl << "y: " << oneReceived.y <<  std::endl;
    std::cout << "list: ";
    for (int i = 0; i < 15; i++) {
      std::cout << oneReceived.list[i] << ' ';
    }
    std::cout << std::endl << std::endl;
    //Receive Two
    MPI_Recv(&twoReceived, 1, mpiTwoStruct, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "> " << node_name << " Received ExampleStruct2 instance: " << std::endl << "playerlistSize: " << twoReceived.playerlistSize 
    << std::endl << "levelName: " << twoReceived.levelName << std::endl << "levelNameSize: " << twoReceived.levelNameSize << std::endl 
    << "randVar: " << twoReceived.randVar << std::endl << "gameBoardWidth: " << twoReceived.gameBoardWidth << std::endl << "gameBoardHeight: " 
    << twoReceived.gameBoardHeight << std::endl;
    std::cout << "playerlist: ";
    for (int i = 0; i < 30; i++) {
      std::cout << twoReceived.playerlist[i] << ' ';
    }
    std::cout << std::endl << std::endl;
    //Receive Three
    MPI_Recv(&threeReceived, 1, mpiThreeStruct, src, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::cout << "> " << node_name << " Received ExampleStruct3 instance: " << std::endl << "playerName: " <<
    threeReceived.playerName << std::endl << "playerNameSize: " << threeReceived.playerNameSize << std::endl << "playerHealth: " 
    << threeReceived.playerHealth << std::endl << "playerMana: " << threeReceived.playerMana <<  std::endl 
    << "itemList: " << threeReceived.itemList << std::endl << "itemListSize: " 
    << threeReceived.itemListSize << std::endl << "warewolfPercentage: " << threeReceived.warewolfPercentage<< std::endl;
  }
  

  
  

 
  MPI_Finalize();
  return 0;
}