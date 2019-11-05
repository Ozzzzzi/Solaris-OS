#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SIZE 256

typedef struct {
	int pos;
	int length;
} str_t;

void makeTable(int file, str_t** table) {
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
	return;
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

int getNum() {
	int num;

	printf("Enter the string number:\n");
	read(0, &num, sizeof(int));
	return num;
}

int main() {	
	int file = open(file, O_RDONLY);
	str_t table[256];
	int num;

	makeTable(file, &table);
	num = getNum();

	while (num != 0) {
		printstr(file, &table, num);
		num = getNum();
	}
	exit(EXIT_SUCCESS);
}


