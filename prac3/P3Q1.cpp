#include "omp.h"
#include "stdio.h"
using namespace std;

int main() 
{
	//#pragma omp parallel
	//{
	//	int ID = omp_get_thread_num();
	//	printf("Hello(%d)", ID);
	//	printf("world(%d)\n", ID);
	//}
	//return 0;

	//int x = 0;
	//#pragma omp parallel
	//{
	//	//data race
	//	x = x + 1;
	//	int ID = omp_get_thread_num();
	//	//printf("Hello(%d)", ID);
	//	//printf("world(%d)\n", ID);
	//	printf("shared: x is %d at process (%d) \n", x, ID);
	//}
	//printf("final: x is %d\n", x);
	//return 0;

	#pragma omp parallel
	{
		int y = 0;
		y = y + 1;
		int ID = omp_get_thread_num();
		printf("shared: y is %d at process (%d) \n", y, ID);
	}
	return 0;
}