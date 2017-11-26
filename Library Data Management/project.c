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


STUDENT* init_s(STUDENT*s);
LIBRARY* init_l(LIBRARY*l);
void append_csv_l(LIBRARY*l);
void append_csv_s(STUDENT*s);
void disp_l(LIBRARY *l);
void disp_s(STUEDNT *s);
void add_book(LIBRARY *l,char *bk_name,char *bk_athr,char *bk_branch);
void add_book1(LIBRARY *l,char *bk_name);
int delete_book(LIBRARY*l,char *book_name);
int search_book(LIBRARY*l,char *bk_name);
int book_check(STUDENT *s,char *usn,char *bk_name);
void issue_book(STUDENT*s,LIBRARY *l,char *st_name,char *st_usn,char *st_branch, char *st_sem); 
int return_book(LIBRARY *l,STUDENT *s,char st_usn[15],char bk_name[50]);
void display_s(STUDENT* s);
void display(LIBRARY *l);


void main()
{ 
  STUDENT s;
  LIBRARY l;
  init_s(&s);
  init_l(&l);
  
  int ch,k,i,j,count=0;
  char bk_name[50],bk_athr[50],bk_branch[5],st_name[20],st_usn[15],st_sem[5],st_branch[5],str[500],bk_count[5];
  
  do{append_csv_l(&l);
     append_csv_s(&s);
     display_l(&l);
     display_s(&s);
    printf("1. add books 2. delete book 3.issue 4. return 5.search 6.display(student) 7.display(library) 8 .exit\n");
    scanf("%d",&ch);
    switch(ch)
    {
      case 1:
              printf("enter book name, author name and branch:");
              gets(bk_name);
              gets(bk_athr);
              gets(bk_branch); 
              add_book(&l,bk_name,bk_athr,bk_branch);   // this  function should add only one book at a time.
             
             break;
			    
      case 2:printf("enter book name:");
             gets(bk_name);
            
             k=delete_book(&l,bk_name);   // this  function should delete only one book at a time.
             if(k==1)
                printf("succefully deleted\n");
             else if(k==0)
                printf("Unsucceful\n");
            break;
			    
            
     /* case 3:printf("enter name of the book or authour name:");
             gets(bk_name);
             gets(bk_athr);
             k=search_book_l(&l,bk_name);   // this  function searches the book and return 1 if book found
             if(k==1){
			 
              		//student details to issue a book;
              		printf("Student name:");
              		gets(st_name);
              		printf("Student USN:");
              		gets(st_usn);
              		
              		printf("Student branch:");
              		gets(st_branch);
              		printf("Student sem:");
              		gets(st_sem);
                        
              		//Check for the constraints like same book issued and no_of_books issued.....
              		if(!book_check(&s,s_usn,bk_name))                // if this function returns true.........
              		    printf("Book can't be issued\n");
              		else
		           issue_book(&s,&l,st_name,st_usn,st_branch,st_sem);  
					//insetrt into file  
				}
             else if(k==0){
                printf("Book not found\n"); 
            }
            break;*/
            
      case 4:printf("enter your USN");
     		gets(st_usn);
     		printf("enter book name ");
     		gets(bk_name);
     		k=return_book(&l,&s,st_usn,bk_name);
               if(k!=1)
                       printf("book is not returned successfully\n");
		break;
			
      case 5:printf("enter name of the book:");
             gets(bk_name);
             
             k=search_book(&l,bk_name); 
             if(k==1)
             {
             	printf("Book found");
             		
		}
	      
	     else{
		  printf("Book not found");
		 }
		 break;
			 
	  case 6:display_s(&s);
		 break;
          case 7:display_l(&l);
                  break;				
    }
  }while(ch<8);
}


STUDENT* init_s(STUDENT*s)
{
	s->root=NULL;
	return s;
}
LIBRARY *init_l(LIBRARY *l)
{
	l->root=NULL;
	return l;
}

void append_csv_l(LIBRARY*l)
{
  char str[500],bk_name[50],bk_athr[50],bk_count[3];
   FILE *fp;
   fp=fopen("LIBRARY.csv","r");
   if(fp==NULL){
   printf("File can't be opened\n");
   
   }
   else{
   fgets(str,500,fp);
   while(fgets(str,500,fp)!=NULL)
   {	
        strtok(str,",");
        strcpy(bk_name,strtok(NULL,","));
	strcpy(bk_athr,strtok(NULL,","));
	strcpy(bk_count,strtok(NULL,","));
	Node_l *temp=(Node_l*)malloc(sizeof(Node_l));       
	strcpy(temp->book_name,bk_name);
	strcpy(temp->authour,bk_athr);
	strcpy(temp->book_remaining,bk_count);
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
   return l;
   }
   fclose(fp);
}
void add_book(LIBRARY *l,char *bk_name,char *bk_athr,char *bk_branch)
{
   
   
   Node_l *p=l->root;
   Node_l *q=NULL;
   while(p!=NULL && strcmp(p->book_name,bk_name)!=0)
   { q=p;
     p=p->next;
   }
   if(p==NULL)
   {    printf("book not found\n");
        Node_l *temp=(Node_l*)malloc(sizeof(Node_l));       
	strcpy(temp->book_name,bk_name);
	strcpy(temp->authour,bk_athr);
	strcpy(temp->branch,bk_branch);
	temp->book_remaining=10;
	temp->next=NULL;
	q->next=temp;
	
   }
   else if(p!=NULL && strcmp(p->book_name,bk_name)==0)
   { printf("book found\n");
     p->book_remaining=p->book_remaining + 1;
   }
   FILE *fp=fopen("LIBRARY1.csv","w");
   
   if(fp==NULL)
   {
     printf("File can't be opened\n");
     return;
     
   }
   else
   {  fprintf(fp,"BRANCH,BOOK NAME,AUTHOR,COUNT");
      Node_l*k=l->root;
      
      while(k!=NULL)
      {  
        fprintf(fp,"%s,%s,%s,%d\n",k->branch,k->book_name,k->authour,k->book_remaining);
        k=k->next;
      }
   }
   fclose(fp);
}
int delete_book(LIBRARY*l,char *book_name);
{
    Node_l *p=l->root;
   Node_l *q=NULL;
   while(p!=NULL && strcmp(p->book_name,bk_name)!=0)
   { q=p;
     p=p->next;
   }
   if(p==NULL)
   {    printf("book not found\n");
        
   }
   else if(p!=NULL && strcmp(p->book_name,bk_name)==0)
   { printf("book found\n");
     p->book_remaining=p->book_remaining - 1;
   }
   FILE *fp=fopen("LIBRARY1.csv","w");
   if(fp==NULL)
   {
     printf("File can't be opened\n");
     return;
     
   }
   else
   {  fprintf(fp,"BRANCH,BOOK NAME,AUTHOR,COUNT");
      Node_l*k=l->root;
      
      while(k!=NULL)
      {  
        fprintf(fp,"%s,%s,%s,%d\n",k->branch,k->book_name,k->authour,k->book_remaining);
        k=k->next;
      }
   }
   fclose(fp);
}
int search_book(LIBRARY*l,char *bk_name)
{
    Node_l*p=l->root;
    while(p!=NULL && strcmp(p->book_name,bk_name)!=0)
    {
      p=p->next;
    }
    if(p==NULL)
      return 0;
    else
      return 1;  
}


int book_check(STUDENT *s,char *usn,char *bk_name)
{
   if(s->root==NULL)
     return 1;
   else 
   {
     Node_s *p=s->root;
     while(p!=NULL  && strcmp(p->usn,usn)!=0)
     {
       p=p->next;
     }
     if(p==NULL)
        return 1;
     else
      {
        if(p->no_of_books==3 || (strcmp(p->book1,bk_name)==0) || (strcmp(p->book2,bk_name)==0) || (strcmp(p->book3,bk_name)==0))
             return 0;
        else
          return 1;     
      }   
   }  
}


void issue_book(STUDENT*s,LIBRARY *l,char *st_name,char *st_usn,char *st_branch, char *st_sem,char *bk_name)
{  
   
}


int return_book(LIBRARY *l,STUDENT *s,char st_usn[15],char bk_name[50])
{
   Node_s *p=s->root;
   if(s->root==NULL)
     return 0;
   while(p!=NULL && (strcmp(p->usn,st_usn)!=0))
   {
     p=p->next;
   }
   if(p==NULL)
      {
        printf("student having this usn has not issued any books\n");
        return 0;
      }
   else
     {  if(p->no_of_books==0) {printf("U don't have books only\n");return 0;}
       else if(p->no_of_books==1)
       {
          if(strcmp(p->book1,bk_name)!=0)
          {
            printf("this book is not issued by this student\n");
            return 0;
          }
          else
          {
            p->no_of_books--;
            strcpy(p->book1,"-");
          }
                
       }
       
       else if(p->no_of_books==2)
       {
          if((strcmp(p->book1,bk_name)!=0) && (strcmp(p->book2,bk_name)!=0))
          {
            printf("this book is not issued by this student\n");
            return 0;
          }
          else
          {
           
            if(strcmp(p->book2,bk_name)==0)
             {
               strcpy(p->book2,"-");
              
             }
             else if(strcmp(p->book1,bk_name)==0)
             {
               strcpy(p->book1,p->book2);
               strcpy(p->book2,"-");
             }
              p->no_of_books--;
              
          }      
       }
       
      else if(p->no_of_books==3)
       {
          if((strcmp(p->book1,bk_name)!=0) && (strcmp(p->book2,bk_name)!=0) && (strcmp(p->book3,bk_name)!=0))
          {
            printf("this book is not issued by this student\n");
            return 0;
          }
          else
          {
            if(strcmp(p->book3,bk_name)==0)
             {
              strcpy(p->book3,"-");
              
             }
             else if(strcmp(p->book2,bk_name)==0)
             {
               strcpy(p->book2,p->book3);
               strcpy(p->book3,"-");
             }
             else if(strcmp(p->book1,bk_name)==0)
             { strcpy(p->book1,p->book2);
               strcpy(p->book2,p->book3);
               strcpy(p->book3,"-");
             }
              p->no_of_books--;
             
          }      
       }
       
     }
     
   FILE *fp=fopen("STUDENT.csv","w");
   if(fp!=NULL)
     {
       
    fprintf(fp,"SEM,BRANCH,USN,NAME,COUNT,BOOK1,BOOK2,BOOK3\n");
   Node_s*k=s->root;
    if(k!=NULL)   
      while(k!=NULL)
      {      if(k->no_of_books==0)
             {
                 fprintf(fp,"%s,%s,%s,%s,%d,-,-,-,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books);             
             }
             else if(k->no_of_books==1)
             {
                 fprintf(fp,"%s,%s,%s,%s,%d,%s,-,-,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1);             
             }
             else if(k->no_of_books==2)
             {
                 fprintf(fp,"%s,%s,%s,%s,%d,%s,%s,-,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1,k->book2);             
             }
             else if(k->no_of_books==3){
                 fprintf(fp,"%s,%s,%s,%s,%d,%s,%s,%s,-\n",k->sem,k->branch,k->usn,k->name,k->no_of_books,k->book1,k->book2,k->book3);}
            k=k->next;
          }  
      }  
   
   fclose(fp);
   add_book1(l,bk_name);
   return 1;        
}
void display_s(STUDENT* s)
{
  int i;
  Node_s*k=s->root;
    if(k==NULL)
       return;
    else{   
      while(k!=NULL)
      {  if(k->no_of_books==1)
          {
           printf("%d--->%s\t%s\t%s\t%s\t%s\t%d\n",i,k->sem,k->branch,k->usn,k->name,k->book1,k->no_of_books);
          } 
          else if(k->no_of_books==2)
          {
            printf("%d--->%s\t%s\t%s\t%s\t%s\t%s\t%d\n",i,k->sem,k->branch,k->usn,k->name,k->book1,k->book2,k->no_of_books);
          }
          else if(k->no_of_books==3)
          {
            printf("%d--->%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\n",i,k->sem,k->branch,k->usn,k->name,k->book1,k->book2,k->book3,k->no_of_books);
          }
        
        k=k->next;
        i++;
      }  
}
}
void display_l(LIBRARY*l)
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

void add_book1(LIBRARY *l,char bk_name[50])
{
  Node_l *p=l->root;
   Node_l *q=NULL;
   while(p!=NULL && strcmp(p->book_name,bk_name)!=0)
   { q=p;
     p=p->next;
   }
  
   if(p!=NULL && strcmp(p->book_name,bk_name)==0)
   { printf("book found\n");
     p->book_remaining=p->book_remaining + 1;
   }
   FILE *fp=fopen("LIBRARY1.csv","w");
   if(fp==NULL)
   {
     printf("File can't be opened\n");
     return;
    }   
   fprintf(fp,"BRANCH,BOOK NAME,AUTHOR,COUNT");
      Node_l*k=l->root;
      
      while(k!=NULL)
      {  
        fprintf(fp,"%s,%s,%s,%d\n",k->branch,k->book_name,k->authour,k->book_remaining);
        k=k->next;
      }
   
   fclose(fp);
}




void append_csv_s(STUDENT *s)
{
  
   char str[500],st_name[20],st_usn[15],st_sem[3],st_branch[5],book1[50],book2[50],book3[50],bk_count[3];
   FILE *fp;
   fp=fopen("STUDENT.csv","r");
   if(fp==NULL)
   {
   printf("File can't be opened\n");
   
   }
   else{
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

   }
   fclose(fp);
}

