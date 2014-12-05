#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "heap.h"

typedef int boolean;
#define NMAX 1000
#define TRUE 1
#define FALSE 0

/*
 * What is relaxation in Dijkstra's algorithm?
 * In general mathematically, 'relaxation' is making a change that reduces constraints.
 * When Dijkstra's algorithm examines an edge, it removes an edge from the pool, thereby
 * reducing the number of constraints.
 * Think about a vertex with a lot of edges coming into it. When you start, you you start
 * you know the solution has to include the weight from the first edge, the second edge,
 * and so on. In effect, for edges a, b, c, d and e, you start saying "the shortest path
 * must include a, b, c, d, e". Then you eliminate e, and now you know it must include
 * just "a, b, c, d". Each step is a "relaxation" because at each step you remove a
 * condition the current solution imposes.
 *
 *
 * <== As explained in Cormen ==>
 *
 * Single-Source shortest path algorithms use the technique of relaxation.
 * For each vertex (v belonging to V), we maintain an attribute 'v.d', which is an upper bound
 * on the weight of a shortest path from source 's' to 'v'. We call 'v.d' a shortest-path
 * estimate . We initialize the shortest-path estimates and predecessors by the following
 * procedure:
 *
 * INITIALIZE-SINGLE-SOURCE(G, s)
 *      for each vertex (v belonging to G.V)
 *          v.d = infinity
 *          v.pi = NIL      // pi - parent of node
 *      s.d = 0             // s - source
 *
 * After initialization, we have v.pi = NIL for all (v belonging to V), s.d = 0 and v.d = infinity
 * for (v belonging to V-{s}).
 *
 * The process of 'relaxing' an edge (u, v) consists of testing whether we can improve the shortest
 * path to 'v' found so far by going through 'u' and, if so, updating 'v.d' and 'v.pi'.
 * A relaxation step may decrease the value of the shortest-path estimate 'v.d' and update "v's"
 * predecessor attribute 'v.pi'. The following code performs a relaxation step on edge (u, v) in
 * O(1) time.
 *
 * RELAX(u, v, w)
 *      if v.d > u.d + w(u, v)
 *          v.d = u.d + w(u, v)
 *          v.pi = w
 *
 *
 * It may seem strange that the term "relaxation" is used for an operation that tightens an upper bound.
 * The use of the term is historical. The outcome of a relaxation step can be viewed as a relaxation of
 * the constraint v.d <= u.d + w(u, v), which, by the triangle inequality, must be satisfied if
 * u.d = delta(s, u) and v.d = delta(s, v). That is, if v.d <= u.d + w(u, v) there is no "pressure"
 * to satisfy this constraint, so that constraint is "relaxed".
 */


void print_shortest_path(FILE *output, int start_vertex, adj_list *adjacency_list);
void relax(node *node_of_vertex, float dist_to[], int edge_to[], MinHeap *h);
void create_dijkstra_path(int start_vertex, adj_list *adjacency_list, float dist_to[], int edge_to[]);

void minimum_spanning_tree(adj_list *adjacency_list);
void relax_min_span_tree(node *node_of_vertex, float node_key[], int node_parent[], MinHeap *h, boolean marked[]);
void create_minimum_span_tree(int start_vertex, adj_list *adjacency_list, float node_key[], int node_parent[]);
void create_minimum_span_tree_queue(adj_list *adjacency_list, float node_key[], int node_parent[]);

#endif // DIJKSTRA_H_INCLUDED










