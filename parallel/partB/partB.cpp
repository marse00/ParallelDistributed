#include <iostream>
#include "omp.h"
using namespace std; 
void printVectors(int vectors[10][3]) {
    for(int x = 0; x < 10; x++) { //Iterate over each vector
        cout << "vector " << x << ": ";
        for(int y = 0; y < 3; y++) { //loop to print each vector
            cout << to_string(vectors[x][y]) << " ";
        }
        cout << endl;
    }
}
int main() {
    int vectors[10][3] = { //Define the vectors used
        {5, 14, 10},
        {7, -8, -14},
        {-2, 9, 8},
        {15, -6, 3},
        {12, 4, -5},
        {4, 20, 17},
        {-16, 5, -1},
        {-11, 3, 16},
        {3, 10, -19},
        {-16, 7, 4}
    };
    int ppa = 2;
    
    int sign = 0;
    //print the original state of vectors
    cout << "Original state: " << endl;
    printVectors(vectors);
        for(int i = 1; i < 51; i++) { //Modify the positions of each vectors coordinate 50 times
            #pragma omp parallel for 
            for(int x = 0; x < 10; x++) { //Iterate over each vector to add or subtract the PPA
            
                for(int y = 0; y < 3; y++) { // iterate over each particle in the current vector
                    sign = rand() % 2; //randomly decide if the ppa will be added or subtracted
                    if(sign == 0) sign = -1;
                    vectors[x][y] = vectors[x][y] + (sign * ppa); //add or subtract the ppa to the particle
                
                }
            
            }
            ppa = ppa + rand() % 5 + 1; //randomly decide the number to increase the ppa between 1 to 5
            if(i == 25) { //print the state of vectors at 25 steps
                cout << "State at 25 iterations: " << endl;
                printVectors(vectors);
            }
    }
    //print the final state of vectors
    cout << "Final state: " << endl;
    printVectors(vectors);
    
    return 0;
}
