#include <stdio.h>
#include <stdlib.h>

#include "patient.h"
#include "cJSON.h"

#define PAT_NUM 3

int main()
{
    const char * filename = "patient.json";
    patient_t * patients[PAT_NUM];
    for(int i = 0;i<PAT_NUM;i++)
    {
        patients[i] = patient_new();
    }
    char * text = patient_getText(filename);
    patient_parse(text, patients);
    for(int i = 0;i<PAT_NUM;i++)
    {
        patient_delete(patients[i]);
    }
	return 0;
}


