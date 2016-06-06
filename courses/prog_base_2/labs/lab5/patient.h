#ifndef PATIENT_H_INCLUDED
#define PATIENT_H_INCLUDED

#include <libxml/tree.h>
#include <libxml/parser.h>

typedef struct patient_s
{
    int id;
    char name[100];
    char disease[100];
    int time;
    double mass;
    char hospitalisedDate[100];
} patient_s;

typedef patient_s * patient_t;


patient_t patient_new();
void patient_delete(void * self);

void patient_setParametr(patient_t self, const char * parametr, const char * field);
char * patient_ConvertToString(patient_t self, char * buff);
void patient_convertFromXml(patient_t self, xmlDocPtr doc, xmlNodePtr patientNode);
void patient_convertToXml(patient_t self, xmlDocPtr doc, xmlNodePtr parent);

#endif // PATIENT_H_INCLUDED
