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
  int intesity = atoi(argv[5]);
  int nbthreads = atoi(argv[6]);
  float x = 0;
  float integral = 0;
  float t1 = (b - a) / n;
  float sum = 0;


  auto start = std::chrono::steady_clock::now();


  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> total_time = stop - start;

  std::cerr << total_time.count() << std::endl;
  
  return 0;
}
