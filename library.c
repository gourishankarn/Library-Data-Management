#include <stdio.h>#include <string.h>
#include <stdlib.h>
#include <time.h>
 
 
int DisplayMenu();
int ReturnToMenu();
int AddBooks(char *filename);
 
 
typedef struct node
{
    char title[90];
    char reader_name[30];
    double unix_date;
    struct node *next;
}book;
 
 
int DisplayMenu()
{
    system("cls");
 
 
    int choice;
    printf("*****MENU***** \n\n"
        "1. Add books \n"
        "2. Remove books \n"
        "3. Find a book \n"
        "4. Find a reader \n"
        "5. Find overdue positions \n"
        "6. Exit \n\n");
    scanf("%d", &choice);
 
 
    return choice;
}
 
 
int main()
{
    int choice;
    while ((choice = DisplayMenu()) != 6)
    {
        switch (choice)
        {
        case 1:
            AddBooks("database.txt");
            break;
        case 2:
             
        case 3:
 
 
        case 4:
 
 
        case 5:
 
 
        default:
            printf("Invalid selection. Try again.\n");
        }
    }
    system("cls");
    printf("The program will exit. Press any key to continue.\n");
 
 
    system("pause");
    return 0;
}
 
 
int ReturnToMenu()
{
    int back;
 
 
    printf("Would you like to return to the Menu[1] or exit[0] the program?\n\n");
    scanf("%d", &back);
 
 
    while (back != 0)
    {
        switch (back)
        {
        case 1:
            DisplayMenu();
            break;
 
 
        default:
            printf("Invalid selection. Try again.\n");
        }
    }
    printf("The program will exit. Press any key to continue.\n");
 
 
    return back;
}
 
 
int AddBooks(char *filename)
{
    FILE *fp;
    book newbook;
    struct tm date;
 
 
    system("cls");
 
 
    fp = fopen(filename, "wb");
    if (!fp)
    {
        printf("Error reading database file!\n");
        return -1;
    }
    else
    {
        int flag = 0;
        do
        {
            printf("Please type in the book's title: \n");
            gets(newbook.title);
            if (strcmp(newbook.title, "") == 0)
            {
                printf("Wrong input. Try again.\n");
                flag = 1;
                system("cls");
            }
            else
            {
                flag = 0;
            }
        } while (flag == 1);
 
 
        int flag0 = 0;
        do
        {
            printf("\nPlease type in the reader's name: \n");
            gets(newbook.reader_name);
            if (strcmp(newbook.reader_name, "") == 0)
            {
                printf("Wrong input. Try again.\n");
                flag0 = 1;
                system("cls");
            }
        } while (flag0 == 1);
 
 
        int d, m, y;
        int days_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int minyear = 1900;
        printf("\nPlease enter the date of rent:\n\n");
 
 
        int flag1 = 0;
        do
        {
            printf("Year(yyyy):\t");
            scanf("%d", &y);
            if (y < minyear)
            {
                printf("Wrong input. Try again.\n\n");
                flag1 = 1;
            }
            else if ((y % 4) == 0 && y % 100 != 0 || y % 400 == 0)
            {
                days_month[2] = 29;
                flag1 = 0;
            }
            else
            {
                days_month[2] = 28;
                flag1 = 0;
            }
        } while (flag1 == 1);
 
 
        int flag2 = 0;
        do
        {
            printf("\nMonth(mm):\t");
            scanf("%d", &m);
            if (m < 1 || m>12)
            {
                printf("Wrong input. Try again.\n\n");
                flag2 = 1;
            }
            else
                flag2 = 0;
        } while (flag2 == 1);
 
 
        int flag3 = 0;
        do
        {
            printf("\nDay(dd):\t");
            scanf("%d", &d);
            if (d < 1 || d>days_month[m])
            {
                printf("Wrong input. Try again.\n\n");
                flag3 = 1;
            }
            else
                flag3 = 0;
        } while (flag3 == 1);
 
 
        date.tm_mday = d;
        date.tm_mon = m - 1;
        date.tm_year = y - 1900;
 
 
        newbook.unix_date = mktime(&date);
 
 
        fwrite(&newbook, sizeof(book), 1, fp);
 
 
        system("cls");
        printf("Item successfully added to the registry.\n\n");
 
 
        fclose(fp);
    }
    ReturnToMenu();
}