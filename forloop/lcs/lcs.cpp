#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include "omploop.hpp"

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef __cplusplus
extern "C" {
#endif

  void generateLCS(char* X, int m, char* Y, int n);
  void checkLCS(char* X, int m, char* Y, int n, int result);

#ifdef __cplusplus
}
#endif

int main (int argc, char* argv[]) {

  if (argc < 4) { std::cerr<<"usage: "<<argv[0]<<" <m> <n> <nbthreads>"<<std::endl;
    return -1;
  }

  auto start = std::chrono::system_clock::now();

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);  

  char *X = new char[m];
  char *Y = new char[n];

  generateLCS(X, m, Y, n);

  //insert LCS code here.
  int result = -1; // length of common subsequence

  const int ten = 10000;
  auto d = new int[ten][ten];

  for(int i = 1; i <= m ; i++) {
    for(int j = 1; j <= n ; j++) {
      d[i][j] = -1;
    }
  }

  OmpLoop o1;
  std::condition_variable cond;
  std::mutex mu1, mu2;
  
  o1.setNbThread(atoi(argv[3]));
  o1.parfor<int>(0, m + n + 1, 1,
    [&](int & tls){
      
    },
    [&](int i, int &tls){
      int find = 0;
      int s, row, col;

      std::unique_lock<std::mutex> lock(mu1);

      if(i>=m && i<=n)
        find = m;

      else if(i<m)
        find = i;
      
      else
        find = (m+n) - i;

      for(int j=0; j<=find; j++) {
        i>=n ? (row=(i-n) + j, col = n-j) : (row = j, col = i-j);

        if(row == 0 || col == 0) continue;
        X[row-1] == Y[col-1] ? s = 1 : s = 0;
        
        cond.wait(lock, [&](){
          return !(d[row-1][col-1] < 0 || d[row][col-1] < 0);
        });

        s ? s = d[row - 1][col - 1] + 1 :
          s = std::max(d[row - 1][col], d[row][col - 1]);
        
        d[row][col] = s;
        cond.notify_one();
      }
    },
    [&](int & tls){
      
    }
  );
  result = d[m][n];
  checkLCS(X, m, Y, n, result);

  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> total_time = finish - start;
  std::cerr << total_time.count() << std::endl;
  return 0;
}