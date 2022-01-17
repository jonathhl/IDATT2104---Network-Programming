#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <bits/stdc++.h>


using namespace std;
vector<int> result;
vector<thread> threads;
mutex result_mutex;

bool primeCalc(int num) {
    if(num<=1) return false;
    if(num == 2) return true;
    for (int i = 2; i <= sqrt(num); ++i) {
        if(num%i == 0) return false;
    }
    return true;
}

void threadWord(int start, int end) {
}

/*
void threadWork(int start, int end) {
    thread t1([&start, &end] {
        for (int i = start; i < end/2; ++i) {
            unique_lock<mutex> lock(result_mutex);
            if(primeCalc(true)) {
                result.emplace_back(i);
            }
        }
    });

    thread t2([&end]{
        for (int i = end/2; i <= end; ++i) {
            unique_lock<mutex> lock(result_mutex);
            if(primeCalc(true)) {
                result.emplace_back(i);
            }
        }
    });
    t1.join();
    t2.join();
}

void print(vector<int> const &input) {
    for (int i : input) {
        cout << i << ' ';
    }
}
*/

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