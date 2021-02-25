#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct cactu{
	char* tu;
	int count;
	int dong[100];
	struct cactu* next;
};

struct tukiemtra
{
	char* tudb;
	struct tukiemtra* next;	
};

void insertstop(char* a,struct tukiemtra** head)
{
	if(*head==NULL)
	{
		*head = (struct tukiemtra*)calloc(1, sizeof(struct tukiemtra*));
		(*head) -> tudb = (char*)calloc(strlen(a), sizeof(char));
		strcpy((*head) -> tudb, a);
	}
	else
	    insertstop(a,&((*head)->next));
}


int checkword(char* tu,struct tukiemtra* head)
{
	while(head != NULL)
	{
		// printf("%s\n", head -> tudb);
		if(strcmp(head->tudb,tu)==0)
			return 0;
	    
	    head = head ->next;
	}
	return 1;
}


void swapsleaf(struct cactu* a,struct cactu* b)
{
	struct cactu* simp;
	simp=a;
	a->count=b->count;
	a->tu=b->tu;
	for(int i=0;i<10;i++)
	{
		a->dong[i]=b->dong[i];
	}
	b->count=simp->count;
	b->tu=simp->tu;
	for(int i=0;i<10;i++)
	{
		b->dong[i]=simp->dong[i];
	}
}

struct cactu* bubblesort(struct cactu* root)
{
	if(root==NULL)
		return NULL;
	struct cactu* p;
	p=root;
	int x=1;
	while(p->next!=NULL)
	{
		x++;
		p=p->next;
	}
	p=root;
	int checkswap=0;
	for(int i=0;i<x;i++)
	{
		checkswap=0;
		for(int j=0;j<x-1;j++)
		{
			if(strcmp(p->tu,p->next->tu)>0)
			{	
				checkswap=1;
				swapsleaf(p,p->next);
			}
		
		}
		if(checkswap==0)
			break;
	}
	return p;
}

void travel(struct cactu* root)
{
	while(root != NULL)
	{
		printf("\n%s\t ", root->tu);
		printf("%d\t", root->count);
		for(int i=0;i< root -> count;i++)
		{

				printf("%d\t",root->dong[i]);
		}
	    root=root->next;
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	struct tukiemtra* head = NULL;
	struct cactu* root = NULL;

	// insertstop("a", head);
	int sodong=1;
	FILE* f=fopen("vanban.txt","r");
	FILE* sf=fopen("stopw.txt","r");
    char* tu=(char*)calloc(30,sizeof(char));
    while(!feof(sf))
    {
    	fgets(tu,30,sf);
    	tu[strlen(tu) - 1]='\0';
    	insertstop(tu, &head);
    }
    fclose(sf);
    char c;
    c=fgetc(f);
    int v=0;
    while(c!=EOF)
    {
    	if(c=='\n')
    		sodong++;
    	if(c>=32&&c<=47||c>=58&&c<=64||c>=91&&c<=96||c>=123&&c<=126||c=='\0'||c=='\n')
    	{
    		tu[v]='\0';
    		v=0;
            if(checkword(tu,head)==1 && strlen(tu) > 0)
            {
    			struct cactu* tmp = root;
    			while(tmp != NULL)
    			{
    				if(strcmp(tmp -> tu, tu) == 0)
    				{
    					++(tmp -> count);
    					tmp -> dong[tmp -> count - 1] = sodong;
    					break;
    				}
    				tmp = tmp -> next;
    			}

    			if(tmp == NULL)
    			{
    				struct cactu* tuMoi = (struct cactu*)calloc(1, sizeof(struct cactu));
    				tuMoi -> tu = (char*)calloc(strlen(tu), sizeof(char));
    				strcpy(tuMoi -> tu, tu);
    				tuMoi -> count = 1;
    				tuMoi -> dong[0] = sodong;
    				tuMoi -> next = root;
    				root = tuMoi;
    			}
            }
    		tu[0]='\0';
    	}
    	else
    		tu[v++]=tolower(c);
    	c=fgetc(f);
    }
    // root=bubblesort(root);
    // travel(root);
    fclose(f);
    // free(tu);
    // insertword("least", 1, &root);
    // insertword("least", 2, &root);
    // insertword("least", 5, &root);
    // insertword("apple", 6, &root);

    // root = (struct cactu*)calloc(1, sizeof(struct cactu));
    // root -> tu = (char*)calloc(strlen("least"), sizeof(char));
    // strcpy(root -> tu, "least");
    // root -> count = 1;
    // root -> dong[0] = 1;

    // ++(root -> count);
    // root -> dong[1] = 2;

    // root -> next = (struct cactu*)calloc(1, sizeof(struct cactu));
    // struct cactu* tmp = root -> next;

    // tmp -> tu = (char*)calloc(strlen("people"), sizeof(char));
    // strcpy(tmp -> tu, "people");
    // tmp -> count = 1;
    // tmp -> dong[0] = 2;

    // printf("%p\n", root -> next);
    // insertword("people", 5, &root);
    // insertword("people", 1, &root);
    travel(root);

	return 0;
}