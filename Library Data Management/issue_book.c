#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node_s
{
	char name[20];
	char branch[5];
	char usn[20];
	char sem[5];
	char book1[50];
	char book2[50];
	char book3[50];
	int  no_of_books;
	struct node_s *next;
}Node_s;
typedef struct node_l
{
	char book_name[50];
	char authour[50];
	char branch[5];
	int book_remaining;
	struct node_l *next;
}Node_l;
typedef struct student
{
	struct node_s *root;
}STUDENT;

typedef struct library
{
	struct node_l*root;
}LIBRARY;

void disp_l(LIBRARY *l);
void disp_s(STUDENT *s);
void delete_book(LIBRARY *l,char *bk_name);
int search_book_l(LIBRARY*l,char *bk_name);
int book_check(STUDENT *s,char *usn,char *bk_name);
void issue_book(STUDENT*s,LIBRARY *l,char *st_name,char *st_usn,char *st_branch, char *st_sem,char *bk_name); 
void append_csv_l(LIBRARY *l);
void append_csv_s(STUDENT *s);

void main()
{
    STUDENT s;
    LIBRARY l;
    s.root=NULL;
    l.root=NULL;
    append_csv_l(&l);
	disp_l(&l);
    append_csv_s(&s);
    disp_s(&s);             
    int k,j;
    char bk_name[50],bk_athr[30],st_name[20],st_usn[20],st_sem[3],st_branch[5];
    printf("enter name of the book:");
    gets(bk_name);
    k=search_book_l(&l,bk_name);   // this function searches the book and return 1 if book found
      if(k==1) 
        {    
           printf("book found\n");	
	       printf("student usn:"); 
		   gets(st_usn);	
	      	//Check for the constraints like same book issued and no_of_books issued.....
           j=book_check(&s,st_usn,bk_name);
          	if(j==0)                // if this function returns true.........
         	    printf("Book can't be issued\n");
           	else
			   {
		 	    printf("student name:"); 
		    	gets(st_name);
		     	printf("student branch:"); 
		     	gets(st_branch);
		     	printf("student sem:"); 
		     	gets(st_sem);
		        issue_book(&s,&l,st_name,st_usn,st_branch,st_sem,bk_name);
			   }
				
		}
      else if(k==0)
		 {
            printf("Book not found\n"); 
         }
}

int search_book_l(LIBRARY*l,char *bk_name)
{
	Node_l*p=l->root;
    while(p!=NULL && strcmp(p->book_name,bk_name)!=0)
    {
       p=p->next;
    }
    if(p!=NULL)
      return 1;
    else
      return 0;    
}
int book_check(STUDENT *s,char *usn,char *bk_name)
{
	Node_s*p=s->root;
   	if(p==NULL)
   	{
      return 1;
    }
   else 
   {
    while(p!=NULL && strcmp(p->usn,usn)!=0)
     {
       p=p->next;
     }
     if(p==NULL)
     {
        printf("for existing student ");
     	return 1;
	 }
     else
      {
        if(p->no_of_books==3) 
        return 0;
        else if(p->no_of_books==1  && (strcmp(p->book1,bk_name)==0))
            return 0; 
        else if(p->no_of_books==2 &&  ((strcmp(p->book1,bk_name)==0) || (strcmp(p->book2,bk_name)==0)))
            return 0;
        else
           return 1;  
      }
   }
}
void issue_book(STUDENT*s,LIBRARY *l,char st_name[20],char st_usn[15],char st_branch[5], char st_sem[5],char bk_name[50])
{
	Node_s*temp=(Node_s*)malloc(sizeof(Node_s));
	strcpy(temp->name,st_name);
    strcpy(temp->branch,st_branch);
    strcpy(temp->usn,st_usn);
    strcpy(temp->sem,st_sem);
    temp->next=NULL;
    if(s->root==NULL)
     {
       strcpy(temp->book1,bk_name);
       strcpy(temp->book2,"-");
       strcpy(temp->book3,"-");
       temp->no_of_books=1;
       s->root=temp;
     }
   else
   {
     Node_s*p=s->root;
     Node_s*q=NULL;
     while(p!=NULL && strcmp(p->usn,st_usn)!=0)
     {
       q=p;
       p=p->next;
     }
     if(p==NULL)
     {
        strcpy(temp->book1,bk_name);
        temp->no_of_books=1;
        q->next=temp;
     }
     else if(p!=NULL)
     { 
	    printf("existing studet\n");
        if(p->no_of_books==1)
        {
          strcpy(p->book2,bk_name);  
          p->no_of_books++;
        }
        else if(p->no_of_books=2)
        {
          strcpy(p->book3,bk_name);
          p->no_of_books++;
        }
     }
   }
   FILE *fp=fopen("STUDENT.csv","w");
   if(fp==NULL)
	{
       printf("file can't be opened\n");
       return;
    }
    fprintf(fp,"SEM,BRANCH,USN,NAME,COUNT,BOOK1,BOOK2,BOOK3\n");
    Node_s*k=s->root;
    if(k==NULL)
       return;
    else
	{   
      while(k!=NULL)
      {     
	  	if(k->no_of_books==1)
         {
           fprintf(fp,"%s,%s,%s,%s,%d,%s,-,-,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1);             
         }
        else if(k->no_of_books==2)
         {
           fprintf(fp,"%s,%s,%s,%s,%d,%s,%s,-,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1,k->book2);             
         }
        else if(k->no_of_books==3)
		 {
           fprintf(fp,"%s,%s,%s,%s,%d,%s,%s,%s,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1,k->book2,k->book3);
		 }
        k=k->next;
      }  
   }
   fclose(fp);
   delete_book(l,bk_name);
}
void append_csv_s(STUDENT *s)
{
   char str[500],st_name[20],st_usn[15],st_sem[3],st_branch[5],book1[50],book2[50],book3[50],bk_count[3];
   FILE *fp;
   fp=fopen("STUDENT.csv","r");
   if(fp==NULL)
   {
   	  printf("File can't be opened\n");
   	  return;
   }
   fgets(str,500,fp);
   while(fgets(str,500,fp)!=NULL)
   {
   	  strcpy(st_sem,strtok(str,","));
      strcpy(st_branch,strtok(NULL,","));
      strcpy(st_usn,strtok(NULL,",")); 
      strcpy(st_name,strtok(NULL,","));
      strcpy(bk_count,strtok(NULL,","));
      int count;
      sscanf(bk_count,"%d",&count);
      strcpy(book1,strtok(NULL,","));
      strcpy(book2,strtok(NULL,","));
      strcpy(book3,strtok(NULL,","));
      Node_s *temp=(Node_s*)malloc(sizeof(Node_s)); 
      strcpy(temp->sem,st_sem);
      strcpy(temp->branch,st_branch);
      strcpy(temp->usn,st_usn);
      strcpy(temp->name,st_name);
      temp->no_of_books=count;
      strcpy(temp->book1,book1);
      strcpy(temp->book2,book2);
      strcpy(temp->book3,book3);
      temp->next=NULL;
      if(s->root==NULL)
	   {
       	   s->root=temp;
	   }
	  else
	   {
		 Node_s*p=s->root;
		 while(p->next!=NULL)
		 {
			p=p->next;
		 }
		 p->next=temp;
	   }
	}
    fclose(fp);
}

void append_csv_l(LIBRARY *l)
{   
   char str[1000],bk_name[50],bk_athr[50],bk_count[3],bk_branch[5];
   FILE *fp;
   fp=fopen("LIBRARY1.csv","r");
   if(fp==NULL)
   {
   	  printf("File can't be opened\n");
   	  return;
   }
   fgets(str,1000,fp);
   while(fgets(str,1000,fp)!=NULL)
   {	
      strcpy(bk_branch,strtok(str,","));
   	  strcpy(bk_name,strtok(NULL,","));
	  strcpy(bk_athr,strtok(NULL,","));
	  strcpy(bk_count,strtok(NULL,","));
	  int count;
      sscanf(bk_count,"%d",&count);
	  Node_l *temp=(Node_l*)malloc(sizeof(Node_l)); 
	  strcpy(temp->branch,bk_branch);    
	  strcpy(temp->book_name,bk_name);
	  strcpy(temp->authour,bk_athr);
	  temp->book_remaining=count;
	  temp->next=NULL;
	  if(l->root==NULL)
	  {
       	   l->root=temp;
	  }
	  else
	  {
		Node_l*p=l->root;
		while(p->next!=NULL)
		{
	    	p=p->next;
		}
		p->next=temp;
	  }
   }
   fclose(fp);
}
void delete_book(LIBRARY *l,char *bk_name)
{
   Node_l *p=l->root;
   Node_l *q=NULL;
   while(p!=NULL && strcmp(p->book_name,bk_name)!=0)
   { 
   	   q=p;
       p=p->next;
   }
   if(p==NULL)
   {    
   		printf("book not found\n");
   }
   else if(p!=NULL && strcmp(p->book_name,bk_name)==0)
   { 
   		printf("book found\n");
        p->book_remaining=p->book_remaining - 1;
   }
   FILE *fp=fopen("LIBRARY1.csv","w");
   if(fp==NULL)
   {
     printf("File can't be opened\n");
     return;
   }
    fprintf(fp,"BRANCH,BOOK NAME,AUTHOR,COUNT\n");
    Node_l*k=l->root;
    while(k->next!=NULL)
    {  
        fprintf(fp,"%s,%s,%s,%d\n",k->branch,k->book_name,k->authour,k->book_remaining);
        k=k->next;
    }
    fprintf(fp,"%s,%s,%s,%d",k->branch,k->book_name,k->authour,k->book_remaining);
    fclose(fp);
}
void disp_l(LIBRARY*l)
{
     int i=1;
     Node_l*p=l->root;
     while(p!=NULL)
     {	
		printf("%d--->%s\t%s\t\t%s\t%d\n",i,p->branch,p->book_name,p->authour,p->book_remaining);
		p=p->next;
		i++;
     }
}
void disp_s(STUDENT* s)
{
	printf("hi\n");
 	int i=1;
  	Node_s*k=s->root;
    if(k==NULL)
       return;
    else
	{   
      while(k!=NULL)
      { 
        printf("%d--->%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s\n",i,k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1,k->book2,k->book3);
        k=k->next;
        i++;
      }  
	}
}
