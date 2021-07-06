#include <stdio.h>
#include <string.h>

char * getNextLine(const char * curLine, int * curLineLen) {
    const char * nextLine = strchr(curLine, '\n');

    *curLineLen = nextLine ? (nextLine - curLine) : strlen(curLine);
 
    return nextLine ? (nextLine + 1) : NULL;
}


int grep(const char * string, const char * pattern, char * line, int line_max_size) {

    const char * curLine  = string;
    const char * nextLine;
    int          curLineLen;
    
    while (curLine) {
       nextLine = getNextLine(curLine, &curLineLen);
 
       if (curLineLen > line_max_size)
          return -1;

       memcpy(line, curLine, curLineLen);
       line[curLineLen] = '\0';

       if (strstr(line, pattern))
         return 1;

       curLine = nextLine;
    }

    return 0;
}


int getBlockNum(char *line) {
    int dev, block;
    int ret;
    if ( (ret = sscanf(line, "%d | %d", &dev, &block)) >= 2) 
       return block;

    printf("%s: ret = %d\n", __func__, ret);
    return -1;
}


int parse_print_vxlan_mac_tbl(char *line, int *num, int *bridge, int *vid, char *mac, int *eport, char *interface, int *type) {
    int ret;
    char type_str[100];
    if ( (ret = sscanf(line, "| %d | %d | %d | %50s | %d | %50s | %6s |", num, bridge, vid, mac, eport, interface, type_str)) >= 7) {
       
       printf("<%s>\n", type_str);
       if (! strcmp(type_str, "static"))
            *type = 1;
       else if ( ! strcmp(type_str, "dynamic"))
            *type = 2;
       else
            *type = 0;
 
       return 1;
    }

    printf("%s: ret = %d\n", __func__, ret);
    return 0;
}


char output[] = "DevIdx | Block | Client |    Client Description    | BlockIdx | Counter Format\n"
                "------ | ----- | ------ | ------------------------ | -------- | --------------\n"
                "     0 |     0 |     13 | TTI_PARALLEL_0           |        0 |              0\n"
                "     0 |     1 |     15 | IPCL0_PARALLEL_0         |        0 |              0\n"
                "     0 |     2 |     19 | IPCL1_PARALLEL_0         |        0 |              0\n\n";                                                                            
char mac_tbl[] = "|  #  | bridgeID | VID  |    MAC address    | ePort | interface  |   type   |\n"
                 "| --- | -------- | ---- | ----------------- | ----- | ---------- | -------- |\n"
                 "|   0 |     1    | 4078 | 00:01:02:03:04:05 |  257  | te2        | dynamic  |\n\n";

int main() 
{
    int result;
    char line[1000] = {0};

    result = grep(output, "IPCL0_PARALLEL_0", line, 1000);
    printf("line:\n%s\n", line);

    printf("Block number = %d\n", getBlockNum(line));
   
    result = grep(mac_tbl, "00:01:02:03:04:05", line, 1000);
    int n, b, v, e, t;
    char interface[100];
    char mac[100];
    parse_print_vxlan_mac_tbl(line, &n, &b, &v, mac, &e, interface, &t);
    printf("Type = %d\n", t);  
 
    return 0;
}


