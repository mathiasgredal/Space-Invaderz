#include "utility.h"

float random(float a, float b){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(a, b);
    return dist(mt);
}

int random(int a, int b){
    return random(static_cast<float>(a), static_cast<float>(b));
}
