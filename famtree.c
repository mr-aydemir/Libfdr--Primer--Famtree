#include <stdio.h>

#include <string.h>
typedef struct Person
{
    char name[100];
    char sex[2];
    char Father[100];
    char Mother[100];
    char children[10][100];
} Person;

int main(int argc, char *argv[])
{
    Person people[100];
    FILE *f = fopen("fam2.txt", "r");
    int i = 0;
    int childcount = 0;
    //Dosya Okuma Döngüsü
    char s[100], v[100];
    while /*(scanf("%s %[^\n]", s, v) != EOF)*/(fscanf(f, "%s %[^\n]", s, v) != EOF)
    {
        
        if (strstr(s, "PERSON") != NULL) //if (s == "PERSON") //strstr(s, "PERSON") != NULL
        {

            childcount = 0;
            Person Person;
            strcpy(Person.name, v);

            people[i] = Person;
            i++;
        }

        else if (strstr(s, "FATHER") != NULL&&strstr(s, "FATHER_OF") == NULL)
        {
            strcpy(people[i - 1].Father, v);
        }

        else if (strstr(s, "MOTHER") != NULL&&strstr(s, "MOTHER_OF") == NULL)
        {
            strcpy(people[i - 1].Mother, v);
        }
        
        else if (strstr(s, "FATHER_OF") != NULL || strstr(s, "MOTHER_OF") != NULL) //(s == "FATHER_OF")
        {
            if (strstr(s, "FATHER_OF") != NULL)
            { 
                 strcpy(people[i - 1].sex, "M");
            }
            else  strcpy(people[i - 1].sex, "F");
            
            strcpy(people[i - 1].children[childcount], v);
            childcount++;
        }
        else if (strstr(s, "SEX") != NULL)
        {
            strcpy(people[i - 1].sex,v);
        }
        printf("%d", i);
    }

    int liste_uzunlugu = i;
    //Anne Baba Belirleme Döngüsü
    for (int j = 0; j < i; j++)
    {
        if (strlen(people[j].children[0]) > 0)
        {
            
            for (int p = 0; strlen(people[j].children[p])>0; p++)
            {
                
                for (int t = 0; t < i; t++)
                {
                    if (strstr(people[t].name, people[j].children[p]) != NULL)
                    { 
                        if (strstr(people[j].sex , "M") != NULL)
                        {
                            strcpy(people[t].Father, people[j].name);
                            
                        }
                        else{
                            strcpy(people[t].Mother, people[j].name);
                        }
                        break;
                    }
                }
            }
        }
        if (strlen(people[j].Mother) > 0)
        {
            for (int p = 0; strlen(people[p].name)>0; p++)
            {
                if (strstr(people[p].name, people[j].Mother)!=NULL)
                {
                    int found = 0;
                    int t = 0;
                    for (; strlen(people[p].children[t])>0; t++)
                    {
                        if (strstr(people[p].children[t], people[j].name)!=NULL)
                        {
                            found = 1;
                            break;
                        }
                        
                    }
                    if (!found)
                    {
                        strcpy(people[p].children[t], people[j].name);
                    }
                    break;
                }
                
            }
            
        }
        if (strlen(people[j].Father) > 0)
        {
            for (int p = 0; strlen(people[p].name)>0; p++)
            {
                if (strstr(people[p].name, people[j].Father)!=NULL)
                {
                    int found = 0;
                    int t = 0;
                    for (; strlen(people[p].children[t])>0; t++)
                    {
                        if (strstr(people[p].children[t], people[j].name)!=NULL)
                        {
                            found = 1;
                            break;
                        }
                        
                    }
                    if (!found)
                    {
                        strcpy(people[p].children[t], people[j].name);
                    }
                    break;
                }
                
            }
        }
    }
    
    FILE * fp;
    fp = fopen ("output.txt", "w+");
    //Dosyaya Yazma Döngüsü:
    for (int j = 0; j < i; j++)
    {
        
        char sex[] = "Undefined";
        if (strstr(people[j].sex , "M") != NULL)
        {
            strcpy(sex , "Male");
        }
        else if (strstr(people[j].sex , "F") != NULL)
        {
            strcpy(sex , "Female");
        }

        char mother[100];
        if (strlen(people[j].Mother)>0)
        {
            strcpy(mother, people[j].Mother);
        }
        else strcpy(mother, "Unknown");
        char father[100];
         if (strlen(people[j].Father)>0)
        {
            strcpy(father, people[j].Father);
        }
        else strcpy(father, "Unknown");
        char children[300];
        if (strlen(people[j].children[0])>0)
        {
            char new_line[] = "\n    ";
            strcpy(children, new_line);
            char child[100];
            for (int t = 0; strlen(people[j].children[t])>0; t++)
            {
                strcpy(child, people[j].children[t]);
                strcat(child, new_line);
                strcat(children, child);
            }
        }
        else strcpy(children ,"None\n");
        fprintf(fp, "%s\n  Sex: %s\n  Father: %s\n  Mother: %s\n  Children: %s\n", people[j].name, sex,  father, mother, children);
    }
   fclose(fp);
}