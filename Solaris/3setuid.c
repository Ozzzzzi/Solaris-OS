#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void check() {
	FILE *fp; 
	uid = getuid();
	euid = geteuid();

	printf("real uid = %5ld; effective uid = %5ld\n", uid, euid);

	if((fp = fopen("answer","r")) == NULL) {
		perror("Cannot open file");
	}
	else {
		printf("Success");
		fclose(fp);
	}
}

int main() {

	check();
	uid = getuid();
	setuid(uid);
	check();

	return 0;
}