#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/utsname.h>

/* Helper: insmod a .ko file */
static int insmod(const char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0) return -1;
	
	/* Use finit_module or init_module syscall */
	long ret = syscall(__NR_finit_module, fd, "", 0);
	close(fd);
	
	if (ret < 0) return -1;
	return 0;
}

int main(void)
{
	struct utsname un;
	char path[256];
	int fd;
	
	uname(&un);
	printf("[*] Kernel release: %s\n", un.release);

	/* Try loading .ko from various locations */
	const char *locations[] = {
		"/lib/modules/psmgr.ko",
		"/root/psmgr.ko",
		"/psmgr.ko",
		"/tmp/psmgr.ko",
		"/lib/modules/6.6.25/psmgr.ko",
		"/lib/modules/6.6.25/kernel/net/psmgr/psmgr.ko",
		"/lib/modules/6.12.28/psmgr.ko",
		NULL
	};
	
	for (int i = 0; locations[i]; i++) {
		fd = open(locations[i], O_RDONLY);
		if (fd >= 0) {
			printf("[*] Found: %s\n", locations[i]);
			close(fd);
			
			/* Try to insmod */
			printf("[*] Trying insmod %s...\n", locations[i]);
			int ret = insmod(locations[i]);
			if (ret == 0) {
				printf("[*] insmod succeeded!\n");
			} else {
				printf("[*] insmod failed: %m\n");
			}
		}
	}

	/* Check if module appeared */
	printf("[*] Checking /proc/modules for psmgr...\n");
	{
		char buf[4096];
		fd = open("/proc/modules", O_RDONLY);
		if (fd >= 0) {
			int n = read(fd, buf, sizeof(buf)-1);
			if (n > 0) buf[n] = 0;
			close(fd);
			char *p = buf;
			char *line;
			while ((line = strsep(&p, "\n")) != NULL) {
				if (strstr(line, "psmgr"))
					printf("FOUND: %s\n", line);
			}
		}
	}

	/* Try socket again */
	printf("[*] Trying AF_PSMGR socket...\n");
	fd = socket(46, 5, 0);
	if (fd < 0) {
		printf("[*] socket failed: %m\n");
	} else {
		printf("[*] SUCCESS! fd=%d\n", fd);
		close(fd);
	}

	printf("[*] Done.\n");
	return 0;
}
