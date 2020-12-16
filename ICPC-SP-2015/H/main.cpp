#include <bits/stdc++.h>
// #include "helpers.h"

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

bool is_valid(int r, int c, int height, int width)
{
    return (r < height && r >= 0) && (c < width && c >= 0);
}

// returns -1 if invalid coordinates
int next_index(int delta, int r, int c, int height, int width)
{
    int next_r = delta == 0 ? r - 1 : r;
    next_r = delta == 2 ? r + 1 : next_r;
    int next_c = delta == 1 ? c - 1 : c;
    next_c = delta == 3 ? c + 1 : next_c;

    if (!is_valid(next_r, next_c, height, width))
    {
        return -1;
    }
    return (next_r * width) + next_c;
}

// bellman subroutine. Returns the distances from S to all nodes.
// This distance acts as a modifier
vector<int64_t> bellman(vector<unordered_map<int, int64_t>> graph, int height, int width)
{
    // init g_prime and copy weights
    vector<unordered_map<int, int64_t>> g_prime(height * width);
    for (int i = 0; i < graph.size(); i++)
    {
        for (const pair<int, int64_t> &mapPair : graph[i])
        {
            g_prime[i].insert(mapPair);
        }
    }

    // init s and add edges to all vertices
    unordered_map<int, int64_t> s_dist;
    for (int i = 0; i < graph.size(); i++)
    {
        s_dist.insert(make_pair(i, 0));
    }
    g_prime.push_back(s_dist); // add s to the new graph

    // track our final distances
    vector<int64_t> dist(height * width + 1);
    for (int i = 0; i < height * width + 1; i++)
    {
        dist[i] = INT32_MAX;
        if (i == height * width)
        {
            dist[i] = 0;
        }
    }

    vector<int64_t> parents(height * width + 1);
    parents[height * width] = -1;

    // calc min weights from s to all vertices
    for (int t = 0; t < height * width; t++)
    {
        for (int node_idx = 0; node_idx < g_prime.size(); node_idx++)
        {
            if (dist[node_idx] != INT32_MAX)
            {
                for (const pair<int, int64_t> &mapPair : g_prime[node_idx])
                {
                    int next_idx = mapPair.first;
                    int64_t weight = mapPair.second;
                    if (dist[node_idx] + weight < dist[next_idx])
                    {
                        dist[next_idx] = dist[node_idx] + weight;
                        parents[next_idx] = node_idx;
                    }
                }
            }
        }
    }
    return dist;
}

// dijkstra subroutine. Returns the min cost of path from s to all nodes.
typedef pair<int64_t, int64_t> pqNode;
vector<int64_t> dijkstra(int s, vector<unordered_map<int, int64_t>> graph)
{
    priority_queue<pqNode, vector<pqNode>, greater<pqNode>> pq;

    vector<bool> visited(graph.size(), false);
    vector<int64_t> distances(graph.size(), INT64_MAX);
    distances[s] = 0;
    vector<int> parents(graph.size(), s);
    pq.push(make_pair(0, s));

    while (!pq.empty())
    {
        int64_t u = pq.top().second;
        pq.pop();
        visited[u] = true;
        for (const pair<int, int64_t> &node : graph[u])
        {
            int v = node.first;
            if (v != -1 && !visited[v])
            {
                // valid edge, so proceed
                int64_t w = node.second;
                if (distances[u] + w < distances[v])
                {
                    distances[v] = distances[u] + w;
                    parents[v] = u;
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
    }
    return distances;
}

// modify back the path distances from dijkstra so they match our original graph
vector<int64_t> get_real_distances(vector<int64_t> dij_dist, vector<int64_t> bell_dist, int source)
{
    vector<int64_t> final_distances(dij_dist.size(), -1);

    for(int v = 0; v < dij_dist.size(); v++) {
        if (v == source) {
            final_distances[source] = 0;
            continue;
        }
        final_distances[v] = dij_dist[v] + bell_dist[v] - bell_dist[source];
    }
    
    return final_distances;
}

int64_t get_avg_min_cost(vector<unordered_map<int, int64_t>> graph, vector<unordered_map<int, int64_t>> g_prime,
                        vector<int64_t> bell_dist)
{   long double sum_avg = 0.0;
    for(int i = 0; i < graph.size(); i++) {
        vector<int64_t> dij_dist = dijkstra(i, g_prime);
        vector<int64_t> final_distances = get_real_distances(dij_dist, bell_dist, i);
        int64_t sum = 0; for (int64_t x: final_distances) { sum += x; }
        long double this_avg = sum / (long double)(graph.size() -1); // because we want distincts
        sum_avg += this_avg;
    }
    
    int64_t ceil_result = (int64_t)ceill(sum_avg / graph.size());
    return ceil_result;
}

int main(int argc, char **argv)
{
    string dim;
    getline(cin, dim);
    int width, height;
    sscanf(dim.c_str(), "%d %d", &width, &height);

    vector<unordered_map<int, int64_t>> graph(height * width);

    for (int delta = 0; delta < 4; delta++)
    {   // 0: north, 1: west, 2: south, 3: east
        for (int r = 0; r < height; r++)
        {
            string w_str;
            getline(cin, w_str);
            vector<string> w_vec = string_split(w_str, ' ');
            for (int c = 0; c < width; c++)
            {
                if (next_index(delta, r, c, height, width) != -1)
                {
                    graph[r * width + c].insert(make_pair(next_index(delta, r, c, height, width), stoll(w_vec[c])));
                }
            }
        }
    }

    vector<int64_t> distances = bellman(graph, height, width);

    // construct new graph with modified weights
    vector<unordered_map<int, int64_t>> g_prime(height * width);
    for (int node_idx = 0; node_idx < graph.size(); node_idx++)
    {
        for (const pair<int, int64_t> &mapPair : graph[node_idx])
        {
            int next_idx = mapPair.first;
            int64_t weight = mapPair.second + distances[node_idx] - distances[next_idx];
            g_prime[node_idx].insert(make_pair(next_idx, weight));
        }
    }

    int64_t result = get_avg_min_cost(graph, g_prime, distances);
    cout << result << endl;
    return 0;
}