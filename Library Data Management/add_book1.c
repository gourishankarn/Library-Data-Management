#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node_l
{
	char book_name[50];
	char authour[50];
	char branch[5];
	int book_remaining;
	struct node_l *next;
}Node_l;

typedef struct library
{
	Node_l*root;
}LIBRARY;

void add_book(LIBRARY *l,char *bk_name,char *bk_athr,char *branch);
void disp(LIBRARY *l);
void append_csv(LIBRARY *l);

void main()
{   
   LIBRARY l;
   l.root=NULL;
   append_csv(&l);
   char bk_name[50],bk_name1[50],bk_name2[50],bk_athr[50],bk_branch[5],bk_count[3];
   char str[500],str1[500];
   printf("enter book name, author name and branch:");
   gets(bk_name);
   gets(bk_athr);
   gets(bk_branch); 
   add_book(&l,bk_name,bk_athr,bk_branch);
   disp(&l);
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
   {
      Node_l*k=l->root;
      
      while(k!=NULL)
      {  
        fprintf(fp,"%s,%s,%s,%d\n",k->branch,k->book_name,k->authour,k->book_remaining);
        k=k->next;
      }
   }
}
void append_csv(LIBRARY *l){   

   char str[500],bk_name[50],bk_athr[50],bk_count[3],bk_branch[5];
   FILE *fp;
   fp=fopen("LIBRARY1.csv","r");
   if(fp==NULL){
   printf("File can't be opened\n");
   return;
   }
   fgets(str,500,fp);
   while(fgets(str,500,fp)!=NULL)
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
void disp(LIBRARY *l)
{    int i=1;
     Node_l*p=l->root;
     while(p!=NULL)
     {	
	printf("%d--->%s    %s    %s    %d\n",i,p->branch,p->book_name,p->authour,p->book_remaining);
	p=p->next;
	i++;
     }
}
