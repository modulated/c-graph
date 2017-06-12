#include "graph.h"
#include <stdio.h>

int main() {
	graph_node_t n = graph_node_new("root of all evil tends to be the money");
	graph_t g = graph_new(&n);
	graph_node_t l = graph_node_new("leaf1");
	graph_node_t l2 = graph_node_new("leaf2");
	graph_node_link(&n, &l, 1.0);
	graph_node_link(&n, &l2, 3.0);
	graph_print(&g);
}
