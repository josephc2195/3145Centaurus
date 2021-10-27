#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "seq_loop.hpp"
#include <atomic>

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

  if (argc < 8) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads> <granularity>"<<std::endl;
    return -1;
  }

  int fID = atoi(argv[1]);
  int a = atoi(argv[2]);
  int b = atoi(argv[3]);
  int n = atoi(argv[4]);
  int intensity = atoi(argv[5]);
  int nbthreads = atoi(argv[6]);
  int g = atoi(argv[7]);
  float t1 = (b-a)/n;
  float sum = 0;


  SeqLoop s1;

  auto start = std::chrono::steady_clock::now();
  std::atomic<int> processPointer = 0;


  switch(fID) {
    case 1:
    s1.parfor<float>(0, nbthreads, 1, 
                    [&](float& tls) -> void{
                      tls=0;
                    },
                    [&](int pass, float& tls) -> void {
                      int localprocessPointer = processPointer;
                      processPointer+=g;

                      while(localprocessPointer < n)
                      {
                        int endLoop = localprocessPointer + g;
                        for(int i = localprocessPointer; i < endLoop; i++)
                        {
                          float x= a + ((i+.5)*t1);
                          tls+= f1(x, intensity);
                        }
                        localprocessPointer = processPointer;
                        processPointer += g;
                      }
                    },
                    [&](float tls) -> void{
                      sum = tls * t1;
                    }
                    );
    break;

    case 2:
    s1.parfor<float>(0, nbthreads, 1, 
                    [&](float& tls) -> void{
                      tls=0;
                    },
                    [&](int pass, float& tls) -> void {
                      int localprocessPointer = processPointer;
                      processPointer+=g;

                      while(localprocessPointer < n)
                      {
                        int endLoop = localprocessPointer + g;
                        for(int i = localprocessPointer; i < endLoop; i++)
                        {
                          float x= a + ((i+.5)*t1);
                          tls+= f2(x, intensity);
                        }
                        localprocessPointer = processPointer;
                        processPointer += g;
                      }
                    },
                    [&](float tls) -> void{
                      sum = tls * t1;
                    }
                    );
    break;

    case 3:
    s1.parfor<float>(0, nbthreads, 1, 
                    [&](float& tls) -> void{
                      tls=0;
                    },
                    [&](int pass, float& tls) -> void {
                      int localprocessPointer = processPointer;
                      processPointer+=g;

                      while(localprocessPointer < n)
                      {
                        int endLoop = localprocessPointer + g;
                        for(int i = localprocessPointer; i < endLoop; i++)
                        {
                          float x= a + ((i+.5)*t1);
                          tls+= f3(x, intensity);
                        }
                        localprocessPointer = processPointer;
                        processPointer += g;
                      }
                    },
                    [&](float tls) -> void{
                      sum = tls * t1;
                    }
                    );
    break;

    case 4:
    s1.parfor<float>(0, nbthreads, 1, 
                    [&](float& tls) -> void{
                      tls=0;
                    },
                    [&](int pass, float& tls) -> void {
                      int localprocessPointer = processPointer;
                      processPointer+=g;

                      while(localprocessPointer < n)
                      {
                        int endLoop = localprocessPointer + g;
                        for(int i = localprocessPointer; i < endLoop; i++)
                        {
                          float x= a + ((i+.5)*t1);
                          tls+= f4(x, intensity);
                        }
                        localprocessPointer = processPointer;
                        processPointer += g;
                      }
                    },
                    [&](float tls) -> void{
                      sum = tls * t1;
                    }
                    );
    break;

    default: 
    std::cerr<<"invalid functionID";
    return -1;   
  }

  auto finish = std::chrono::steady_clock::now();
  std::chrono::duration<double> time_elapsed = finish-start;
  std::cout << time_elapsed.count();

  std::cerr << sum << std::endl;

  return 0;
}
