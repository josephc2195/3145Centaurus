#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include "omploop.hpp"

#ifdef __cplusplus
extern "C" {
#endif

  void generateMergeSortData (int* arr, size_t n);
  void checkMergeSortResult (const int* arr, size_t n);

#ifdef __cplusplus
}
#endif


void swap(int* arr, int i, int j)
{
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

int main (int argc, char* argv[]) {
  if (argc < 3) { std::cerr<<"usage: "<<argv[0]<<" <n> <nbthreads>"<<std::endl;
    return -1;
  }

  int n = atoi(argv[1]);
  int nbthreads = atoi(argv[2]);

  OmpLoop omp;
  omp.setNbThread(nbthreads);
  
  // get arr data
  int * arr = new int [n];
  generateMergeSortData (arr, n);
  
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  
  //insert sorting code here.
  int swapped = 1;
  while (swapped) {
    swapped = 0;
    omp.parfor<int>(0, n, 1,
		   [&](int& tls) -> void{
		     
		   },
		   [&](int i, int& tls) -> void{
		     if (arr[i-1] > arr[i]) {
		       swap(arr, i-1, i);
		       swapped = 1;
		     }
		   },
		     
		   [&](int tls) -> void{
		   
	           }
		 );
    n--;
  }

  std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
  std::chrono::duration<double> elpased_seconds = end-start;
  
  checkMergeSortResult (arr, n);
  std::cerr<<elpased_seconds.count()<<std::endl;
  
  delete[] arr;

  return 0;
}