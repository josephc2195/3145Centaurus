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

  std::mutex mtx;
  
  SeqLoop sl; 
    if(functionid == 1){ 
      sl.parfor(0, n, nbthreads,
	        [&](int i) -> void{
	          mtx.lock();
	          x = t1* f1(a+((i+.5)*(t1), intensity);
	          integral = x + integral;
	          mtx.unlock();
	        }  
	);  	
  } else if(functionid == 2){
      sl.parfor(0, n, nbthreads,
	        [&](int i) -> void{
	          mtx.lock();
	          x = t1 * f2(a+((i+.5)*(t1), intensity);
	          integral = x + integral;
	          mtx.unlock();
	        }  
	);  	
  } else if(functionid == 3){
      sl.parfor(0, n, nbthreads,
	        [&](int i) -> void{
	          mtx.lock();
	          x = t1 * f3(a+((i+.5)*(t1), intensity);
	          integral = x + integral;
	          mtx.unlock();
	        }  
	);  	
  } else if(functionid == 4){
      sl.parfor(0, n, nbthreads,
	        [&](int i) -> void{
	          mtx.lock();
	          x = t1 * f4(a+((i+.5)*(t1), intensity);
	          integral = x + integral;
	          mtx.unlock();
	        }  
	);  	
    }
    
  std::cout<<integral<<std::endl; 
  auto finish = std::chrono::system_clock::now();
  std::cerr<<std::chrono::duration_cast<std::chrono::microseconds> (finish - start).count();
  return 0;
}
