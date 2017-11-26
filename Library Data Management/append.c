#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node_l
{
	char book_name[50];
	char authour[50];
	char branch[5];
	char book_remaining[3];
	struct node_l *next;
}Node_l;


typedef struct library
{
	Node_l*root;
}LIBRARY;

//void create_node_l(LIBRARY *l,char *bk_name,char *bk_athr);
void disp(LIBRARY *l);
void append(LIBRARY *l);

void main()
{   
   LIBRARY l;
   l.root=NULL;
   append_csv(&l);
   disp(&l);
   }
void append_csv(LIBRARY *l){   

   char str[500],bk_name[50],bk_athr[50],bk_count[3];
   FILE *fp;
   fp=fopen("LIBRARY.csv","r");
   if(fp==NULL){
   printf("File can't be opened\n");
   return;
   }
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

  
}

void disp(LIBRARY *l)
{    int i=1;
     Node_l*p=l->root;
     while(p!=NULL)
     {	
	printf("%d--->%s\t\t%s\t%s\n",i,p->book_name,p->authour,p->book_remaining);
	p=p->next;
	i++;
     }
}
