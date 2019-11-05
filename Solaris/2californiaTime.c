#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	time_t time_cal;
	setenv("TZ", "America/Los_Angeles", 0);
	time(&time_cal);
	printf("%s\n", ctime(&time_cal));
	return 0;
}


