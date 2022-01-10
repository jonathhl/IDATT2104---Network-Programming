#include <iostream>
#include <vector>
#include <thread>

using namespace std;

struct primeArray {
    int start, end, num;
};

int main() {
    
}

int check_prime(int a) {
    int c;

    if(a == 2 || a == 3 || a == 5 || a == 7) { // Check if number is 2 
        return 0;
    }
    else if (a % 2 == 0 || a % 3 == 0 || a % 5 == 0 || a % 7 == 0) {
    // Check if number is even
        return 0;
    } else { // Odd numbers, check if prime.
        for(c == 11; c <= a - 1; c += 2) {
            if(a%c == 0)
            return 0;
        }
        if(c == a)
        return 1;
    }
};