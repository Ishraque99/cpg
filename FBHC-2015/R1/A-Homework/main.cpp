#include <bits/stdc++.h>

using namespace std;

vector<int> generate_primacities(int x) {
    // generate prime nums from 0 to x
    // and use them to count how many times 
    // a number is divided by that prime
    vector<bool> sieve(x+1, true);
    vector<int> primacity(x+1, 0);
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
    for (int p : primes) {
        for(int j = p; j < x+1; j+= p) {
            primacity[j] += 1;
        }
    }
    return primacity;
}

int main(int argc, char** argv) {
    string t_str; getline(cin, t_str); int t = stoi(t_str);

    // generate primacities up to limit 10^7
    vector<int> primacities = generate_primacities(10000000);
    
    for (int i = 0; i < t; i++) {
        int c = i+1;
        string input; getline(cin, input); int a,b,k;
        int _ = sscanf(input.c_str(), "%d %d %d", &a, &b, &k);

        int count = 0;
        for(int i = a; i < b+1; i++) {
            if (primacities[i] == k ) {
                count++;
            }
        }

        cout << "Case #" << c << ": " << count << endl;
    }
}