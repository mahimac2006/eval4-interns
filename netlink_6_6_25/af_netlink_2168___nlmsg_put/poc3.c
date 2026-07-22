/*
 * Minimal validation PoC: verify the kernel and user-space work
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(void)
{
	printf("Test PoC: starting\n");
	fflush(stdout);

	/* Do a simple syscall to make sure we're running */
	int ret = syscall(SYS_gettid);
	printf("Test PoC: gettid=%d\n", ret);
	fflush(stdout);

	sleep(1);

	printf("Test PoC: done, exiting cleanly\n");
	fflush(stdout);
	return 0;
}
