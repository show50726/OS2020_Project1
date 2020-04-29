#include <linux/kernel.h>
#include <linux/linkage.h>
<<<<<<< HEAD
#include <linux/syscalls.h>
SYSCALL_DEFINE3(printm, int, pid, long, start, long, end){
=======
SYSCALL_DEFINE3(sys_printm, int, pid, long, start, long, end){
>>>>>>> 9c1610810431ae821ccf2b58584dc984cf37a0a6
	static const long ns = 1000000000;
    	printk(KERN_INFO "[Project1] %d %ld.%09ld %ld.%09ld\n", pid, start/ns, start%ns, end/ns, end%ns);
    	return 0;
}
