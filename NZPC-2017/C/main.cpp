#include <bits/stdc++.h>

using namespace std;
int circle = 8; // total points in circle
int main(int argc, char **argv)
{
    vector<int> freq;
    for (int i=0; i < circle; i++) { freq.push_back(0); }
    string start_n; getline(cin, start_n); int position = stoi(start_n);
    position--; // so modular arithmetic works
    freq[position] += 1;
    vector<string> res = {start_n};
    string curr; getline(cin, curr);
    while(curr != "#") {
        char direction = curr.at(0);
        string num_s = curr.substr(1); int delta = stoi(num_s);

        if (direction == 'A') { delta = -delta; }
        position = (position + delta)%circle;
        // cout << "Pos: " << position << endl;
        if (position < 0) {
            freq[circle +position] += 1;
        } else {
            freq[position] += 1;
        }

        if (position < 0) {
            res.push_back(to_string(circle + position + 1));
        } else {res.push_back(to_string(position + 1));}

        getline(cin, curr);
    }
    
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    int s = 0;
    for (int i = 0; i < circle; i++) {
        // cout << i << ": " << freq[i] << endl; 
        if (freq[i] > 1) {
            cout << "reject" << endl;
            return 0;
        }
        s += freq[i];
    }
    if (s < 5) {
        cout << "reject" << endl;
        return 0;
    }
    cout << endl;
    return 0;
}