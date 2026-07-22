/*
 * PoC: Demonstrate WMI-3 for copy_peercred
 * 
 * Shows that when an attacker process listens on a socket and a victim
 * connects, the victim gets the attacker's credentials in SO_PEERCRED.
 * The sk_peer_pid content is attacker-determined (by the attacker's
 * call to listen()) but is placed in an authoritative position
 * (the connecting socket's peer credentials).
 * 
 * Expected result: victim reads back attacker's pid/uid/gid
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/wait.h>

int main(void)
{
    int fd, ret;
    struct sockaddr_un addr;
    pid_t pid;
    int status;
    
    unlink("/tmp/poc_wmi3.sock");
    
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) { perror("socket"); return 1; }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, "/tmp/poc_wmi3.sock", sizeof(addr.sun_path) - 1);
    
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) { perror("bind"); return 1; }
    
    /* Attacker (this process) listens -> sets sk_peer_* to attacker's creds */
    ret = listen(fd, 8);
    if (ret < 0) { perror("listen"); return 1; }
    
    printf("[+] Server (PASS-attacker, pid=%d) listening\n", getpid());
    
    /* Fork to create a "victim" that connects */
    pid = fork();
    if (pid == 0) {
        /* Child = "victim" */
        int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (cfd < 0) { perror("child socket"); exit(1); }
        
        ret = connect(cfd, (struct sockaddr *)&addr, sizeof(addr));
        if (ret < 0) { perror("child connect"); exit(1); }
        
        /* This triggers copy_peercred() which copies server's creds 
         * (attacker's pid/uid/gid) into client socket's sk_peer_pid 
         * and sk_peer_cred fields.
         * 
         * The attacker-determined content is now in an authoritative
         * position - the victim will read back the attacker's credentials
         * when checking SO_PEERCRED.
         */
        
        struct {
            unsigned int pid;
            unsigned int uid;
            unsigned int gid;
        } cred;
        socklen_t len = sizeof(cred);
        
        ret = getsockopt(cfd, SOL_SOCKET, SO_PEERCRED, &cred, &len);
        if (ret < 0) { perror("getsockopt"); exit(1); }
        
        printf("[victim] Attacker's credentials via SO_PEERCRED: "
               "pid=%u uid=%u gid=%u\n",
               cred.pid, cred.uid, cred.gid);
        printf("[victim] (Expected: pid=%d uid=0 gid=0)\n", getppid());
        
        if (cred.pid == (unsigned int)getppid()) {
            printf("[victim] PASS: Attacker's pid matches!\n");
        } else {
            printf("[victim] FAIL: Wrong pid (expected %d, got %u)\n", 
                   getppid(), cred.pid);
        }
        
        close(cfd);
        exit(cred.pid == (unsigned int)getppid() ? 0 : 1);
    }
    
    /* Parent accepts */
    int afd = accept(fd, NULL, NULL);
    if (afd < 0) { perror("parent accept"); return 1; }
    printf("[+] Parent accepted connection\n");
    
    waitpid(pid, &status, 0);
    
    close(afd);
    close(fd);
    unlink("/tmp/poc_wmi3.sock");
    
    printf("[+] Done\n");
    return 0;
}
