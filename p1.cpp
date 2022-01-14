#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <bits/stdc++.h>

using namespace std;
vector<vector<int>> matrixArray;

bool primeCalc(int num) {
    if(num<=1) return false;
    if(num == 2) return true;
    for (int i = 2; i <= sqrt(num); ++i) {
        if(num%i == 0) return false;
    }
    return true;
}

int main() {

}