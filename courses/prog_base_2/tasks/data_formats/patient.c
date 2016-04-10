#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"

#include "patient.h"

typedef struct
{
    char lastname[100];
    char specialization[100];
}Doctor;

struct patient_s
{
    char name[100];
    char lastname[100];
    char diagnosis[100];
    Doctor * doctor;
    int age;
    double mass;
};

patient_t * patient_new()
{
    patient_t * patient = malloc(sizeof(struct patient_s));
    return patient;
}

void patient_delete(patient_t * patient)
{
    free(patient);
}

char * patient_getText(const char * filename)
{
    FILE * fr = fopen(filename, "r");
    char str[1000];
    char * text;
    char line[1000];
    while(fgets(line, 1000, fr) != NULL)
    {
        strcat(str, line);
    }
    text = strstr(str, "[");
    printf("%s", text);
    return text;
}

void patient_parse(char * text, patient_t * patients[])
{
	cJSON * jList = cJSON_Parse(text);
	if (!jList)
    {
		printf("Error before: [%s]\n", cJSON_GetErrorPtr());
		return;
	}

    int count = cJSON_GetArraySize(jList);
    for (int i = 0; i < count; i++) {
        cJSON * jItem = cJSON_GetArrayItem(jList, i);
        strcpy(patients[i]->name, cJSON_GetObjectItem(jItem, "name")->valuestring);
        strcpy(patients[i]->lastname, cJSON_GetObjectItem(jItem, "lastname")->valuestring);
        strcpy(patients[i]->diagnosis, cJSON_GetObjectItem(jItem, "diagnosis")->valuestring);
        patients[i]->age = cJSON_GetObjectItem(jItem, "age")->valueint;
        patients[i]->mass = cJSON_GetObjectItem(jItem, "mass")->valuedouble;
        cJSON * jDoctor = cJSON_GetObjectItem(jItem, "doctor");
        strcpy(patients[i]->doctor->lastname, cJSON_GetObjectItem(jDoctor, "lastname")->valuestring);
        strcpy(patients[i]->doctor->specialization, cJSON_GetObjectItem(jDoctor, "specialization")->valuestring);
    }
    for (int i = 0; i < count; i++)
    {
        printf("Name: \t%s\nSurname: \t%s\nYear: \t%i\nScore:\t%f\nBirth:\t%s\n", patients[i]->name, patients[i]->lastname, patients[i]->diagnosis, patients[i]->age, patients[i]->mass);
        printf("Group:\t%s (%s)\n\n", patients[i]->doctor->lastname, patients[i]->doctor->specialization);
    }
    cJSON_Delete(jList);
}





