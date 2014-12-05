#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define INITIAL_SIZE	100

typedef struct HeapNode {
    int   indx;
    float key;
} HeapNode;

struct MinHeap {
    int       allocated;
    int       size;
    HeapNode *heap;
    int      *indexMap;		// Maps index to heap node.
};

static void Heap_Check(const MinHeap *h, const char *reason);
static void Heap_Print(const MinHeap *h);

MinHeap *Heap_Create(void)
{
    MinHeap *h = calloc(1, sizeof(MinHeap));

    if (h == NULL)
	exit(1);

    h->size      = 0;
    h->allocated = INITIAL_SIZE;
    h->heap      = calloc(INITIAL_SIZE, sizeof(*(h->heap)));
    h->indexMap  = calloc(INITIAL_SIZE, sizeof(*(h->indexMap)));
    if (h->heap == NULL || h->indexMap == NULL)
	exit(1);

    return h;
}

void Heap_Insert(MinHeap *h, int indx, float key)
{
    int       i    = h->size++;
    HeapNode *heap = h->heap;
    int      *map  = h->indexMap;

    // Expand heap if needed.
    if (h->size > h->allocated) {
	h->allocated *= 2;
	h->heap       = realloc(h->heap, h->allocated * sizeof(*(h->heap)));
	h->indexMap   = realloc(h->heap, h->allocated * sizeof(*(h->indexMap)));
	if (h->heap == NULL || h->indexMap == NULL)
	    exit(1);
    }

    // Pretend node was inserted at i.  Find proper level for heap node.
    while(i > 0) {
	int parent = ((i-1) >> 1);
	if (heap[parent].key > key) {
	    // Swap parent with child, and fix up its index in indexMap.
	    heap[i] = heap[parent];
	    map[heap[i].indx] = i;
	    i = parent;
	} else {
	    break;
	}
    }

    // i is now the index where the new node should be inserted.
    heap[i].indx = indx;
    heap[i].key  = key;
    map[indx]    = i;
    Heap_Check(h, "insert");
}

// Returns index of the minimum node.
int Heap_ExtractMin(MinHeap *h)
{
    HeapNode *heap      = h->heap;
    int      *map       = h->indexMap;
    int       ret       = heap[0].indx;
    float     key       = heap[--h->size].key;
    int       i         = 0;
    int       firstLeaf = h->size / 2;

    map[ret] = -1;

    // Pretend that heap[h->size-1] was placed at heap[0].  Fix the heap
    // starting at heap[0].
    while (i < firstLeaf) {
	int lesser = (i << 1) + 1;
	int right  = lesser + 1;
	if (right < h->size && heap[right].key < heap[lesser].key)
	    lesser = right;
	if (heap[lesser].key < key) {
	    // Swap i with its lesser child.
	    heap[i] = heap[lesser];
	    // Fix up i in indexMap.
	    map[heap[i].indx] = i;
	    i = lesser;
	} else
	    break;
    }

    // i is now the node where the last node should be placed.
    heap[i] = heap[h->size];
    map[heap[i].indx] = i;
    Heap_Check(h, "extract");

    return ret;
}

void Heap_DecreaseKey(MinHeap *h, int indx, float key)
{
    HeapNode *heap = h->heap;
    int      *map  = h->indexMap;
    int       i    = map[indx];

    while(i > 0) {
	int parent = ((i-1) >> 1);
	if (heap[parent].key > key) {
	    // Swap parent with child, and fix up its index in indexMap.
	    heap[i] = heap[parent];
	    map[heap[i].indx] = i;
	    i = parent;
	} else {
	    break;
	}
    }

    heap[i].key  = key;
    heap[i].indx = indx;
    map[indx]    = i;
}

int Heap_Size(const MinHeap *h)
{
    return h->size;
}

static void Heap_Check(const MinHeap *h, const char *reason)
{
    HeapNode *heap      = h->heap;
    int       i         = 0;
    int       firstLeaf = h->size / 2;
    int       hasBroken = 0;

    for (i=0;i<firstLeaf;i++) {
	int left  = (i << 1) + 1;
	int right = left + 1;

	if (heap[i].key > heap[left].key) {
	    printf("BROKEN (%s): %d %d\n", reason, i, left);
	    hasBroken = 1;
	}
	if (right < h->size && heap[i].key > heap[right].key) {
	    printf("BROKEN (%s): %d %d\n", reason, i, right);
	    hasBroken = 1;
	}
    }
    for (i=0;i<h->size;i++) {
	if (h->indexMap[i] < h->size && h->indexMap[i] != -1) {
	    if (h->heap[h->indexMap[i]].indx != i) {
		printf("BROKEN (%s): index %d %d\n", reason, i, h->indexMap[i]);
		hasBroken = 1;
	    }
	}
    }
    if (hasBroken)
	Heap_Print(h);
}

static void Heap_Print(const MinHeap *h)
{
    HeapNode *heap      = h->heap;
    int       i         = 0;
    int       firstLeaf = h->size / 2;

    printf("Heap: size=%d\n", h->size);
    for (i=0;i<firstLeaf;i++) {
	int left  = i*2 + 1;
	int right = left + 1;
	printf("%d: %f (%d) -> %d: %f (%d) , %d: %f (%d)\n",
		i, heap[i].key, heap[i].indx,
		left, heap[left].key, heap[left].indx,
		right, heap[right].key, heap[right].indx);
    }
    printf("Indexmap: ");
    for (i=0;i<h->size;i++) {
	printf("%d ", h->indexMap[i]);
    }
    printf("\n");
}

