/*
    readcin.cpp

    Read an entire file from stdin using std::cin.get()
*/

#include <iostream>

int main(int argc, char* argv[]) {

    int count = 0;
    char c;
    std::cin.unsetf(std::ios::skipws);
    while (std::cin.get(c)) {
        ++count;
    }

    std::cout << count << '\n';

    return 0;
}
