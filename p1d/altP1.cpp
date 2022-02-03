#include <algorithm>
#include <execution>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
vector<int> result;

bool primeCalc(int num) {
    if(num<=1) return false;
    if(num == 2) return true;
    for (int i = 2; i <= sqrt(num); ++i) {
        if(num%i == 0) return false;
    }
    return true;
}

void threadWork(int start, int end) {
    vector<int> list;
    for (int i = start; i <= end; ++i) {
        list.emplace_back(i);
    }

    transform(execution::par, list.begin(), list.end(), [](int num) {
        if(primeCalc(num)) {
            return result.emplace_back(primeCalc(num));
        }
    });
}

void print(vector<int> const &input) {
    for (int i : input) {
        cout << i << ' ';
    }
}

int main() {
    int start;
    int end;

    cout << "Select start of interval: ";
    cin >> start;
    cout << "Select end of interval: ";
    cin >> end;

    threadWork(start, end);

    print(result);
}