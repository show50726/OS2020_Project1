#include "process.h"

int get_next(process* processes, int n, int p, int *id, int *ctime, int* last){
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
		if(*id==-1){
			for(int i = 0; i < n; i++){
				if(processes[i].pid!=-1&&processes[i].et>0){
					return i;
				}
			}
			return -1;
		}
		else if((*ctime-*last)%RRT==0){
			int t = (*id+1)%n;
			//printf("%d %d %d\n", t, processes[t].pid, processes[t].et);
			while(processes[t].pid==-1||processes[t].et==0){
				t = (t+1)%n;
			}
			return t;
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
