#include "omp.h"
#include <iostream>
#include <string>

int main(void){
	#pragma omp parallel for schedule(static,2) //Code inside following brackets will be parallelized
	{	
		int sum = 0;
		for(int i=0; i<16; i++) {
			sum += i;
			std::cout << sum << std::endl;			
		}	
	}

}
