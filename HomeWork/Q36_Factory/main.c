#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b)) 

typedef struct node_s {
    int machine;
    int time;
    struct node_s* next;
} node_t;

node_t* createNode(int machine, int time) {
    node_t* new = (node_t*)malloc(sizeof(node_t));
    new->machine = machine;
    new->time = time;
    new->next = NULL;
    return new;
}

void add(node_t** node, int machine, int time) {
    node_t* new = createNode(machine, time);

    if (*node == NULL) {
        *node = new;
        return;
    }

    node_t* current = *node;
    while (current->next != NULL)
        current = current->next;
    
    current->next = new;
}

void pop(node_t** node) {
    node_t* tmp = *node;
    *node = (*node)->next;
    free(tmp);
}

typedef struct job_s {
    int totalTime;
    node_t* process;
} job_t;

void solve(job_t *jobList, int jobCount, int *bots) {
    while (true)
    {
        bool ALL_DONE = true;

        // find min
        job_t *minJob = &jobList[0];
        int minTime = 99999;

        for (int i = 0; i < jobCount; i++) {
            if (jobList[i].process == NULL)
                continue;

            job_t* currentJob = &jobList[i];
            int currentMinTime = MAX(bots[currentJob->process->machine], currentJob->totalTime) + currentJob->process->time;

            if (currentMinTime < minTime) {
                minTime = currentMinTime;
                minJob = currentJob;
            }
            ALL_DONE = false;
        }
        if (ALL_DONE)
            break;

        bots[minJob->process->machine] = minTime;
        minJob->totalTime = minTime;
        pop(&minJob->process);
    }
}

int main(void) {
    int machineCount, jobCount;
    scanf("%d %d", &machineCount, &jobCount);

    job_t jobList[jobCount];
    int bots[jobCount];

    for (int i = 0; i < jobCount; i++) {
        jobList[i].process = NULL;
        jobList[i].totalTime = 0;
        bots[i] = 0;

        int processCount;
        scanf("%d", &processCount);

        for (int j = 0; j < processCount; j++) {
            int machine, time;
            scanf("%d %d", &machine, &time);

            add(&jobList[i].process, machine, time);
        }
    }
    solve(jobList, jobCount, bots);

    int total = 0;
    for (int i = 0; i < jobCount; i++) {
        total += jobList[i].totalTime;
    }
    printf("%d\n", total);
}
