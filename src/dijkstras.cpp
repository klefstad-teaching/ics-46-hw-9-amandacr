#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
#include <algorithm>

#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distance[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue<pair<int, int>> minHeap;
    minHeap.push({source, 0});
    while(!minHeap.empty()){
        int u = minHeap.extractVertexWithMinimumWeight().first;
        if(visited[u]) continue;
        visisted[u] = true;
        for(Edge e : G[u]){
            int v = e.dst;
            int weight = e.weight;
            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push(v, distances[v]);
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    for(int vertex = destination; vertex != -1; vertex = previous[vertex]){
        path.push_back(vertex);
    }
    if(path.size() > 0){
        reverse(path.begin(), path.end());
    }
    return path;
}

void print_path(const vector<int>& v, int total){
    for(auto e : v){
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}