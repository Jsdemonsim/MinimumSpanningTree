#if !defined(__HEAP_H)
#define __HEAP_H

typedef struct MinHeap MinHeap;

MinHeap *Heap_Create(void);
void Heap_Insert(MinHeap *h, int indx, float key);
int  Heap_ExtractMin(MinHeap *h);
int  Heap_Size(const MinHeap *h);
void Heap_DecreaseKey(MinHeap *h, int indx, float key);

#endif
