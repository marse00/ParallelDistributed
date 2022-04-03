#include <iostream>
#include "omp.h"
#include<vector>
#include<math.h>
using namespace std; 

vector<vector<int>> partB() {
    vector<vector<int>> vectors = { //Define the vectors used
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
    }
    
    return vectors;
}

vector<int> findCenter(vector<vector<int>> vectors) {
    int sumX = 0;
    int sumY = 0;
    int sumZ = 0;
    for(vector<int> i : vectors) {
        sumX += i[0];
        sumY += i[1];
        sumZ += i[2];
    }
    vector<int> result {sumX/10,sumY/10,sumZ/10};
    return result;
}

int getDistance(vector<int> point1, vector<int> point2) {
    int distance = sqrt(abs(point1[0] - point2[0])^2+abs(point1[1] - point2[1])^2+abs(point1[2] - point2[2])^2 );
    return distance;
}


void moveToCenter(vector<vector<int>> vectors) {
    int ppa = 2;
    int sign = 0;
    vector<int> center = findCenter(vectors);
    vector<vector<int>> origVectors = vectors; 
    //print the original distances of vectors
    cout << "Original distances: " << endl;
    for(int x = 0; x < 10; x++) { //Iterate over each vector
        cout << "distance " << x+1 << ": ";
        cout << getDistance(vectors[x], center);
        cout << endl;
    }
        for(int i = 1; i < 51; i++) { //Modify the positions of each vectors coordinate 50 times
            #pragma omp parallel for 
            for(int x = 0; x < 10; x++) { //Iterate over each vector to add or subtract the PPA
            
                for(int y = 0; y < 3; y++) { // iterate over each particle in the current vector
                    if(int(vectors[x][y]) < int(center[y])) { //decide if the ppa needs to be added or subtracted
                        sign = +1;
                    }else{
                        sign = -1;
                    }
                    vectors[x][y] = vectors[x][y] + (sign * ppa); //add or subtract the ppa to the particle
                
                }
            
            }
            ppa = ppa + rand() % 5 + 1; //randomly decide the number to increase the ppa between 1 to 5
            if(i == 25) { //print the state of vectors at 25 steps
                cout << "iteration 25 distances: " << endl;
                for(int x = 0; x < 10; x++) { //Iterate over each vector
                    cout << "distance " << x+1 << ": ";
                    cout << getDistance(vectors[x], center);
                    cout << endl;
                }
            }
        }
    //print the final state of vectors
    cout << "Final distances: " << endl;
    for(int x = 0; x < 10; x++) { //Iterate over each vector
        cout << "distance " << x+1 << ": ";
        cout << getDistance(vectors[x], center);
        cout << endl;
    }
    cout << "Distance change(Original-Final): " << endl;
    for(int x = 0; x < 10; x++) { //Iterate over each vector
        cout << "distance " << x+1 << " change: ";
        cout << getDistance(origVectors[x], center)-getDistance(vectors[x], center);
        cout << endl;
    }
    return;
}

 int main() {
   vector<vector<int>> results = partB();
   moveToCenter(results);
   return 0;
 }