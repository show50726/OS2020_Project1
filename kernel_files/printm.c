#include <linux/kernel.h>
#include <linux/linkage.h>
SYSCALL_DEFINE3(sys_printm, int pid, long start, long end){
	static const long ns = 1000000000;
    	printk(KERN_INFO "[Project1] %d %ld.%09ld %ld.%09ld\n", pid, start/ns, start%ns, end/ns, end%ns);
    	return 0;
}
