#include <stdio.h>
#include <stdlib.h>

#include <libxml/tree.h>
#include <libxml/parser.h>

#include "patient.h"

patient_t patient_new()
{
    patient_t pt = (patient_t) malloc(sizeof(patient_s));
    return pt;
}

void patient_delete(patient_t self)
{
    free(self);
}

void patient_setParametr(patient_t self, const char * parametr, const char * field)
{
    if(!strcmp(field, "name"))
        {
        strcpy(self->name, parametr);
    }
    else if(!strcmp(field, "lastname"))
    {
        strcpy(self->lastname, parametr);
    }
    else if(!strcmp(field, "hospitalisedDate"))
    {
        strcpy(self->hospitalisedDate, parametr);
    }
    else if(!strcmp(field, "mass"))
    {
        self->mass = atof(parametr);
    }
    else if(!strcmp(field, "age"))
    {
        self->age = atoi(parametr);
    }
}

char * patient_ConvertToString(patient_t self, char * buff)
{
    sprintf(buff, "patient %s %s:\nhospitalisedDate %s;\nmass %d age %f", self->name, self->lastname, self->hospitalisedDate, self->age, self->mass);
    return buff;
}

void patient_convertFromXml(patient_t self, xmlDocPtr doc, xmlNodePtr patientNode)
{
    for (xmlNodePtr cur = patientNode->xmlChildrenNode; cur != NULL; cur = cur->next)
        {
        if (!xmlStrcmp(cur->name, (const xmlChar *)"name"))
        {
            xmlChar * name = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            strcpy(self->name, (const char *) name);
            free(name);
        }
        else if (!xmlStrcmp(cur->name, (const xmlChar *)"lastname"))
        {
            xmlChar * lastname = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            strcpy(self->lastname, (const char *) lastname);
            free(lastname);
        }
        else if (!xmlStrcmp(cur->name, (const xmlChar *)"hospitalisedDate"))
        {
            xmlChar * hospitalisedDate = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            strcpy(self->hospitalisedDate, (const char *) hospitalisedDate);
            free(hospitalisedDate);
        }
        else if (!xmlStrcmp(cur->name, (const xmlChar *)"mass"))
        {
            xmlChar * str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            self->mass = atof((const char *) str);
            free(str);
        }
        else if (!xmlStrcmp(cur->name, (const xmlChar *)"age"))
        {
            xmlChar * str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            self->age = atoi((const char *) str);
            free(str);
        }
    }
}

void patient_convertToXml(patient_t self, xmlDocPtr doc, xmlNodePtr parent)
{
    char buff[100];
    xmlNodePtr patientNode = NULL;
    if(parent != NULL)
    {
        patientNode = xmlNewChild(parent, NULL, "patient", NULL);
    }
    else
    {
        patientNode = xmlNewNode(NULL, "patient");
        xmlDocSetRootElement(doc, patientNode);
    }

    xmlNewChild(patientNode, NULL, "name", self->name);
    xmlNewChild(patientNode, NULL, "lastname", self->lastname);
    xmlNewChild(patientNode, NULL, "hospitalisedDate", self->hospitalisedDate);
    sprintf(buff, "%f", self->mass);
    xmlNewChild(patientNode, NULL, "mass", buff);
    sprintf(buff, "%i", self->age);
    xmlNewChild(patientNode, NULL, "age", buff);
}

char * patient_convertToXmlString(patient_t self, char * buff)
{
	xmlChar * str = NULL;
    xmlDoc * doc = NULL;
	doc = xmlNewDoc("1.0");
	patient_convertToXml(self, doc, NULL);
	xmlDocDumpMemory(doc, &str, NULL);
	strcpy(buff, str);
	free(str);
    xmlFreeDoc(doc);
    return buff;
}


