#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "prioq.h"

#define BUF_SIZE 1024

static char buf[BUF_SIZE];

struct config {
    // You can ignore these options until/unless you implement the
    // bonus features.

    // Set to 1 if -y is specified, 0 otherwise.
    int year;
};

static
int parse_options(struct config *cfg, int argc, char *argv[]);

typedef struct {
    char *name;
    int age;
} patient_t;

static int compare_patient_name(const void *a, const void *b)
{
    return strcmp(((const patient_t *) a)->name,
            ((const patient_t *) b)->name);
}

static int compare_patient_age(const void *a, const void *b)
{
    return (((const patient_t* ) a)->age - ((const patient_t* ) b)->age);
}

void free_func(void* patient) {
    patient_t* p = (patient_t *) patient;
    free(p->name);
    free(p);
}

void print_and_free(prioq* queue) {
    patient_t* patient;
    while ( (patient = prioq_pop(queue)) ) {
        printf("%s\n", patient->name);
        free_func(patient);
    }
}

int main(int argc, char *argv[]) {
    char *token, *name_cpy;
    prioq *queue;
    struct config cfg;

    if (parse_options(&cfg, argc, argv) != 0) {
        return EXIT_FAILURE;
    }

    if (cfg.year) {
        queue = prioq_init(&compare_patient_age);
    } else {
        queue = prioq_init(&compare_patient_name);
    }

    for (int iterations = 0;;) {
        while (1) {
            char *s = fgets(buf, BUF_SIZE, stdin);
            
            if (s == NULL) {
                prioq_cleanup(queue, free_func);
                fprintf(stderr, "Unexpected end of file. exiting\n");
                return EXIT_FAILURE;
            }
            
            if (s[0] == '.') {
                break;
            }

            token = strtok(s, " ");
            name_cpy = malloc(strlen(token) + 1);

            if (name_cpy == NULL) {
                prioq_cleanup(queue, free_func);
                return 1;
            }

            strcpy(name_cpy, token);
            int age = (int) atoi(strtok(NULL, s));

            patient_t* patient = malloc(sizeof(patient_t));

            if (patient == NULL) {
                prioq_cleanup(queue, free_func);
                return 1;
            }
            patient->name = name_cpy;
            patient->age = age;
            // printf("name: %s\n", patient->name);
            // printf("age: %d\n", patient->age);

            prioq_insert(queue, patient);

        }

        patient_t* patient = prioq_pop(queue);

        if (patient != NULL) {
            printf("%s\n", patient->name);
            free_func(patient);
        } 
        
        printf(".\n"); // End turn.

        if (++iterations == 10) {

            print_and_free(queue);

            break;
        }
    }

    prioq_cleanup(queue, free_func);

    return EXIT_SUCCESS;
}

int parse_options(struct config *cfg, int argc, char *argv[]) {
    memset(cfg, 0, sizeof (struct config));
    int c;
    while ((c = getopt (argc, argv, "y")) != -1) {
        switch (c) {
            case 'y': cfg->year = 1; break;
            default:
                fprintf(stderr, "invalid option: -%c\n", optopt);
                return 1;
        }
    }
    return 0;
}
