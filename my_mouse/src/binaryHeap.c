#include <binaryHeap.h>

static void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

static void heapMemoryInc(struct heap* self)
{
    if ((self->size + 2) == self->maxSize)
    {
        self->maxSize *= 2;
        self->array = (int*)realloc(self->array, sizeof(int) * self->maxSize);
    }
}

static void heapMemoryDec(struct heap* self)
{
    if ((self->size + 2) == self->maxSize / 2)
    {
        self->maxSize /= 2;
        self->array = (int*)realloc(self->array, sizeof(int) * self->maxSize);
    }
}

static void minHeapify(struct heap* self, int index)
{
    int left = 2 * index + 1;
	int right = 2 * index + 2;
    int smallest = index;
    if (right < self->size && self->array[right] < self->array[smallest])
        smallest = right;
    if (left < self->size && self->array[left] < self->array[smallest])
        smallest = left;
    if (smallest != index)
    {
        swap(&self->array[index], &self->array[smallest]);
        minHeapify(self, smallest);
    }
}

static void insert(struct heap* self, int value)
{
    if (self->size == 0)
    {
        self->size += 1;
        self->array = (int*)malloc(sizeof(int) * self->maxSize);
        self->array[0] = value;
        return;
    }
    else
    {
        heapMemoryInc(self);
        self->array[self->size] = value;
        self->size += 1;
        for (int i = ((self->size / 2) - 1); i >= 0; i--)
		    minHeapify(self, i);
    }
}

static bool isEmpty(struct heap* self)
{
    if (self->size == 0) return true;
    else return false;
}

static int pop(struct heap* self)
{
    if (!isEmpty(self))
    {
        int minHeap = self->array[0];
        self->size -= 1;
        swap(&self->array[0], &self->array[self->size]);
        heapMemoryDec(self);
        minHeapify(self, 0);
        return minHeap;
    }
    else
    {
        fprintf(stderr, "Error: the heap is empty\n");
        exit(1);
    }
}

static int peek(struct heap* self)
{
    if (!isEmpty(self))
    {
        return self->array[0];
    }
    else
    {
        fprintf(stderr, "Error: the heap is empty\n");
        exit(1);
    }
}

static struct heap new()
{
    return (struct heap){
        .value = 0,
        .size = 0,
        .array = NULL,
        .maxSize = MAXHEAP,
        .insert = (void*)&insert,
        .pop = (void*)&pop,
        .peek = (void*)&peek,
        .isEmpty = (void*)&isEmpty};
}

const struct heapClass heap = {
    .new = &new,
};