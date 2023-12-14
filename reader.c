#include <stdio.h>
#include <stdlib.h>

#include "reader.h"

static long filesize(FILE *fp) {
	long pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, pos, SEEK_SET);

	return sz;
}

Reader *new_reader(int type, void *arg) {
	Reader *r = calloc(1, sizeof(Reader));

	if (type == READER_FILE) {
		char *filename = ((char*)(*(char**)arg)); 
		r->data.file.fp = fopen(filename, "r");
		if (r->data.file.fp == NULL) {
			fprintf(stderr, "failed to open file: %s", filename);
			exit(1);
		}

		r->data.file.len = filesize(r->data.file.fp);

		r->peek = file_peek;
		r->next = file_next;
		r->isEOF = file_isEOF;
	}
	return r;
}

char file_peek(Reader *r) {
	FILE *fp = r->data.file.fp;
	
	int c = fgetc(fp);
	if (c != EOF)
		ungetc(c, fp);

	return c;
}

char file_next(Reader *r) {
	FILE *fp = r->data.file.fp;
	return fgetc(fp);
}

bool file_isEOF(Reader *r) {
	FILE *fp = r->data.file.fp;
	int c = fgetc(fp);
	if (c == EOF) 
		return true;
	else {
		ungetc(c, fp);
		return false;
	}
}
