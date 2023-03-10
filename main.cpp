#include <iostream>
#include "game.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int main() {
    game chess;
    
    auto start = high_resolution_clock::now();
    chess.start();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<nanoseconds>(end - start);
    cout << "Time taken: " << duration.count() << " nanoseconds" << endl;

    int x;
    cin >> x;

    return 0;
}
