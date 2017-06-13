#include "graph.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


graph_t graph_new(graph_node_t* root) {
	graph_t g;
	g.root = root;
	g.count = 1;
	g.list = list_new(root);
	root->graph = &g;

	return g;
}

void node_print(graph_node_t* n) {
	printf("Node: %s, Links:%u\n", n->id, n->count);
}

void graph_print(graph_t* g) {
	printf("Graph nodes: %u\nRoot: %s Links:%u\n", g->count, g->root->id, g->root->count);
	for (int i = 0; i < g->root->count; i++) {
		node_print(g->root->links[i].node);
	}
}

graph_node_t graph_node_new(char* id) {
	graph_node_t n;
	strncpy(n.id, id, 31);
	n.id[31] = '\0';
	n.count = 0; 
	n.graph = NULL;
	return n;
}

void graph_node_link(graph_node_t* n1, graph_node_t* n2, float weight) {
	if (n1->count >= LINKMAX || n2->count >= LINKMAX)
	{
		puts("ERROR: Node has too many links");
		exit(1);
	}

	graph_link_t l;

	l.node = n1;
	l.weight = weight;
	n1->links[n1->count++] = l;
	l.node = n2;
	n2->links[n2->count++] = l;	
	
	if (n1->graph == NULL) {
		if (n2->graph == NULL) {
			puts("ERROR: Dangling nodes");
			exit(1);
		}
		n1->graph = n2->graph;
		//list_add(&n1->graph->list, n1);
	}
	
	if (n2->graph == NULL) {
		n2->graph = n1->graph;
		//list_add(&n1->graph->list, n2);
	}
	
	//printf("N1: %p, N2: %p\n", n1->graph, n2->graph);
	n1->graph->count = list_count(&n1->graph->list);

}

list_node_t* list_node_new(graph_node_t* n) {
	list_node_t* l = malloc(sizeof(list_node_t));
	l->node = n;
	l->next = NULL;
	l->prev = NULL;
	return l;
}

int list_count(list_t* l) {
	if (l == NULL) {
		puts("List not initialized");
		exit(1);
	}

	list_node_t* p = l->start;
	int counter = 0;
	if (p == NULL) {
		puts("Unallocated node");
		exit(1);
	}
	while (p != NULL) {
		counter++;
		p = p->next;
	}

	return counter;
}

list_t list_new(graph_node_t* n) {
	list_node_t* node = list_node_new(n);
	list_t l;
	l.start = node;
	l.end = node;
	return l;
}

void list_add(list_t* l, graph_node_t* n) {
	list_node_t* new_node = list_node_new(n);
	l->end->next = new_node;
	new_node->prev = l->end;
	l->end = new_node;
}

int list_find(list_t* l, graph_node_t* n) {
	list_node_t* p;
	p = l->start;
	while (p != NULL) {
		if (n == p->node) return 1;
		p = p->next;
	}

	return 0;
}

void list_remove(list_t* l, graph_node_t* n) {
	list_node_t* p;
	p = l->start;
	while (p != NULL) {
		printf("P: %p\n", p);
		if (n == p->node) {
			if (p->prev != NULL)
				p->prev->next = p->next;
			
			if (p->next != NULL)
				p->next->prev = p->prev;
			return;
		}
		p = p->next;
	}

	puts("ERROR: Could not find node to remove.");
	exit(1);
}
