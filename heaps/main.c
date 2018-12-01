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
    int duration;
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

void release_waiting_patients(prioq* queue) {
    patient_t* patient;
    while ( (patient = prioq_pop(queue)) ) {
        printf("%s\n", patient->name);
        free_func(patient);
    }
    
}

void treat_patient(patient_t** p) {
    if( (*p)->duration <= 1) {
        printf("%s\n", (*p)->name);
        free_func(*p);
        *p = NULL;
    } else {
        (*p)->duration--;
    }        
}

void release_patient_in_treatment(patient_t** p) {
    printf("%s\n", (*p)->name);
    free_func(*p);
    *p = NULL;
}

patient_t* create_patient_from_input(char* input) {
    char *token, *name_cpy;
    char* saveptr = NULL;
    int i = 1, age = 0, duration = 0;
    char* str = NULL;

    for (str = input; ; i++, str = NULL) {
        token = __strtok_r(str, " ", &saveptr);
        if (token == NULL)
            break;

        if (i == 1) {
            name_cpy = malloc(strlen(token) + 1);

            if (name_cpy == NULL) {
                return NULL;
            }

            strcpy(name_cpy, token);
        } else if (i == 2) {
            age = (int) atoi(token);
        } else if (i == 3) {
            duration = (int) atoi(token);
        }
    }

    patient_t* patient = malloc(sizeof(patient_t));

    if (patient == NULL) {
        free(name_cpy);
        return patient;
    }
    
    patient->name = name_cpy;
    patient->age = age;
    
    // check whether duration is provided, else provide default duration
    if (duration != 0) {
        patient->duration = duration;
    } else {
        patient->duration = 1;
    }

    return patient;
}

int main(int argc, char *argv[]) {
    prioq *queue;
    struct config cfg;
    patient_t* patient_in_treatment = NULL;

    if (parse_options(&cfg, argc, argv) != 0) {
        return EXIT_FAILURE;
    }

    if (cfg.year) {
        queue = prioq_init(&compare_patient_age);
    } else {
        queue = prioq_init(&compare_patient_name);
    }

    for (int iterations = 0;;) {
        // Parse input line
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

            patient_t* patient = create_patient_from_input(s);

            if (patient == NULL) {
                prioq_cleanup(queue, free_func);
                return EXIT_FAILURE;
            }

            prioq_insert(queue, patient);
        }
        
        // Make sure there is a patient in treatment or NULL if queue empty
        if (patient_in_treatment == NULL) {
            patient_in_treatment = prioq_pop(queue);
        }
        
        if (patient_in_treatment != NULL) {
            treat_patient(&patient_in_treatment);
        }

        printf(".\n"); // End turn.

        // Work day has ended
        if (++iterations == 10) {
            if (patient_in_treatment != NULL) {
                release_patient_in_treatment(&patient_in_treatment);
            }

            release_waiting_patients(queue);

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
