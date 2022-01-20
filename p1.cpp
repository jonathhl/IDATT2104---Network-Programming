#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
vector<int> result;
vector<thread> threads;

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

// TODO: fix threading, threads each does the interval throughout once. Not optimal.
void threadWork(int start, int end) {

    for (int thread_number = 0; thread_number < 5; thread_number++) {
        threads.emplace_back([&thread_number, &start, &end]{
            for (int i = start; i <= end; i++) {
                if(primeCalc(i))
                    result.emplace_back(i);
            }
        });
    }

    /*
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&i, &temp] {
           bool task_done = false;
           int nr = i;
           while(!task_done) {
               for (int j = temp.size(); j >= temp.size()/5; --j) {
                   if(primeCalc(j)) {
                       result.emplace_back(j);
                   }
               }
           }
        });
    }
     */

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
    vector<int> temp;

    cout << "Start of interval:";
    cin >> start;
    cout << "End of interval:";
    cin >> end;

    /*
    for (int i = start; i <= end; ++i) {
        temp.emplace_back(i);
    }
     */

    threadWork(start, end);

    print(result);
}