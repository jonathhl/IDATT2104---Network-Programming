#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool primeCalc(int num) {
    if(num <= 1) return false;
    if(num <= 3) return true;
    
    if(num % 2 == 0 || num % 3 == 0)
        return false;


    for (int i = 5; i * i <= num; i = i + 6)
        if(num % i == 0 || num % (i + 2) == 0)
            return false;

    return true;
}


void threadWork(int start, int end, vector<int> *vectorArray) {
    for (int i = start; i <= end; ++i) {
        if(primeCalc(i))
            vectorArray->emplace_back(i);
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
    int n;
    vector<thread> threads;

    cout << "Start of interval:";
    cin >> start;
    cout << "End of interval:";
    cin >> end;
    cout << "Number of threads:";
    cin >> n;

    vector<int> vectorArray[n];
    int smallInterval = ((end)-start)/n;

    threads.reserve(n);
    for (int i = 0; i < n; ++i) {
        threads.emplace_back(threadWork, start + (smallInterval * i), start + (smallInterval*(i + 1)), &vectorArray[i]);
    }

    for(auto &t : threads) {
        t.join();
    }

    for (int i = 0; i < n; ++i) {
        print(vectorArray[i]);
    }
}