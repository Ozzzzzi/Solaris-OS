#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <ulimit.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char* optarg;
extern char** environ;


void printugid() {
	uid_t uid = getuid();
	printf("real uid: %d\n", uid);
	uid_t euid = geteuid();
	printf("effective uid: %d\n", euid);	
	gid_t gid = getgid();
	printf("real gid: %d\n", gid);
	gid_t egid = getegid();
	printf("effective gid: %d\n", egid);
}


void groupLeader() {
	pid_t pid = getpid();
	setpgid(pid, pid);
}


void printpid(){
	pid_t pid = getpid();
	printf("process id: %d\n", pid);
	pid = getppid();
	printf("parent process id: %d\n", pid);
	pid = getpgid(NULL);
	printf("process group id: %d\n", pid);
}


void printulim() {
	long ulim = ulimit(UL_GETFSIZE);
	printf("Soft file size limit: %ld\n", ulim);
}


void setNewLim() {
	long new_lim = atol(optarg);
	if (ulimit(UL_SETFSIZE, new_lim) == -1) 
		printf("Incorrect size\n");
	else 
		printf("New limit set\n");
}


void printCore() {
	struct rlimit core_lim;
	getrlimit(RLIMIT_CORE, &core_lim);
	printf("Core limit: %d\n", core_lim.rlim_cur);
}


void setCore() {
	struct rlimit cur_lim;
	getrlimit(RLIMIT_CORE, &cur_lim);
	struct rlimit new_lim;
	new_lim.rlim_cur = (rlim_t)optarg;
	new_lim.rlim_max = RLIM_SAVED_MAX;
	if (setrlimit(RLIMIT_CORE, &new_lim) == -1)
		printf("Incorrect size\n");
	else
		printf("New limit set\n");
}


void printCurDir() {
	char *cur_dir = getcwd(NULL, 0);
	if (cur_dir != NULL) {
		printf("Current working directory: %s\n", cur_dir);
		free(cur_dir);
	}
}


void printEnv() {
	char ** envp;
	for (enp = environ; *envp; envp++)
		printf("%s\n", *envp);
}


void setEnv() {
	if (putenv(optarg) != NULL) 
		printf("Some problem\n");
	else 
		printf("Enviroment var set\n");
}


int main(int argc, char *argv[]) {
	char* options = "ispuU:cC:dvV:";
 	while ((c = getopt(argc, argv, options)) != -1) {
        	switch(c) {
        	case 'i':
            		printugid();
            		break;
        	case 's':
           		groupLeader();
            		break;
        	case 'p':
            		printpid();
            		break;
        	case 'u':
            		printulim();
            		break;
		case 'U':
            		setNewLim();
            		break;
		case 'c':
            		printCore();
            		break;
		case 'C':
            		setCore();
            		break;
		case 'd':
            		printCurDir();
            		break;
		case 'v':
            		printEnv();
            		break;
		case 'V':
            		setEnv();
            		break;
        	case ':':
            		printf("Option -%c requires an operand\n", optopt);
			break;
        	case '?':
            		printf("Unrecognized option: -%c\n", optopt);
        	} 
    }
	return 0;
}