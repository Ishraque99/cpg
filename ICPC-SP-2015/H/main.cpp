#include <bits/stdc++.h>
#include "helpers.h"

using namespace std;

bool is_valid(int r, int c, int height, int width)
{
    return (r < height && r >= 0) && (c < width && c >= 0);
}

// returns -1 if invalid coordinates
int next_index(int delta, int r, int c, int height, int width) {
    // this logic could be wrong
    int next_r = delta == 0 ? r - 1 : r; next_r = delta == 2 ? r + 1 : next_r;
    int next_c = delta == 1 ? c - 1 : c; next_c = delta == 3 ? c + 1 : next_c;

    if (!is_valid(next_r, next_c, height, width)) {
        return -1;
    }
    return (next_r*width) + next_c;
}

vector<int64_t> bellman(vector<vector<vector<int64_t>>> graph, int height, int width)
{
    // init g_prime and copy weights
    vector<vector<vector<int64_t>>> g_prime(height*width, vector<vector<int64_t>>(4, vector<int64_t>(2)));
    for(int i = 0; i < graph.size(); i++) {
        for(int j = 0; j < graph[i].size(); j++) {
            for (int k =0; k < graph[i][j].size(); k++) {
                g_prime[i][j][k] = graph[i][j][k];
            }
        }
    }

    // init s and add edges to all vertices
    vector<vector<int64_t>> s_dist(height*width, vector<int64_t>(2));
    for(int i = 0; i < height*width; i++) {
        s_dist[i][0] = i;
        s_dist[i][1] = 0;
    }
    // add s to the new graph
    g_prime.push_back(s_dist);
    
    // track our final distances
    vector<int64_t> dist(height*width + 1);
    for(int i = 0; i < height*width + 1; i++) {
        dist[i] = INT32_MAX;
        if (i==height*width) {
            dist[i] = 0;
        }
    }

    vector<int64_t> parents(height*width + 1);
    parents[4] = -1;

    // calc min weights from s to all vertices
    for(int t = 0; t < height*width; t++) {
        // cout << "WTF" << endl;
        for(int node_idx = 0; node_idx < g_prime.size(); node_idx ++) {
            // cout <<  "curr node: " << node_idx << endl;
            if(true) {
                for(int edge_idx = 0; edge_idx < g_prime[node_idx].size(); edge_idx++) {
                    // check if valid edge
                    int next_idx = g_prime[node_idx][edge_idx][0];
                    if (next_idx != -1) {
                        int64_t weight = g_prime[node_idx][edge_idx][1];
                        // cout << "next node: " << next_idx << ", w: " << weight << endl;
                        if (dist[node_idx] + weight < dist[next_idx]) {
                            dist[next_idx] = dist[node_idx] + weight;

                            parents[next_idx] = node_idx;
                        }
                    }
                }
            }
        }
    }
    cout << "dists: " << endl;

    for (int i = 0; i < dist.size(); i++) {
        cout << i << ": " << dist[i] << endl;
    }
    // print_2d(dist);
    cout << "parents:" << endl;

    for (int i =0; i < parents.size(); i++) {
        cout << i << " is child of " << parents[i] << endl;
    }

    cout << "G Prime" << endl;
    print_w_mat(g_prime);
    return dist;
}

// int solve(vector<vector<int64_t>> graph, int height, int width)
// {
//     // get new weights
//     bellman(graph, height, width);
//     return 0;
// }

int main(int argc, char **argv)
{

    string dim;
    getline(cin, dim);
    int width, height;
    sscanf(dim.c_str(), "%d %d", &width, &height);

    // // get all input data
    vector<vector<vector<int64_t>>> graph(height*width, vector<vector<int64_t>>(4, vector<int64_t>(2)));
    
    for (int delta = 0; delta < 4; delta++)
    {
        // 0: north, 1: west, 2: south, 3: east
        for (int r = 0; r < height; r++)
        {
            string w_str;
            getline(cin, w_str);
            vector<string> w_vec = string_split(w_str, ' ');
            for (int c = 0; c < width; c++)
            {
                graph[r*width + c][delta][0] = next_index(delta, r, c, height, width);
                graph[r*width + c][delta][1] = stoll(w_vec[c]);
            }
        }
    }
    cout << "Graph: " << endl;
    print_w_mat(graph);
    bellman(graph, height, width);
    // solve(w_mat, height, width);
}