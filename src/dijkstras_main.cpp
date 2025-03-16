#include "dijkstras.h"

int main(){
    Graph G;
    file_to_graph("large.txt", G);
    vector<int> previous(G.size());
    vector<int> distances = dijkstra_shortest_path(G, 3, previous);//
    print_path(extract_shortest_path(distances, previous, 3), distances[3]);
}