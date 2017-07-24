#include <iostream>
#include <cmath>

const uint64_t COIN = 100000000;
const uint64_t G = 100 * COIN;
const uint64_t blocksPerYear = 210240;
const long double k = 1 + (std::log(1 + 0.032) / blocksPerYear);
const long double r = 1 + (std::log(1 - 0.12) / blocksPerYear);
const uint64_t supplyAtSwitchover = 132474000 * COIN;
const uint64_t switchoverBlock = 2667032;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

uint64_t calcK(const uint64_t height) {
    const uint64_t supply = supplyAtSwitchover * std::pow(k, height - switchoverBlock);
    return supply * (k - 1);
}

uint64_t calcR(const uint64_t height) {
    return G * std::pow(r, height); 
}

int main() {
    for(uint64_t i = 1; i < (blocksPerYear * 20); i += blocksPerYear * (28.0/365.0)) {
        std::cout << "Year: " << (i / (float)blocksPerYear) << std::endl;
        if(i > switchoverBlock) {
            std::cout << "K: " << (calcK(i) / (long double)COIN) << std::endl;
        } else {
            std::cout << "R: " << (calcR(i) / (long double)COIN) << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}
