#include "geom.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void arrowin(int id)
{
    for (int i = 0; i <= id; i++)
    {
        if (i == id)
        {
            printf("^\n");
            break;
        }
        printf(" ");
    }
}
int zap_id(char *ptr)
{
    int zapid, c = 0;
    for (unsigned int i = 0; i < strlen(ptr); i++)
    {
        if (ptr[i] == ',')
        {
            break;
        }
        c++;
    }
    zapid = c;
    return zapid;
}
int skob_id(char *ptr)
{
    int skobid, c = 0;
    for (unsigned int i = 0; i < strlen(ptr); i++)
    {
        if (ptr[i] == ')')
        {
            break;
        }
        c++;
    }
    skobid = c;
    return skobid;
}
int skob_id2(char *ptr)
{
    int skobid, c = 0;
    for (unsigned int i = 0; i < strlen(ptr); i++)
    {
        if (ptr[i] == '(')
        {
            break;
        }
        c++;
    }
    skobid = c;
    return skobid;
}
int prob_id1(char *ptr)
{
    int probid1, c = 0;
    for (unsigned int i = 0; i < strlen(ptr); i++)
    {
        if (ptr[i] == ' ')
        {
            break;
        }
        c++;
    }
    probid1 = c;
    return probid1;
}
int prob_id2(char *ptr)
{
    int probid2, c = 0;
    for (unsigned int i = 0; i < strlen(ptr); i++)
    {
        if ((ptr[i] == ' ') && (c == 2))
        {
            break;
        }
        c++;
    }
    probid2 = c;
    return probid2;
}
int rad_id(char *ptr, char *rad)
{
    int zapid = zap_id(ptr);
    int radidfoo = zapid;
    int radid;
    for (unsigned int i = zapid; i < strlen(ptr); i++)
    {
        if (ptr[i] == rad[0])
        {
            radid = radidfoo;
            break;
        }
        radidfoo++;
    }
    return radid;
}
void radius(char *ptr, char *rad)
{
    int t = 0;
    int zapid = zap_id(ptr);
    int skobid = skob_id(ptr);
    for (int j = zapid + 2; j < skobid; j++)
    { // заполнение радиуса
        rad[t] = ptr[j];
        t++;
    }
}
void sixcheck(char *ptr)
{
    int skobid = skob_id2(ptr);
    char name[100] = {'0'};
    for (int i = 0; i < skobid; i++)
    {
        name[i] = ptr[i];
    }
    if (strlen(name) > 6)
    {
        arrowin(strlen(name) - 1);
        printf(" Error at column %lld: unexpected tocken", strlen(name) - 1);
        exit(0);
    }
    for (unsigned int i = 0; i < strlen(name); i++)
    {
        if (name[0] == 'c')
        {
            if (name[1] == 'i')
            {
                if (name[2] == 'r')
                {
                    if (name[3] == 'c')
                    {
                        if (name[4] == 'l')
                        {
                            if (name[5] == 'e')
                            {
                            }
                            else
                            {
                                arrowin(5);
                                printf("Error at column 5: expected 'circle'");
                                exit(0);
                            }
                        }
                        else
                        {
                            arrowin(4);
                            printf("Error at column 4: expected 'circle'");
                            exit(0);
                        }
                    }
                    else
                    {
                        arrowin(3);
                        printf("Error at column 3: expected 'circle'");
                        exit(0);
                    }
                }
                else
                {
                    arrowin(2);
                    printf("Error at column 2: expected 'circle'");
                    exit(0);
                }
            }
            else
            {
                arrowin(1);
                printf("Error at column 1: expected 'circle'");
                exit(0);
            }
        }
        else
        {
            arrowin(0);
            printf("Error at column 0: expected 'circle'");
            exit(0);
        }
    }
}
void namecheck(char *ptr, struct figura *circle, char *rad)
{
    char *fl = NULL;
    int c = 0;
    for (int i = 0; i < 7; i++)
    { // заполнение буквами
        if ((ptr[i] > 96) && (ptr[i] < 123))
        {
            c++;
        }
    }
    if (((ptr[0] == 'c') && (ptr[1] == 'i') && (ptr[2] == 'r') // проверка на ввод фигуры
         && (ptr[3] == 'c') && (ptr[4] == 'l') && (ptr[5] == 'e') && (ptr[6] == '(')))
    {
        for (unsigned int i = 0; i < sizeof(ptr); i++)
        {
            circle->x = ptr[7] - 48;
            circle->y = ptr[9] - 48;
        }
        circle->radius = strtod(rad, &fl);
        float area = 3.1415926 * (circle->radius * circle->radius);
        float per = 2 * 3.1415926 * circle->radius;
        printf("perimetr: %f\n", per);
        printf("area: %f\n", area);
    }
    else
    {
        if ((ptr[6] != '('))
        { // проверка на скобку '('
            arrowin(6);
            printf("Error at column 6: expected '('\n");
            exit(0);
        }
        else
        {
            arrowin(0);
            printf("Error at column 0: expected 'circle'\n");
            exit(0);
        }
    }
}
void xcheck(char *ptr)
{
    int c = 0;
    int probid1 = prob_id1(ptr);
    int minusid = 0;
    for (int i = 7; i < probid1; i++)
    {
        if (((ptr[i] < 48) || (ptr[i] > 57)) && (ptr[i] != '-') && (ptr[i] != '.'))
        {
            arrowin(i);
            printf("Error at acolumn %d: <double> expected\n", i);
            exit(0);
        }
        if (ptr[i] == '-')
        {
            c++;
            minusid = i;
        }
    }
    if (c > 1)
    {
        arrowin(minusid);
        printf("Error at acolumn %d: unexpected '-'\n", minusid);
        exit(0);
    }
}
void ycheck(char *ptr)
{
    int c = 0;
    int minusid = 0;
    int probid1 = prob_id1(ptr);
    int zapid = zap_id(ptr);
    int arrow = probid1 + 1;
    for (int i = probid1 + 1; i < zapid; i++)
    {
        if (((ptr[i] < 48) || (ptr[i] > 57)) && (ptr[probid1 + 1] != '-') && (ptr[i] != '.'))
        {
            arrowin(arrow);
            printf("Error at column %d: <double> expected\n", probid1 + 1);
            exit(0);
        }
        if (ptr[i] == '-')
        {
            c++;
            minusid = i;
        }
    }
    if (c > 1)
    {
        arrowin(minusid);
        printf(" Error at column %d: unexpected '-'\n", minusid);
        exit(0);
    }
}
void radcheck(char *rad, char *ptr)
{
    int zapid = zap_id(ptr);
    int arrow = 0;
    for (unsigned int i = 0; i < strlen(rad); i++)
    {
        if (((rad[i] < 48) || (rad[i] > 57)) && (rad[i] != '.') && (rad[i] != '-'))
        {
            arrow = i + zapid + 2;
            arrowin(arrow);
            printf("Error at column %d: <double> expected\n", i + zapid + 2);
            exit(0);
        }
    }
}
void probelcheck1(char *ptr)
{
    int c = 0;
    int zapid = zap_id(ptr);
    int problemzapid = 0;
    int probid1 = 0;
    int arrow = 0;
    for (int i = 0; i < zapid; i++)
    {
        if (ptr[i] == ' ')
        {
            problemzapid = probid1;
            c++;
        }

        probid1++;
    }
    if (ptr[7] == ' ')
    {
        arrow = 7;
        arrowin(arrow);
        printf("Error at column 7: unexpected: ' '\n");
        exit(0);
    }
    if (c > 1)
    {
        arrow = problemzapid;
        arrowin(arrow);
        printf("Error at column %d: unexpected: ' '\n", problemzapid);
        exit(0);
    }
}
void radminus(char *ptr, char *rad)
{
    int radid = rad_id(ptr, rad);
    int arrow = 0;
    for (unsigned int i = 0; i < strlen(rad); i++)
    {
        if (rad[0] == '-')
        {
            arrow = radid;
            arrowin(arrow);
            printf("Error at column %d: radius positive expected\n", arrow);
            exit(0);
        }
        else if (rad[i] == '-')
        {
            arrow = radid + i;
            arrowin(arrow);
            printf("Error at column %d: unexpected '-'\n", arrow);
            exit(0);
        }
    }
}
void unexpected_check(char *ptr)
{
    int skobid = skob_id(ptr) + 1;
    int arrow = 0;
    for (unsigned int i = skobid; i < strlen(ptr); i++)
    {
        if (ptr[i] != '\n')
        {
            arrow = skobid;
            arrowin(arrow);
            printf("Error at column %d: unexpected tocken\n", skobid);
            exit(0);
        }
    }
}
void skobcheck(char *ptr, char *rad)
{
    int arrow = 0;
    int radid = rad_id(ptr, rad);
    if (ptr[radid + strlen(rad)] != ')')
    {
        arrow = radid + strlen(rad);
        arrowin(arrow);
        printf("Error at column %d: expected ')'\n", arrow);
        exit(0);
    }
}
