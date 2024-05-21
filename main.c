#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int num_io_ops;
    int io_remaining;
    int waiting_time;
    int time_in_q1;
    struct Process* next;
} Process;

typedef struct Queue {
    Process* front;
    Process* rear;
} Queue;

void enqueue(Queue* q, Process* p) {
    if (q->rear == NULL) {
        q->front = q->rear = p;
    } else {
        q->rear->next = p;
        q->rear = p;
    }
    p->next = NULL;
}

Process* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    Process* temp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

int is_empty(Queue* q) {
    return q->front == NULL;
}

void round_robin(Queue* q0, Queue* q1, int quantum, int io_device_time) {
    int time = 0;
    printf("Diagrama de Gantt:\n");

    while (!is_empty(q0) || !is_empty(q1)) {
        // Process Q0
        if (!is_empty(q0)) {
            Process* process = dequeue(q0);
            if (process->remaining_time > quantum) {
                printf("P%d (%d - %d)\n", process->id, time, time + quantum);
                time += quantum;
                process->remaining_time -= quantum;
                enqueue(q1, process);
            } else {
                printf("P%d (%d - %d)\n", process->id, time, time + process->remaining_time);
                time += process->remaining_time;
                process->remaining_time = 0;
                if (process->io_remaining > 0) {
                    process->io_remaining--;
                    process->remaining_time = io_device_time;
                }
            }
        }

        // Process Q1
        else if (!is_empty(q1)) {
            Process* process = dequeue(q1);
            process->time_in_q1 += quantum;  
            if (process->time_in_q1 >= 30) {  
                enqueue(q0, process);
            } else {
                if (process->remaining_time > 0) {
                    printf("P%d (%d - %d)\n", process->id, time, time + process->remaining_time);
                    time += process->remaining_time;
                    process->remaining_time = 0;
                }
                enqueue(q1, process);  
            }
        }
    }
}

int main() {
    Queue q0 = {NULL, NULL};
    Queue q1 = {NULL, NULL};

    // Entrada de dados (exemplo)
    Process p0 = {0, 50, 50, 1, 1, 0, 0, NULL};
    Process p1 = {1, 20, 20, 2, 2, 0, 0, NULL};

    enqueue(&q0, &p0);
    enqueue(&q0, &p1);

    int quantum = 10;
    int io_device_time = 20;

    round_robin(&q0, &q1, quantum, io_device_time);

    return 0;
}
