#include <bits/stdc++.h>
#include "helpers.h"

using namespace std;

bool is_valid(int r, int c, int height, int width)
{
    return (r < height && r >= 0) && (c < width && c >= 0);
}

void bellman(vector<vector<int64_t>> graph, int height, int width)
{
    // init g_prime and copy weights
    vector<vector<int64_t>> g_prime(height*width, vector<int64_t>(4));
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            g_prime[i][j] = graph[i][j];
        }
    }

    // init s and add edges to all vertices
    vector<int64_t> s_dist;
    for(int i = 0; i < height*width; i++) {
        s_dist.push_back(0);
    }
    // add s to the new graph
    g_prime.push_back(s_dist);
    
    // track our final distances
    vector<int64_t> dist(height*width + 1);
    for(int i = 0; i < height*width + 1; i++) {
        dist[i] = INT64_MAX;
        if (i==height*width) {
            dist[i] = 0;
        }
    }


    // calc min weights from s to all vertices
    for (int times = 0; times < height * width; times++)
    {
        // go thru the existing edges
        for (int r = 0; r < height; r++)
        {
            for (int c = 0; c < width; c++)
            {   
                if (dist[r*height + c] != INT64_MAX) {
                    for (int d = 0; d < 4; d++)
                {
                    int next_r = d == 0 ? r - 1 : r;
                    next_r = d == 2 ? r + 1 : r;
                    int next_c = d == 1 ? c - 1 : c;
                    next_c = d == 3 ? c + 1 : c;
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
        }
    }
    cout << "S_dists: " << endl;
    print_2d(s_dist);
    // return w_mat;
}

int solve(vector<vector<int64_t>> graph, int height, int width)
{
    // get new weights
    bellman(graph, height, width);
    return 0;
}

int main(int argc, char **argv)
{

    string dim;
    getline(cin, dim);
    int width, height;
    sscanf(dim.c_str(), "%d %d", &width, &height);

    // get all input data
    vector<vector<int64_t>> graph(height*width, vector<int64_t>(4));
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
                graph[r*height + c][delta] = stoll(w_vec[c]);
            }
        }
    }
    cout << "Graph: " << endl;
    print_2d(graph);
    // solve(w_mat, height, width);
}