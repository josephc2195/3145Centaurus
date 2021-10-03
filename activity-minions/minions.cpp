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
  for (int i = 0; i < argc[1]; i++) {
      std::thread gru[i](f, i);
  }

  for (int i = 0; i < argc[1]; i++) {
      std::thread gru[i].join();
  }

  return 0;
}
