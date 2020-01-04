#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>
/****************************************************************************

  Compile and run with:
    nvcc -o cudapassword cudapassword.cu
    ./cudapassword

*****************************************************************************/



__device__ int is_a_match(char *attempt) {
	char mypassword1[] = "CR2817";
	char mypassword2[] = "LM3019";
	char mypassword3[] = "LS0909";
	char mypassword4[] = "NJ1110";


	char *s = attempt;
	char *h = attempt;
	char *u = attempt;
	char *b = attempt;
	char *pw1 = mypassword1;
	char *pw2 = mypassword2;
	char *pw3 = mypassword3;
	char *pw4 = mypassword4;

	while(*s == *pw1) { 
		if(*s == '\0') 
		{
			printf("Password: %s\n",mypassword1);
			break;
		}

		s++;
		pw1++;
	}
	
	while(*h == *pw2) { 
		if(*h == '\0') 
		{
			printf("Password: %s\n",mypassword2);
			break;
		}

		h++;
		pw2++;
	}

	while(*u == *pw3) { 
		if(*u == '\0') 
		{
			printf("Password: %s\n",mypassword3);
			break;
		}

		u++;
		pw3++;
	}

	while(*b == *pw4) { 
		if(*b == '\0') 
		{
			printf("Password: %s\n",mypassword4);
			return 1;
		}

		b++;
		pw4++;
	}
	return 0;
}

__global__ void  kernel() {
	char i1,i2,i3,i4;

	char password[7];
	password[6] = '\0';

	int i = blockIdx.x+65;
	int j = threadIdx.x+65;
	char firstMatch = i; 
	char secondMatch = j; 

	password[0] = firstMatch;
	password[1] = secondMatch;
	for(i1='0'; i1<='9'; i1++){
		for(i2='0'; i2<='9'; i2++){
			for(i3='0'; i3<='9'; i3++){
				for(i4='0'; i4<='9'; i4++){
					password[2] = i1;
					password[3] = i2;
					password[4] = i3;
					password[5] = i4; 
					if(is_a_match(password)) {
					} 
					else {
	     			//printf("tried: %s\n", password);		  
					}
				}
			}
		}
	}
}

int time_difference(struct timespec *start, 
	struct timespec *finish, 
	long long int *difference) {
	long long int ds =  finish->tv_sec - start->tv_sec; 
	long long int dn =  finish->tv_nsec - start->tv_nsec; 
	if(dn < 0 ) {
		ds--;
		dn += 1000000000; 
	} 
	*difference = ds * 1000000000 + dn;
	return !(*difference > 0);
}


int main() {

	struct  timespec start, finish;
	long long int time_elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	kernel <<<26,26>>>();
	cudaThreadSynchronize();

	clock_gettime(CLOCK_MONOTONIC, &finish);
	time_difference(&start, &finish, &time_elapsed);
	printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9)); 

	return 0;
}


