 
/******************************************************************************
CSE 1310 Fall 2021
File name: SXR9995Lab3Part1.c

Author: Shah Arifur Rahman Rhyme

Created on: 11/19/2021

UTA STUDENT NAME: Shah Arifur Rahman Rhyme
UTA ID: 1001909995
*******************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define LN 25
#define lengTH 30


/*
 LAB-3 PART=2
 */

int checkDate(int day, int month, int year);
int checkLeap(int yr);
void errorMsgs(int flag);

void printAmerDate( int day, int month, int year);
void printEuroDate( int day, int month, int year);
void printISODate( int day, int month, int year);
void printSpaceDate( int day, int month, int year);

void blankLn(void);
void blankLns(int n);

int addYear(int year);
int priorMonthDays(int month, int year);
void printDateAEI(int day, int month, int year);
// Add any new function declaration headers below this comment

void happyBirthday(int bday, int bmonth, int byear, int cday, int cmonth, int cyear);
 
int findAge(int fileYr, int presentYr, int age); 
int findOldest(int dead[25],double age[25] , int j );
int findYoungest (int dead[25],double age[25], int j);


 /*
 * Dr T given code for Lab 2 - dates section
 * Use all of this given code, then add the code as directed for Lab 2
 */

const int DY = 0;
const int MO = 1;
const int YR = 2;
const int REL = 0;
const int LAST = 1;
const int FIRST = 2;
const int AGE = 3;

int main(int argc, char * argv[])
{
    // Do not change any of the given code in main
    // Add your new code after the comment marked with ***
    
    
   
    int day, month, year;
    int invalid = 0;    // used as a boolean flag
    int format = 0;
    
    int currentday, currentmonth, currentyear;
    
    // From https://www.techiedelight.com/print-current-date-and-time-in-c/
        // time_t is arithmetic time type declared in header file time.h  
        time_t now;

        // Obtain current time
        // time() returns the current time of the system as a time_t value
        time(&now);

        // Convert to local time format and print to stdout
        //printf("Today is : %s", ctime(&now));
        

        // localtime converts a time_t value to calendar time and
        // returns a pointer to a tm structure with its members
        // filled with the corresponding values
        struct tm *local = localtime(&now);

        currentday = local->tm_mday;			// get day of month (1 to 31)
        currentmonth = local->tm_mon + 1;   	// get month of year (0 to 11)
        currentyear = local->tm_year + 1900;	// get year since 1900   
       // printf("Today is : ");
        //printSpaceDate(currentday, currentmonth, currentyear);


    
   //*****************************2b)
   FILE * ptr = NULL;
   char filename[20];
   printf("please enter the file name:\n");
   scanf("%s",filename);
   
   ptr = fopen(filename,"r");
   
   
char fileN[30];
strcpy(fileN, "peopleOut.txt");
FILE * OUTfile=fopen(fileN, "w+");
  
   
  int dates[25][3];
  double age[25];
  char name[LN][3][lengTH];
  char gender[25];
  
  int dead[25];
  char inFile[128];
  
  
  //*****************************2c)
  int j=0;
  char tmp;
  while(!feof(ptr))
  {
      fgets(inFile,128,ptr);
      sscanf(inFile,"%s %lf %c %d %d %d %[^',']%c%c %[^\n] ",name[j][REL],&age[j],&gender[j],
      &dates[j][DY],&dates[j][MO],&dates[j][YR],name[j][LAST],&tmp,&tmp, name[j][FIRST]);
      j++;
  }
 
  printf("%-20s %-20s %-5s %-15s %-6s %20s\n\n","first","last","Age","Birthday","Gender","Relationship");
  fprintf(OUTfile,"%-20s %-20s %-5s %-15s %-6s %20s\n\n","first","last","Age","Birthday","Gender","Relationship");

  
  for (int i=0; i<j; i++)
  {
      printf("%-20s %-20s %-5.2f %2d/%2d/%-9d %-6c %20s\n",name[i][FIRST],name[i][LAST],age[i],dates[i][MO],
      dates[i][DY],dates[i][YR],gender[i],name[i][REL]);
      
      //**2h
       fprintf(OUTfile,"%-20s %-20s %-5.2f %2d/%2d/%-9d %-6c %20s\n",name[i][FIRST],name[i][LAST],age[i],dates[i][MO],
      dates[i][DY],dates[i][YR],gender[i],name[i][REL]);
  }
  
 //***********************************2e)   
for (int k=0; k<j; k++)
 {
      
      dead[k] = findAge(dates[k][YR], currentyear,age[k]);
      //printf("dead[%d]=%d\n",k,dead[k]);
        if(dead[k]==0)
        {
            printf("%s %s, my %s, passed away at age %0.1f\n",name[k][FIRST],name[k][LAST],name[k][REL],age[k]);
            
            fprintf(OUTfile,"%s %s, my %s, passed away at age %0.1f\n",name[k][FIRST],name[k][LAST],name[k][REL],age[k]);
        }
  } 
            

 
 //************************************2f)
 int oldestPerson= findOldest( dead, age ,  j);
 printf("At age %.2f , %s %s was born on %d/%d/%d and is the oldest living person in the file\n", age[oldestPerson],
                                                   name[oldestPerson][FIRST],name[oldestPerson][LAST],
                                                  dates[oldestPerson][MO],dates[oldestPerson][DY],dates[oldestPerson][YR]);
 //**2h
 fprintf(OUTfile,"At age %.2f , %s %s was born on %d/%d/%d and is the oldest living person in the file\n", age[oldestPerson],
                                                name[oldestPerson][FIRST],name[oldestPerson][LAST],
                                                  dates[oldestPerson][MO],dates[oldestPerson][DY],dates[oldestPerson][YR]);                                                  
 
 
 //************************************2g)
 int youngestPerson= findYoungest(dead, age ,  j);
 printf("At age  %d/%d/%d, %s %s has the most recent birthdate in the file ",dates[youngestPerson][MO],
                                dates[youngestPerson][DY],dates[youngestPerson][YR],
                                name[youngestPerson][FIRST],name[youngestPerson][LAST] );
 
 //**2h
 fprintf(OUTfile,"At age  %d/%d/%d, %s %s has the most recent birthdate in the file ",dates[youngestPerson][MO],dates[youngestPerson][DY],dates[youngestPerson][YR],
                                name[youngestPerson][FIRST],name[youngestPerson][LAST] );                               
                                                  
 
 
 
   // end if valid 
   return (EXIT_SUCCESS);
}
 


void happyBirthday(int bday, int bmonth, int byear, int cday, int cmonth, int cyear)
{
    if (bmonth < cmonth)
        printf("\nI hope you had a great birthday earlier this year!\n");
    else if (bmonth > cmonth)
        printf("\nBest wishes for a great birthday later this year!\n");
    else if (bday < cday)
        printf("\nI hope you had a great birthday earlier this month!\n");
    else if (bday > cday)
        printf("\nBest wishes for a great birthday later this month!\n");
    else
        printf("\nTODAY is your birthday!  Have a happy one!\n");
}

/*
    Note:  There are many ways to correctly calculate the age.
    Again, this is an EXAMPLE of how to do it
*/



// ALL FUNCTIONS BELOW HERE SHOULD BE THE FUNCTIONS GIVEN BY DR T.  
// DO NOT CHANGE ANY OF THE GIVEN FUNCTIONS BELOW 
// BUT YOU CAN ADD SIMILAR FUNCTIONS ABOVE IF NEEDED
 


int findAge(int fileYr, int presentYr, int age)
{
    if( (presentYr-fileYr == age) || (presentYr-fileYr == age-1) || (presentYr-fileYr == age+1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int findOldest(int dead[25],double age[25] , int j )
{
    int rowNum=0;
    double maxAge=0;
    for (int m=0; m<j; m++)
    {
        if((age[m]>maxAge) && dead[m]==1)
        {
         maxAge=age[m];
         rowNum=m;
        }
    }
    return rowNum;
}

int findYoungest (int dead[25],double age[25], int j)
{
    int rowCNT=0;
    double minAge=150;
    for (int r=0; r<j; r++)
    {
        if ((age[r]<minAge) && dead[r]==1)
        {
            minAge=age[r];
            rowCNT=r;
        }
    }
    return rowCNT;
    
}


