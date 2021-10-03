#include <iostream>
#include <thread>

void f(int i) {
    std::cout << "Hello! I am minion " << i << std::endl;
}

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cerr<<"usage: "<<argv[0]<<" <nbminions>\n";
    return -1;
  }
  //Your code goes here
  int num = atoi(argv[2]);
  
  std::thread gru(f, num);
  gru.join();

  
  /*for (int i = 0; i < num; i++) {
      std::thread gru[i](f, i);
  }

  for (int i = 0; i < num; i++) {
      gru[i].join();
  }*/

  return 0;
}
