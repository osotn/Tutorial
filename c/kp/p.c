/* p: print input in chuncks (version 4) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGESIZE	22

char *progname;	/* program name for error messages */

int spname(char *oldname, char *newname);	/* correct spelled filename */
FILE *efopen(char *file, char *mode);	/* fopen file, die if can't */
void print(FILE *fp, int pagesize);	/* print fp in pagesize chunks */
int ttyin(void);			/* process response from /dev/tty */

int main(int argc, char *argv[])
{
	int i, pagesize = PAGESIZE;
	FILE *fp;
	char buf[BUFSIZ];

	progname = argv[0];

	if (argc > 1 && argv[1][0] == '-') {
		pagesize = atoi(&argv[1][1]);
		argc--;
		argv++;
	}

	if (argc == 1)
		print(stdin, pagesize);
	else
 		for (i = 1; i < argc; i++) {
			switch (spname(argv[i], buf)) {
			case -1: 	/* no match possible */
				fp = efopen(argv[i], "r");
				break;
			case 1:		/* corrected */
				fprintf(stderr, "\"%s\"? ", buf);
				if (ttyin() == 'n')
					break;
				argv[i] = buf;
				/* fall through... */
			case 0:
				fp = efopen(argv[i], "r");
				print(fp, pagesize);
				fclose(fp);
				break;
			}
		}
	return 0;
}



/* 
 * correct spelled filename.
 * returns 	-1 if no reasonable match to oldname,
 *		 0 if exact match,
 *		 1 if corrected.
 * stores corrected name in newname.
 */
#include <dirent.h>

int mindist(char *dir, char *guess, char *best);	/* search dir for guess */
int spdist(char *s, char *t);	/* distance between two names */

int spname(char *oldname, char *newname)
{
	char *p, guess[BUFSIZ], best[BUFSIZ];
	char *new = newname, *old = oldname;

	for (;;) {
		while (*old == '/')	/* skip slashes */
			*new++ = *old++;
		*new = '\0';
		if (*old == '\0')	/* exact to corrected */
			return strcmp(oldname, newname) != 0;
		p = guess;	/* copy next component into guess */
		for ( ; *old != '/' && *old != '\0'; old++)
			if (p < guess + BUFSIZ-1)
				*p++ = *old;
		*p = '\0';
		if (mindist(newname, guess, best) >= 3)
			return -1;	/* hopeless */
		for (p = best; *new = *p++; )	/* add to end */
			new++;			/* of newname */
	}
}

/* set best, return distance 0..3 */
int mindist(char *dir_name, char *guess, char *best)
{
	int d, nd;
	DIR *dir;
	struct dirent *entry;

	if (dir_name[0] == '\0')	/* current directory */
		strcpy(dir_name, ".");
	d = 3;	/* minimun distant */
	if ((dir = opendir(dir_name)) == NULL) {
		perror("opendir() error");
		return d;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_ino) {
			nd = spdist(entry->d_name, guess);
			if (nd <= d && nd != 3) {
				strcpy(best, entry->d_name);
				d = nd;
				if (d == 0)	/* exact match */
					break;
			}
		}
	}
	closedir(dir);
	return d;
}


/*
 * return distance between two names.
 *
 * very rough spelling metric:
 * 	0 if the strings are identical
 * 	1 if two chars are transposed
 *	2 if one char wrong, added or deleted
 * 	3 otherwise  
 */
#define EQ(s,t) (strcmp(s,t) == 0)

int spdist(char *s, char *t)
{
	while (*s++ == *t)
		if (*t++ == '\0')
			return 0;
	if (*--s) {
		if (*t) {
			if (s[1] && t[1] && *s == t[1] &&
			    *t == s[1] && EQ(s+2, t+2))
				return 1;	/* transposition */
			if (EQ(s+1, t+1))
				return 2;	/* 1 char mismatch */
		}
		if (EQ(s+1, t))
			return 2;		/* extra character */
	}
	if (*t && EQ(s, t+1))
		return 2;			/* missing character */
	return 3;
}

FILE *efopen(char *file, char *mode)
{
	FILE *fp;

	if ((fp = fopen(file, mode)) != NULL)
		return fp;

	fprintf(stderr, "%s: can't open file %s mode %s\n",
		progname, file, mode);
	exit(1);
	return NULL; /* never return */
}

void print(FILE *fp, int pagesize)
{
	static int lines = 0;	/* number of lines so far */
	char buf[BUFSIZ]; 

	while (fgets(buf, sizeof buf, fp) != NULL)
		if (++lines < pagesize)
			fputs(buf, stdout);
		else {
			buf[strlen(buf)-1] = '\0';
			fputs(buf, stdout);
			fflush(stdout);
			ttyin();
			lines = 0;
		}
}

int ttyin(void)
{
	char buf[BUFSIZ];
	static FILE *tty = NULL;

	if (tty == NULL)
		tty = efopen("/dev/tty", "r");

	for (;;) {
		if (fgets(buf, sizeof buf, tty) == NULL || buf[0] == 'q')
			exit(0);
		else if (buf[0] == '!') {
			system(buf + 1);	/* BUG here */
			printf("!\n");
		}
		else
			return buf[0];
	}
}
	
