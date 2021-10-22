#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include "seq_loop.hpp"


#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif


int main (int argc, char* argv[]) {

  if (argc < 7) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads>"<<std::endl;
    return -1;
  }
  int functionID = atoi(argv[1]);
  float a = atoi(argv[2]);
  float b = atoi(argv[3]);
  float n = atof(argv[4]);
  int intensity = atoi(argv[5]);
  int nbthreads = atoi(argv[6]);
  float x = 0.0;
  

  auto start = std::chrono::steady_clock::now();

  SeqLoop sl; 

  switch(functionID) {
  case 1:
    x = sl.parforThreads(a, b, n, intensity, nbthreads, f1);
    break;
  case 2:
    x = sl.parforThreads(a, b, n, intensity, nbthreads, f2); 
    break;
  case 3:
    x = sl.parforThreads(a, b, n, intensity, nbthreads, f3);
    break;
  case 4:
    x = sl.parforThreads(a, b, n, intensity, nbthreads, f4);
    break;
  default:
    std::cerr<<"Invalid function ID."<<std::endl;
  }

  std::cout<<x<<std::endl;
  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> time_elapsed = finish - start;
  std::cerr<<time_elapsed.count();
  return 0;
}
