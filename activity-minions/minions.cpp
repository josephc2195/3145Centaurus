#include <iostream>
#include <thread>

void f(int i) {
    std::cout << "Hello! I am minion " << i << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <nbminions>\n";
        return -1;
    }
    //code goes here
    int num = atoi(argv[1]);

    std::thread gru[num];

    for (int i = 0; i < num; i++) {
        gru[i] = std::thread(f, i + 1);
    }

    for (int i = 0; i < num; i++) {
        gru[i].join();
    }
    std::cout << "hello minions! I am the Overlord!" << std::endl;
    return 0;
}
