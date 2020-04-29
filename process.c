#include "process.h"



void push(queue* q, int x){
	q->_q[q->last++] = x;
}

int pop(queue* q){
	if(q->start==q->last) return -1;
	return q->_q[q->start++];
}

int size(queue* q){
	return q->last-q->start;
}

int front(queue* q){
	if(q->start==q->last) return -1;
	return q->_q[q->start];
}

void showq(queue* q){
	for(int i = q->start; i < q->last; i++){
		printf("%d ", q->_q[i]);
	}
	printf("\n");
}

int inq(queue* q, int x){
	for(int i = q->start; i < q->last; i++){
		if(q->_q[i]==x) return 1;
	}
	return 0;
}

int get_next(process* processes, int n, int p, int *id, int *ctime, int* last, queue* q){
	if(*id!=-1&&(p==0||p==2)){
		return *id;
	}

	if(p==0){
		int t = -1;
		for(int i = 0; i < n; i++){
			if(processes[i].pid==-1||processes[i].et==0){
				continue;
			}
			else{
				if(t==-1||processes[i].rt<processes[t].rt){
					t = i;
				}
			}
		}
		return t;
	}
	else if(p==1){
		//showq(q);
		//printf("%d %d %d\n", processes[0].et, processes[2].et, *ctime);
		if(*id==-1){
			return pop(q);
			/*
			for(int i = 0; i < n; i++){
				if(processes[i].pid!=-1&&processes[i].et>0){
					return i;
				}
			}
			*/
			//return -1;
		}
		else if((*ctime-*last)%RRT==0){
			int k = pop(q);
			if(processes[*id].et>0&&!inq(q, *id)&&*id!=k){
				push(q, *id);
			}
			return k;
			/*
			int t = (*id+1)%n;
			//printf("%d %d %d\n", t, processes[t].pid, processes[t].et);
			while(processes[t].pid==-1||processes[t].et==0){
				t = (t+1)%n;
			}
			*/
			//return t;
		}
		else return *id;
	}
	else if(p==2||p==3){
		int t = -1;
		for(int i = 0; i < n; i++){
			if(processes[i].pid==-1||processes[i].et==0){
				continue;
			}
			else{
				if(t==-1||processes[i].et<processes[t].et){
					t = i;
				}
			}
		}
		return t;
	}
	else return -1;

}
