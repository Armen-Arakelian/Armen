#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>

#include "patient.h"

patient_t patient_new()
{
    patient_t pt = (patient_t) malloc(sizeof(patient_s));
    return pt;
}

void patient_delete(void * self)
{
    free(self);
}

void patient_setParametr(patient_t self, const char * parametr, const char * field)
{
    if(!strcmp(field, "name"))
        {
        strcpy(self->name, parametr);
    }
    else if(!strcmp(field, "disease"))
    {
        strcpy(self->disease, parametr);
    }
    else if(!strcmp(field, "hospitalisedDate"))
    {
        strcpy(self->hospitalisedDate, parametr);
    }
    else if(!strcmp(field, "mass"))
    {
        self->mass = atof(parametr);
    }
    else if(!strcmp(field, "time"))
    {
        self->time = atoi(parametr);
    }
}

char * patient_ConvertToString(patient_t self, char * buff)
{
    sprintf(buff, "patient %s %s:\nhospitalisedDate %s;\nmass %d time %f", self->name, self->disease, self->hospitalisedDate, self->time, self->mass);
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
        else if (!xmlStrcmp(cur->name, (const xmlChar *)"disease"))
        {
            xmlChar * disease = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            strcpy(self->disease, (const char *) disease);
            free(disease);
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
        else if (!xmlStrcmp(cur->name, (const xmlChar *)"time"))
        {
            xmlChar * str = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
            self->time = atoi((const char *) str);
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
        patientNode = xmlNewChild(parent, NULL, (xmlChar *)"patient", NULL);
    }
    else
    {
        patientNode = xmlNewNode(NULL, (xmlChar *)"patient");
        xmlDocSetRootElement(doc, patientNode);
    }

    xmlNewChild(patientNode, NULL, (const xmlChar *)"name", (const xmlChar *)self->name);
    xmlNewChild(patientNode, NULL, (const xmlChar *)"disease", (const xmlChar *)self->disease);
    xmlNewChild(patientNode, NULL, (const xmlChar *)"hospitalisedDate", (const xmlChar *)self->hospitalisedDate);
    sprintf(buff, "%f", self->mass);
    xmlNewChild(patientNode, NULL, (const xmlChar *)"mass", (const xmlChar *)buff);
    sprintf(buff, "%i", self->time);
    xmlNewChild(patientNode, NULL, (const xmlChar *)"time", (const xmlChar *)buff);
}

char * patient_convertToXmlString(patient_t self, char * buff)
{
	xmlChar * str = NULL;
    xmlDoc * doc = NULL;
	doc = xmlNewDoc((xmlChar *)"1.0");
	patient_convertToXml(self, doc, NULL);
	xmlDocDumpMemory(doc, &str, NULL);
	strcpy((char *)buff, (char *)str);
	free(str);
    xmlFreeDoc(doc);
    return buff;
}


