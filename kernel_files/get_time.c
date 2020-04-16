#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
asmlinkage long sys_get_time(void) {
  struct timespec t;

  getnstimeofday(&t);

  long total = 1000000000*t.tv_sec+t.tv_nsec;
  return total;

  return 0;
}
