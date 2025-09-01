/*
 * Ed = editor 
 * osotn: August 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define OPT_STRING "sp:"
void help(void)
{
        printf("\nUsage\n"
               "ed [options] [<filename>]\n"
               "\nOptions:\n"
               "  <filename>            If present, ed shall simulate e command on\n"
               "                        the file name.\n"
               "  -p <string>           Use string as the prompt in command mode.\n"
               "                        By default, there shall be no prompt string.\n"
               "  -s                    Suppress for writing of byte counts by\n"
               "                        e,E,r,w commands and the ! prompt after !command.\n"
               );
}

const char *g_filename = NULL;
const char *g_prompt = NULL;
bool        g_suppress_byte_count = false;

void free_globals(void)
{
        free((void*)g_filename);
        free((void*)g_promt);
}

int get_opts(int argc, char *argv[])
{
        int opt;

        while ((opt = getopt(argc, argv, OPT_STRING)) != -1) {
                switch (opt) {
                        case 's':
                                printf("option: %c\n", opt);
                                g_suppress_byte_count = true;
                                break;
                        case 'p':
                                printf("option 'p' arg = %s\n", optarg);
                                g_prompt = strdup(optarg);
                                break;
                        case '?':
                                printf("unknown option %c\n", optopt);
                                return 1;
                }
        }

        /* optind */
        printf("optind =  %d\n", optind);

        if (optind < argc) {
                g_filename = strdup(argv[optind]);
        }

        if (g_filename) {
                printf("filename = %s\n", g_filename);
        }

        return 0;
}

int main(int argc, char *argv[])
{
        int i;

        /* argv */
        printf("argc = %d\n", argc);
        for (i = 0; i < argc; i++) {
                printf("argv[%d] = %s\n", i, argv[i]);
        }

        if (get_opts(argc, argv)) {
                help();
                return 1;
        }

        /* argv */
        printf("argc = %d\n", argc);
        for (i = 0; i < argc; i++) {
                printf("argv[%d] = %s\n", i, argv[i]);
        }

        free_globals();
        return 0;
}

/* EOF */

