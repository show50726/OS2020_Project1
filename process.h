#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define _NS 1e9
#define RRT 500
#define GET_TIME 337
#define PRINT 336
#define ll long long

typedef struct process{
	char name[110];
	int rt;
	int et;
	pid_t pid;
} process;

typedef struct queue{
	int start;
	int last;
	int _q[1010];
}queue;

int get_next(process* processes, int n, int p, int *id, int *ctime, int* last, queue* q);
