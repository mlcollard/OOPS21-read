/*
    readcin.cpp

    Read an entire file from stdin using std::cin
*/

#include <iostream>

int main(int argc, char* argv[]) {

    int count = 0;
    char c;
    std::cin.unsetf(std::ios::skipws);
    while (std::cin >> c) {
        ++count;
    }

    std::cout << count << '\n';

    return 0;
}
