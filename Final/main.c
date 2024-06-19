#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct task_s {
    int botIndex, time;
    struct task_s *next;

    int jobIndex;
} Task;

typedef struct job_s {
    int numTask;
    Task *taskList;

    int timeTotal;
} Job;

typedef struct bot_s {
    int timeTotal;
    Task *taskList;
} Bot;

Task* createTask(int botIndex, int time, int jobIndex) {
    Task *new = (Task*)malloc(sizeof(Task));
    new->botIndex = botIndex;
    new->time = time;
    new->next = NULL;
    new->jobIndex = jobIndex;
    return new;
}
void add(Task** task, Task* newTask) {
    if (*task == NULL) {
        *task = newTask;
    } else {
        Task* current = *task;
        while (current->next != NULL)
            current = current->next;        
        current->next = newTask;
    }
}
void pop(Task** task) {
    Task* tmp = *task;
    *task = (*task)->next;
    free(tmp);
}

void solve(int numBot, int numJob, Bot *botList, Job *jobList) {
    while (true)
    {
        // find min
        int minTime = 999999;
        Job *minJob = NULL;

        for (int i = 0; i < numJob; i++) {
            Job *currentJob = &jobList[i];
            if (currentJob->taskList == NULL)
                continue;

            Task *task = currentJob->taskList;
            int currentTime = MAX(botList[task->botIndex].timeTotal, currentJob->timeTotal) + task->time;

            if (currentTime < minTime) {
                minTime = currentTime;
                minJob = currentJob;
            }
        }

        // check finish
        if (minJob == NULL)
            break;
        
        // set min data
        Task* task = minJob->taskList;

        botList[task->botIndex].timeTotal = minTime;
        minJob->timeTotal = minTime;

        add(&botList[task->botIndex].taskList, createTask(task->botIndex, task->time, task->jobIndex));
        pop(&minJob->taskList);
    }
}

int main(void) {
    int printMode; scanf("%d", &printMode);
    int numBot, numJob; scanf("%d %d", &numBot, &numJob);

    Bot *botList = (Bot*)malloc(numBot * sizeof(Bot));
    Job *jobList = (Job*)malloc(numJob * sizeof(Job));
    
    for (int i = 0; i < numBot; i++) {
        botList[i].timeTotal = 0;
        botList[i].taskList = NULL;
    }

    for (int i = 0; i < numJob; i++) {
        Job *job = &jobList[i];

        // init job
        scanf("%d", &job->numTask);
        job->taskList = NULL;
        job->timeTotal = 0;

        for (int t = 0; t < job->numTask; t++) {
            // init task
            int botIndex, time; scanf("%d %d", &botIndex, &time);
            add(&job->taskList, createTask(botIndex, time, i));
        }
    }

    solve(numBot, numJob, botList, jobList);

    // print
    if (printMode == 1) {
        for (int i = 0; i < numBot; i++) {
            for (Task* cur = botList[i].taskList; cur; cur = cur->next) {
                printf("%d ", cur->jobIndex + 1);
            }
            printf("\n");
        }
    }
    else {
        int total = 0;
        for (int i = 0; i < numJob; i++)
            total += jobList[i].timeTotal;
        printf("%d\n", total);
    }
}
