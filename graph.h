#pragma once

#define LINKMAX 4

typedef struct graph_node_s graph_node_t;
typedef struct graph_s graph_t;

typedef struct {
	graph_node_t* node;
	float weight;
} graph_link_t;

typedef struct list_node_s {
	graph_node_t* node;
	struct list_node_s* next;
} list_node_t;

typedef struct {
	list_node_t* start;
	list_node_t* end;
} list_t;
struct graph_node_s {
	char id[32];
	graph_link_t links[LINKMAX];
	unsigned int count;
	graph_t* graph;
};

struct graph_s {
	graph_node_t* root;
	unsigned int count;
	list_t list;
};



graph_t graph_new(graph_node_t* root);
void graph_print(graph_t* g);
graph_node_t graph_node_new(char* id);

void graph_node_link(graph_node_t* n1, graph_node_t* n2, float weight);

list_t list_new(graph_node_t* n);
void list_add(list_t* l, graph_node_t* n);
int list_find(list_t* l, graph_node_t* n);
int list_count(list_t* l);
