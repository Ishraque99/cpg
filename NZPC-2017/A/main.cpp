#include <iostream>
#include <cstdlib>
#include <string>
#include <limits>
#include <vector>
#include <numeric>
#include <ctime>
#include <cmath>

using namespace std; // so we don't have to do std::cout..

void solve(int a, int b, int c);

int main(int arc, char** argv) {
    cout << "Hello World!" << endl;
    int n; cin >> n; 
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        solve(a, b, c);
    }
    return 0;
}

void solve(int a, int b, int c) {
    if ((a + b + c) == 180) {
        printf("%d %d %d Seems OK\n", a, b, c);
    } else {
        printf("%d %d %d Check\n", a, b, c);
    }
}