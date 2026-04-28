#define COMP ==
#define TEST >=
typedef long data_t;

int test(data_t a, data_t b) {
    return a TEST b;
}

int compare(data_t a, data_t b) {
    return a COMP b;
}

