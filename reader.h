#ifndef _READER_H
#define _READER_H

#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

/* to expand later */ 
enum reader_type { READER_FILE };

typedef struct Reader {
	enum reader_type type;
	char (*peek)(struct Reader *r); /* read n characters from input stread without consuming input */
	char (*next)(struct Reader *r); /* read and consume n characters from input stread */
	bool (*isEOF)(struct Reader *r);
	union {
		struct {
			FILE *fp;
			size_t len;
		} file;
	} data;
} Reader;

/* generic methods */ 

Reader *new_reader(int type, void *arg);

#define reader_peek(r) r->peek(r)
#define reader_next(r) r->next(r)
#define reader_isEOF(r) r->isEOF(r)

/* reader type specific methods */

char file_peek(Reader *r);
char file_next(Reader *r);
bool file_isEOF(Reader *r);

#endif 
