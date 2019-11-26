typedef struct Queue 
{ 
	int front, rear, size; 
	unsigned capacity; 
	void** array; 
}Queue; 

// function to create a queue of given capacity. 
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity);

// Queue is full when size becomes equal to the capacity 
int isFull(Queue* queue);
int isEmpty(Queue* queue);
// Function to add an item to the queue. 
// It changes rear and size 
void enqueue(Queue* queue, void* item);
// Function to remove an item from queue. 
// It changes front and size 
void* dequeue(Queue* queue);

// Function to get front of queue 
void* front(Queue* queue);

// Function to get rear of queue 
void* rear(Queue* queue);