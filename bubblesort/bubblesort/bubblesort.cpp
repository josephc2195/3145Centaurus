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


void swap(int* a, int b, int c) {
  int temp = a[b];
  a[b] = a[c];
  a[c] = temp;
}

int main (int argc, char* argv[]) {
  if (argc < 3) { std::cerr<<"usage: "<<argv[0]<<" <n> <nbthreads>"<<std::endl;
    return -1;
  }

  auto start = std::chrono::system_clock::now();

  int n = atoi(argv[1]);
  int nbthreads = atoi(argv[2]);

  OmpLoop omp;
  omp.setNbThread(nbthreads);
  
  int *arr = new int [n];
  generateMergeSortData (arr, n);
  
  int cont = 1;
  while(cont) {
    cont = 0;
    omp.parfor<int>(0, n, 1,
		   [&](int& tls) -> void{
		     
		   },
		   [&](int i, int& tls) -> void{
		     if (arr[i-1] > arr[i]) {
		       swap(arr, i-1, i);
		       cont = 1;
		     }
		   },
		   [&](int tls) -> void{
	           }
		 );
  }

  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> total_time = finish-start;
  checkMergeSortResult (arr, n);
  std::cerr<<total_time.count()<<std::endl;

  return 0;
}