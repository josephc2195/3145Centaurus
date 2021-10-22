#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cmath>
#include <thread>
#include <vector>
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

float get_function_value(int f,float x, int intensity) {
    switch(f) {
        case 1:
            return f1(x, intensity);
            break;
        case 2:
            return f2(x, intensity);
            break;
        case 3:
            return f3(x, intensity);
            break;
        case 4:
            return f4(x, intensity);
            break;
        default:
            return -1;
    }
}

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
    float t1 = (b-a) / n;
    float temp = 0.0f;

    SeqLoop sl; 

    s1.set_thread_count(nbthreads);

    s1.parfor_parallel<float>(0, n, 1,
    [&](float& tls) -> void{ // Before
        tls = 0;
    },
    [&](int i, float& tls) -> void{
        float x_value = a + (i + 0.5f) * start;
        tls += get_function_value(fuctionID, x_value, intensity);
    },
    [&](float& tls) -> void{ // After
        temp += tls;
    }
    );

    result = start * temp;

    std::cout << result;


    std::cout<<x<<std::endl;
    auto finish = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_elapsed = finish-start;
    std::cerr<<time_elapsed.count();
    return 0;
}
