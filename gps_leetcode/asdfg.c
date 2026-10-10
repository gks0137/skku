#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct _Queue {
  int front, rear;
  int items[MAX_SIZE];
} Queue;

Queue createQueue();
void removeQueue(Queue *queue);

bool isEmpty(Queue *queue);
bool isFull(Queue *queue);
void enqueue(Queue *queue, int item);
int dequeue(Queue *queue);
int peek(Queue *queue);
void printItems(Queue *queue);

void push(Queue *queue1, Queue *queue2, int item);
int pop(Queue *queue1, Queue *queue2);

int main() {
  Queue queue;

  // Create a queue
  queue = createQueue();

  enqueue(&queue, 1);
  enqueue(&queue, 3);
  enqueue(&queue, 2);
  printItems(&queue);

  dequeue(&queue);
  enqueue(&queue, 4);
  printItems(&queue);

  printf("Front: %d\n", peek(&queue));
  enqueue(&queue, 10);
  printItems(&queue);

  // Remove the queue
  removeQueue(&queue);
  return 0;
}

Queue createQueue() {
  // Write your own code
  Queue newQueue;
  newQueue.front = newQueue.rear = -1;
  return newQueue;
}

void removeQueue(Queue *queue) {
  // Nothing to do
}

bool isEmpty(Queue *queue) {
  // Write your own code
  return queue->front == queue->rear;
}

bool isFull(Queue *queue) {
  // Write your own code
  return queue->rear == MAX_SIZE-1;
}

void enqueue(Queue *queue, int item) {
  // Write your own code
  if (isFull(queue)) {
    printf("Error: queue is already full\n");
    return;
  }
  queue->rear++;
  queue->items[queue->rear] = item;
}

int dequeue(Queue *queue) {
  // Write your own code
  if (isEmpty(queue)) {
    printf("Error: queue is empty\n");
    return 0;
  }
  queue->front++;
  return = queue->items[queue->front];
}

int peek(Queue *queue) {
  // Write your own code
  return = queue->items[queue->front];
}

void printItems(Queue *queue) {
  if (isEmpty(queue)) {
    printf("Queue: empty\n");
    return;
  }

  printf("Queue: ");
  for (int i = queue->front; i < queue->rear; i ++) {
    printf("%d ", queue->items[i]);
  }
  printf("\n");
}