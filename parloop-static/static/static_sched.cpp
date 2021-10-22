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
  float x = 0;
  float integral = 0;
  float t1 = (b - a) / n;
  float sum = 0;


  auto start = std::chrono::steady_clock::now();

  SeqLoop s1;

  s1.parfor<float>(
      0, 
      n, 
      1,
      [&](float& tls) -> void {
          tls = 0.0;
      },
      [&](int i, float& tls) ->void {
          float x = a + (i + .5) * t1;
          switch (functionID)
          {
          case 1:
              tls += f1(x, intensity);
              break;
          case 2:
              tls += f2(x, intensity);
              break;
          case 3:
              tls += f3(x, intensity);
              break;
          case 4:
              tls += f4(x, intensity);
              break;
          }
      },
          [&](float& tls) -> void {
          sum += tls;
      });

  std::cout << t1 * sum << std::endl;
  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> total_time = stop - start;

  std::cerr << total_time.count() << std::endl;
  
  return 0;
}
