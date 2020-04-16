#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
#include <string.h>
#include <math.h>
#include "process.h"

int cmp(const process* a, const process* b){
	return a->rt>b->rt;
}

int execute(process p){
	int pid = fork();
	long start, end;
	
	if(pid==0){
		int pd = getpid();
		start = syscall(GET_TIME);

		for(int j = 0; j < p.et; j++){
			volatile unsigned long i;
			for(i = 0; i < 1000000UL; i++);		
		}
		
		end = syscall(GET_TIME);
	
		syscall(PRINT, pd, start, end, 11111);
		long base = 1e9;
		//fprintf(stderr, "[Project1] %d %ld.%09ld %ld.%09ld\n", pd, start/base, start%base, end/base, end%base);
		exit(0);
	}
	return pid;
}

void start_scheduling(process* processes, int n, int p){
	int ctime = 0, id = -1, nfinish = 0, last = 0;
	
	cpu_set_t mask, mask1;
	CPU_ZERO(&mask);
	CPU_SET(0, &mask);
	CPU_ZERO(&mask1);
	CPU_SET(1, &mask1);

	sched_setaffinity(getpid(), sizeof(mask), &mask);

	struct sched_param param, _param;
	param.sched_priority = sched_get_priority_max(p==1?SCHED_RR:SCHED_FIFO);
	_param.sched_priority = 0;

	sched_setscheduler(getpid(), SCHED_OTHER, &_param);

	while(1){
		//printf("t: %d %d\n", ctime, procesmakses[0].rt);
		if(id!=-1&&processes[id].et==0){
			waitpid(processes[id].pid, NULL, 0);
			
			printf("%s %d\n", processes[id].name, processes[id].pid);
			fflush(stdout);
			id = -1;
			if(++nfinish==n){
				break;			
			}
		}
		for(int i = 0; i < n; i++){
			if(processes[i].rt==ctime){
				//printf("%d %d", ctime, processes[i].rt);
				int p = execute(processes[i]);
				processes[i].pid = p;
				sched_setscheduler(p, SCHED_IDLE, &param);
			}			
		}
		
		int next = get_next(processes, n, p, &id, &ctime, &last);
		if(next!=-1&&id!=next){
			//printf("%d %d\n", ctime, next);
			sched_setscheduler(processes[next].pid, SCHED_OTHER, &param);
			sched_setscheduler(processes[id].pid, SCHED_IDLE, &_param);
			last = ctime;
			id = next;
		}
		
		volatile unsigned long i;
		for(i = 0; i < 1000000UL; i++);
		if(id!=-1){
			processes[id].et--;
		}
		ctime++;
	}
	return 0;
}


int main(){
	char policy[110];
	int n;

	scanf("%s", policy);
	scanf("%d", &n);
		
	process* processes;
	processes = (process* )malloc(n*sizeof(process));
	for(int i = 0; i < n; i++){
		scanf("%s%d%d", processes[i].name, &processes[i].rt, &processes[i].et);
		processes[i].pid = -1;
	}	
	
	int p = -1;
	if(strcmp(policy, "FIFO")==0){
		p = 0;
	}
	else if(strcmp(policy, "RR")==0){
		p = 1;	
	}
	else if(strcmp(policy, "SJF")==0){
		p = 2;	
	}
	else if(strcmp(policy, "PSJF")==0){
		p = 3;	
	}
	else{
		printf("Policy not found!\n");
		return -1;
	}
	
	qsort(processes, n, sizeof(process), cmp);
	
	/*
	for(int i = 0; i < n; i++){
		printf("%s: %d\n", processes[i].name, processes[i].rt);
	}
	*/	
	
	start_scheduling(processes, n, p);

	return 0;
}
