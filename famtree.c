/*Eksikler: 
    Anne Baba çocuklardan önce gelecek. Şekilde düzenli sıralama yaptırılacak.
    Çift anne, baba olma durumu hata mesajı olarak verilecek.
    Bir kadının baba, bir erkeğin anne olması durumu hatası verilecek.
*/
/*Tamamlanan:
    Bahsi geçen ama Person olarak bulunmayan insanlar oluşturulacak, çocuklar anne babalar gibi.
    input dosyası istenen düzende yazdırılacak.
*/

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
    int i = 0; // people listesindeki kişi sayısını tutacak sayı
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
    }

    int liste_uzunlugu = i;
    
    for (int j = 0; j < i; j++)
    {   //Anne Baba Belirleme Döngüsü
        if (strlen(people[j].children[0]) > 0)//çocuğu var mı?
        {
            
            for (int p = 0; strlen(people[j].children[p])>0; p++)//boş elemana kadar kontrol et
            {
                int found = 0;
                for (int t = 0; t < i&&!found; t++)//bütün insanları kontrol etme çocuğu bulma döngüsü
                {
                    if (strstr(people[t].name, people[j].children[p]) != NULL)//çocuk ile bulunan insanın ismi aynı ise
                    { 
                        found = 1;
                        //çocuğu kontrol edilenin cinsiyetine göre baba ve anne bilgisini çocuğun bilgilerine girmek
                        if (strstr(people[j].sex , "M") != NULL)//Male, Erkek ise
                        {
                            strcpy(people[t].Father, people[j].name);
                        }
                        else if(strstr(people[j].sex , "F") != NULL)//Female, Kadın ise
                        {
                            strcpy(people[t].Mother, people[j].name);
                        }
                        else{
                        }
                        break;
                    }
                }
                if (found==0)//çocuk bulunamadı ise oluşturmak için
                {
                    
                    Person Person;
                    strcpy(Person.name, people[j].children[p]);
                    people[i] = Person;
                    if (strstr(people[j].sex , "M") != NULL)//Male, Erkek ise
                    {
                        strcpy(people[i].Father, people[j].name);
                    }
                    else if(strstr(people[j].sex , "F") != NULL)//Female, Kadın ise
                    {
                        strcpy(people[i].Mother, people[j].name);
                    }
                    else{}
                    i++;
                }
                

            }
        }
        
        //Çocuk belirleme döngüleri
        if (strlen(people[j].Mother) > 0)// Annesi belirlenmiş ise
        {
            int found = 0;
            for (int p = 0; strlen(people[p].name)>0; p++)//Boş elamana denk gelene kadar döngü
            {
                
                if (strstr(people[p].name, people[j].Mother)!=NULL)//aranılan kişi bulundu ise 
                {
                    found = 1;
                    int t_found = 0;
                    int t = 0;
                    for (; strlen(people[p].children[t])>0; t++)
                    {
                        if (strstr(people[p].children[t], people[j].name)!=NULL)
                        {
                            t_found = 1;
                            break;
                        }
                        
                    }
                    if (!t_found)
                    {
                        strcpy(people[p].children[t], people[j].name);
                        if (strlen(people[p].sex)<=0)
                        {
                             strcpy(people[p].sex, "F");
                        }
                        
                    }
                    break;
                }
            }
            if (!found)//Anne bulunamadı ise oluşturmak için
            {
                Person Person;
                strcpy(Person.name, people[j].Mother);
                people[i] = Person;
                strcpy(people[i].sex, "F");
                strcpy(people[i].children[0], people[j].name);
                //printf("sex: %s\n", people[i].sex);
                i++;
            }
            
        }
        if (strlen(people[j].Father) > 0)
        {
            int found = 0;
            for (int p = 0; strlen(people[p].name)>0; p++)
            {
                
                if (strstr(people[p].name, people[j].Father)!=NULL)
                {
                    found = 1;
                    int t_found = 0;
                    int t = 0;
                    for (; strlen(people[p].children[t])>0; t++)
                    {
                        if (strstr(people[p].children[t], people[j].name)!=NULL)
                        {
                            t_found = 1;
                            break;
                        }
                        
                    }
                    if (!t_found)
                    {
                        strcpy(people[p].children[t], people[j].name);
                        if (strlen(people[p].sex)<=0)
                        {
                             strcpy(people[p].sex, "M");
                        }
                    }
                    break;
                }
                
            }
            if (!found)//Baba bulunamadı ise oluşturmak için
            {
                Person Person;
                strcpy(Person.name, people[j].Father);
                people[i] = Person;
                strcpy(people[i].sex, "M");
                strcpy(people[i].children[0], people[j].name);
                i++;
            }
        }
        

    }
    //Baba, Anne Çocuklar Sıralı Liste: (Daha tamamlanmadı)
    for (int j = 0; j < i; j++)
    {
        Person family[20];
        if(strlen(people[j].Father)>0){

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