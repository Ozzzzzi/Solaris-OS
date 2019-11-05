#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SIZE 256
#define FILESIZE 65536

typedef struct {
	int pos;
	int length;
} str_t;

int makeTable(int file, str_t** table) {
	char c;
	int cnt = 0;
	read(file, &c, 1);
	for (int i = 1; c != EOF; i++) {
		while (c == '\t') {
			cnt++;
			read(file, &c, 1);
		}
		table[i]->pos = cnt;
		while ((c != '\n') && (c != EOF)) {
			cnt++;
			read(file, &c, 1);
		}
		table[i]->length = cnt - table[i]->pos;
		cnt++;
		read(file, &c, 1);
			
	}
	return cnt;
}

void printstr(int file, str_t** table, int num) {
	char buf[SIZE];
	off_t offset = table[num]->pos;
	int length = table[num]->length;
	lseek(file, offset, SEEK_SET);
	read(file, buf, length);
	write(1, buf, length);
	return;
}

int getNum5() {
	int num;

	printf("Enter the string number within five seconds:\n");
	sleep(5);
	read(0, &num, sizeof(int));
	return num;
}

void printfile(int file, int length) {
	char buf[FILESIZE];
	lseek(file, 0, SEEK_SET);
	read(file, buf, length);
	write(1, buf, length);
	return;
}

int main() {	
	int file = open(file, O_RDONLY);
	str_t table[256];
	int num, cnt;

	makeTable(file, &table);
	num = getNum5();
	
	while (num != 0) {
		if (read(0, &num, sizeof(int)) == 0) {
			printFile(file, cnt);
			exit(1);			
		}
		printstr(file, &table, num);
		num = getNum5();
	}
	exit(EXIT_SUCCESS);
}


