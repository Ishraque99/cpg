#include <bits/stdc++.h>
#include "helpers.h"

using namespace std;

bool is_valid(int r, int c, int height, int width)
{
    return (r < height && r >= 0) && (c < width && c >= 0);
}

vector<vector<vector<int64_t>>> bellman(vector<vector<vector<int64_t>>> w_mat, int height, int width)
{
    // init s_distances
    vector<vector<int64_t>> s_dist(height, vector<int64_t>(width));
    // set dist from s to other vertices to 0
    for (vector<int64_t> v : s_dist)
    {
        for (int i = 0; i < v.size(); i++)
        {
            v[i] = 0;
        }
    }

    // calc min weights from s to all vertices
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            for (int d = 0; d < 4; d++)
            {
                int next_r = d == 0 ? r - 1 : r;
                next_r = d == 2 ? r + 1 : next_r;
                int next_c = d == 1 ? c - 1 : c;
                next_c = d == 3 ? c + 1 : next_c;
                if (is_valid(next_r, next_c, height, width))
                {
                    int64_t new_weight = s_dist[r][c] + w_mat[r][c][d];
                    if (new_weight < s_dist[next_r][next_c])
                    {
                        s_dist[next_r][next_c] = new_weight;
                    }
                }
            }
        }
    }
    cout << "S_dists: " << endl;
    print_2d(s_dist);
    return w_mat;
}

int solve(vector<vector<vector<int64_t>>> w_mat, int height, int width)
{
    // get new weights
    vector<vector<vector<int64_t>>> w_mat2 = bellman(w_mat, height, width);
    return 0;
}

int main(int argc, char **argv)
{

    string dim;
    getline(cin, dim);
    int width, height;
    sscanf(dim.c_str(), "%d %d", &width, &height);

    // get all input data
    vector<vector<vector<int64_t>>> w_mat(height, vector<vector<int64_t>>(width, vector<int64_t>(4)));
    for (int delta = 0; delta < 4; delta++)
    {
        for (int r = 0; r < height; r++)
        {
            // 0: north, 1: west, 2: south, 3: east
            string w_str;
            getline(cin, w_str);
            vector<string> w_vec = string_split(w_str, ' ');
            for (int c = 0; c < width; c++)
            {
                w_mat[r][c][delta] = stoll(w_vec[c]);
            }
        }
    }
    print_w_mat(w_mat);
    solve(w_mat, height, width);
}