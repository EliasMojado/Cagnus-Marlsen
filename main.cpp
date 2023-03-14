#include <iostream>
#include "game.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    game* chess = new game();
    
    auto start = high_resolution_clock::now();
    chess->start();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}
