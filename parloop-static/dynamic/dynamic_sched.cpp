#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <thread>
#include <mutex>
#include <vector>
#include <array>
#include "../sequential/seq_loop.hpp"

#ifdef __cplusplus
extern "C" {
#endif

typedef float (*ptr) (float,int);
float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

ptr getFunc(int f) {
  switch (f) {
    case 1:
      return &f1;
    case 2:
      return &f2;
    case 3:
      return &f3;
    default:
      return &f4;
  }
} 

int main (int argc, char* argv[]) {

  std::mutex mu1, mu2;
  std::vector<std::thread> threads;
  int count = 0;
  float sum = 0;

  if (argc < 8) {
    std::cerr<<"usage: "<<argv[0]<<" <functionid> <a> <b> <n> <intensity> <nbthreads> <granularity>"<<std::endl;
    return -1;
  }

  
  auto start = std::chrono::system_clock::now();

  int functionID = atoi(argv[1]);
  float a = atoi(argv[2]);
  float b = atoi(argv[3]);
  float n = atof(argv[4]);
  int intensity = atoi(argv[5]);
  int nbthreads = atoi(argv[6]);
  int gran = atoi(argv[7]);
  float t1 = (b-a) / n;

  float (*ptr)(float, int) = getFunc((int) a);

  for (int i = 0; i < nbthreads; i++) {
    threads.push_back(
      std::thread([&](){ 
        
        float temp = 0;
        while (count < n){
          
          mu1.lock();
          int local_count = count;
          count+= gran;
          mu1.unlock();

          for (int i  = local_count; i < local_count + gran && i < n; i++){
            temp += (*ptr)(a + ((i + .5) * t1), intensity) * t1;
          }
        }

        mu2.lock();
        sum += temp;
        mu2.unlock();
      })
    );
  }

  for (auto & t : threads){
    t.join();
  }

  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_time = finish - start;

  std::cout << sum << std::endl;
  std::cerr << elapsed_time.count() << std::endl;

  return 0;
}