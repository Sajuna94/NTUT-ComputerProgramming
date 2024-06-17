// not a good question
// reference xinchen-8 github user

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NODE_COUNT 100

typedef struct node_s{
    int time;
    int waiteNodeNum;
    int waiteNode[NODE_COUNT];
    // struct node_s* next;
} node_t;

void DFS(node_t **nodeList, int now, int* timeList) {
    for (int i = 0; i < nodeList[now]->waiteNodeNum; i++) {
        int wait = nodeList[now]->waiteNode[i];

        if (timeList[wait] < timeList[now] + nodeList[wait]->time) {
            timeList[wait] = timeList[now] + nodeList[wait]->time;
            DFS(nodeList, wait, timeList);
        }
    }
}

int main(void) {
    int projectCount; scanf("%d", &projectCount);

    for (int i = 0; i < projectCount; i++) {
        int jobCount; scanf("%d", &jobCount);
        node_t* nodeList[jobCount];

        for (int jobIndex = 0; jobIndex < jobCount; jobIndex++) {
            node_t* job = (node_t*)malloc(sizeof(node_t));

            // init node
            scanf("%d %d", &job->time, &job->waiteNodeNum);
            for (int j = 0; j < job->waiteNodeNum; j++) {
                scanf("%d", &job->waiteNode[j]);
                job->waiteNode[j]--;
            }
            // init graph
            nodeList[jobIndex] = job;
        }

        // init time list
        int timeList[jobCount];
        for (int j = 0; j < jobCount; j++) {
            timeList[j] = nodeList[j]->time;
        }
        
        DFS(nodeList, 0, timeList);

        int max = 0;
        for (int j = 0; j < jobCount; j++) {
            max = max > timeList[j] ? max : timeList[j];
        }
        printf("%d\n", max);
    }
}
