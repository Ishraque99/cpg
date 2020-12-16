#include <bits/stdc++.h>

using namespace std;

vector<string> string_split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void print_w_mat(vector<vector<vector<int64_t>>> w_mat)
{
    for (int r = 0; r < w_mat.size(); r++)
    {
        for (int c = 0; c < w_mat[r].size(); c++)
        {
            cout << "[ ";
            for (int d = 0; d < w_mat[r][c].size(); d++)
            {
                cout << w_mat[r][c][d] << ", ";
            }
            cout << "] ";
        }
        cout << endl;
    }
}

void print_2d(vector<vector<int64_t>> arr2d) {
    for(int i = 0; i < arr2d.size(); i++) {
        cout << "[ ";
        for(int j = 0; j < arr2d[i].size(); j++) {
            cout << arr2d[i][j] << ", ";
        }
        cout << "]" << endl;
    }
}

void print_graph(vector<unordered_map<int, int64_t>> graph) {
    for (int i = 0; i < graph.size(); i ++) {
        cout << i << ": ";
        for(const auto &p: graph[i]) {
            cout << "(" << p.first << ", " << p.second << "), ";
        }
        cout << endl;
    }
}