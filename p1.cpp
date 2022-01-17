#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
vector<int> result;
vector<thread> threads;

bool primeCalc(int num) {
    if(num<=1) return false;
    if(num == 2) return true;
    for (int i = 2; i <= sqrt(num); ++i) {
        if(num%i == 0) return false;
    }
    return true;
}

// TODO: fix threading, threads each does the interval throughout once. Not optimal.
void threadWork(int start, int end) {
    for (int thread_number = 0; thread_number < 2; thread_number++) {
        threads.emplace_back([thread_number, &start, &end]{
            for (int i = start; i <= end; i++) {
                if(primeCalc(i))
                    result.emplace_back(i);
            }
        });
    }

    for(auto &t : threads) {
        t.join();
    }
}

void print(vector<int> const &input) {
    for (int i : input) {
        cout << i << ' ';
    }
}

int main() {
    int start;
    int end;

    cout << "Select start of interval:";
    cin >> start;
    cout << "Select end of interval:";
    cin >> end;

    threadWork(start, end);

    print(result);
}