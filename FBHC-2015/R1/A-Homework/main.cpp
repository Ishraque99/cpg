#include <bits/stdc++.h>

using namespace std;

bool n_primes(int x) {
    
}

int primacity_matches(int a, int b, int k) {
    int count = 0;
    for (int i = a; a < b+1; i++) {
        if (n_primes(i) == k) {
            count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    string t_str; getline(cin, t_str); int t = stoi(t_str);
    
    for (int i = 0; i < t; i++) {
        int c = i+1;
        string input; getline(cin, input); int a,b,k;
        int _ = sscanf(input.c_str(), "%d %d %d", &a, &b, &k);

        int result = primacity_matches(a, b, k);
    }
}