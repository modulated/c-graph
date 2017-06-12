#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

// const char emoji_tick[] = "\xF0\x9F\x27\x05";
const char emoji_tick[] = "✅";

void test_list() {
	graph_node_t node = graph_node_new("Alpha");
	graph_node_t node2 = graph_node_new("Beta");
	list_t l = list_new(&node);

	assert(l.start->node->id[0] == 'A');
	assert(l.end->node->id[0] == 'A');
	assert(l.start->next == NULL);
	puts("list_new OK");

	int res = list_find(&l, &node2);
	assert(res == 0);

	list_add(&l, &node2);
	assert(l.end->node->id[0] == 'B');
	puts("list_add OK");

	res = list_find(&l, &node2);
	assert(res == 1);
	puts("list_find OK");
	
	res = list_count(&l);
	assert(res == 2);

	list_t l2 = list_new(&node);
	res = list_count(&l2);
	assert(res == 1);
	puts("list_count OK");

	graph_t g = graph_new(&node);
	list_count(&g.list);
}


void test_node() {
	
	graph_node_t n = graph_node_new("Alpha");
	assert(strcmp(n.id, "Alpha") == 0);
	assert(n.count == 0);
	assert(n.graph == NULL);
	puts("graph_node_new OK");

	graph_t g = graph_new(&n);
	assert(g.count == 1);
	assert(strcmp(g.root->id, "Alpha") == 0);
	puts("graph_new OK");
}

void test_link() {
	graph_node_t n1 = graph_node_new("A1");
	graph_node_t n2 = graph_node_new("A2");

	graph_t g = graph_new(&n1);
	graph_node_link(&n1, &n2, 1.0);

	assert(n1.count == 1 && n2.count == 1);
	assert(g.count == 2);
	

}

int main() {	
	test_node();
	puts("Node ✅");

	test_list();
	puts("List ✅");

	test_link();
	puts("Link ✅");
}

