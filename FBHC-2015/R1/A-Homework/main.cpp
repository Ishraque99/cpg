#include <bits/stdc++.h>

using namespace std;

vector<int> generate_primes(int x) {
    // generate prime nums from 0 to x
    vector<bool> sieve(x+1, true);
    sieve[0] = false; sieve[1] = false;

    for(int i = 2; i < sqrt(x) + 1; i++) {
        if (sieve[i]) {
            for(int j = i*i; j < x + 1; j += i) {
                sieve[j] = false;
            }
        }
    }

    vector<int> primes;
    for(int i = 0; i < sieve.size(); i++) {
        if (sieve[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// int primacity_matches(int a, int b, int k, vector<int> primes) {
//     int count = 0;
//     for (int i = a; a < b+1; i++) {
//         primacity = 0;
//         double limit = sqrt(i) + 1;
//         for(int j = 0; j < primes.size(); j++) {
//             if (primes[j] > limit) {
//                 break;
//             } else {
//                 if ()
//             }
//         }
//     }
//     return count;
// }

int main(int argc, char** argv) {
    string t_str; getline(cin, t_str); int t = stoi(t_str);

    // generate primes up to limit
    vector<int> primes = generate_primes(108);
    
    for (int i = 0; i < t; i++) {
        int c = i+1;
        string input; getline(cin, input); int a,b,k;
        int _ = sscanf(input.c_str(), "%d %d %d", &a, &b, &k);

        int result = primacity_matches(a, b, k, primes);
    }
}