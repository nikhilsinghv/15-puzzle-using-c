#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{
	int matrix[4][4];
	struct node *parent;
	int cost;
	int level;
	int x,y;
	struct node *next;
}NODE;
typedef struct queue{
	NODE data;
	struct queue *next;
}Queue;
void swap(int a,int b)
{
	int temp=a;
	a=b;
	b=temp;
}
void printmat(int c[][4])
{
	int i,j;
	for (i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%d ",c[i][j]);
		}
		printf("\n");
	}printf("\n");
}
NODE *createnode(int mat[4][4],int x,int y,int a,int b,NODE *parent,int level)
{
	NODE *node = (NODE*)malloc(sizeof(NODE));
	node->parent=parent;
	

	memcpy(node->matrix, mat, sizeof node->matrix);
	int temp=node->matrix[x][y];
	node->matrix[x][y]=node->matrix[a][b];
	node->matrix[a][b]=temp;
	//swap(node->matrix[x][y],node->matrix[a][b]);
	node->x=a;
	node->y=b;
	node->cost=INT_MAX;
	node->level=level;
	return node;
	
} 
int misplacedtiles(int mat[][4],int goal[][4])
{
	int cost=0;
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++)
		{
			if(mat[i][j]!=goal[i][j] && mat[i][j])
				cost+=1;
		}
	}
	//printf("cost:%d\n",cost);
	return cost;
}
Queue *insertdata(Queue *head,NODE *data)
{
	Queue *temp=head;
	
	if (head==NULL){
		(temp->data).cost=data->cost;
		(temp->data).x=data->x;
		(temp->data).y=data->y;
		(temp->data).level=data->level;
		memcpy((temp->data).matrix,data->matrix,sizeof (temp->data).matrix );
		(temp->data).parent=data->parent;

		return head;
	}
	else{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}	
		(temp->data).cost=data->cost;
		(temp->data).x=data->x;
		(temp->data).y=data->y;
		(temp->data).level=data->level;
		memcpy((temp->data).matrix,data->matrix,sizeof (temp->data).matrix );
		(temp->data).parent=data->parent;

	}	

	return head;
}

int empty(Queue *head)
{
	if(head->next!=NULL)
	{
		return 1;
	}
	return 0;
}
NODE *extractmin(Queue *head)
{
	//printf("asq");
	Queue *temp=head;
	Queue *temp1=head;
	NODE *newnode;
	int min=INT_MAX;
		
	while(temp!=NULL)
	{
		if(check_visited_closed(temp)==0){
			
		if(min > temp->data.cost+temp->data.level){
			min=temp->data.cost+temp->data.level;
			newnode=(NODE*)malloc(sizeof(NODE));
			newnode->x=temp->data.x;
			newnode->y=temp->data.y;
			newnode->cost=temp->data.cost;
			newnode->level=temp->data.level;
			newnode->parent=temp->data.parent;
			memcpy(newnode->matrix,temp->data.matrix,sizeof newnode->matrix);
			
		}
	}

		temp=temp->next;
	}
		return newnode;
}
int isSafe(int x, int y)
{
    return (x >= 0 && x < 4&& y >= 0 && y < 4);
}
int check(NODE temp,int mat[][4])
{
	int i,j;
	for( i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(temp.matrix[i][j]!=mat[i][j])
				return 0;
		}
	}
	return 1;
}
 void pop(Queue *head,int data[][4])

 {
 	//printf("as \n");
 	Queue *temp=head;
 	//printf("as1 \n");
 	Queue *temp2=head;
 	//printf("ads");
 	while(temp!=NULL)
 	{
 		
 		if(check(temp->data,data))
 		{
 			temp=temp2;
 			if(temp->next!=NULL)
 				temp->next=(temp->next)->next;
 			
 		}
 		
 		else{
 			temp2=temp;
 		}	
 			temp=temp->next;
 		
 		
 	}
 
 }
 int findlength(NODE *temp)
 {
 	NODE *head=temp;
 	int c=0;
 	while(head!=NULL)
 	{
 		c++;
 		head=head->next;
 	}
 	return c;
 }
 int findlength1(Queue *temp)
 {
 	Queue *head=temp;
 	int c=0;
 	while(head!=NULL)
 	{
 		c++;
 		head=head->next;
 	}
 	return c;
 }
 NODE *closed;
 void mark_visited(NODE* root,NODE* parent){
	
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	int i,j;
	
		temp->parent = parent;
		for( i=0;i<4;i++){
			for( j=0;j<4;j++){	
				temp->matrix[i][j]=root->matrix[i][j];
			}
		}
		temp->cost = root->cost;	
		temp->x = root->x;
		temp->y = root->y; 
		temp->level=root->level;
		temp->next = closed;
		closed = temp;
		
	
}
 
 
 
int check_visited_closed(NODE* root){ 
 

 	NODE* temp=closed;
 //	printf(" 5\n");
 	while(temp!=NULL){
 	//	printf("6\n");
 		int count=0,i,j;
 		for(i=0;i<4;i++){
			for(j=0;j<4;j++){
				if (temp->matrix[i][j]!=root->matrix[i][j]){
					count++;
					break;
				}
			}
			if(count)
			{
				count=0;
				break;
			}
		}
		if(i==4 && j==4){			
			return 1;
		}
		temp=temp->next;
 	}
 	//printf("7\n");
 	return 0;
 		
}
void printpath(NODE* root){
	if(root->parent!=NULL){
		printpath(root->parent);
	}
	printmat(root->matrix);
	
}

void solvepuzzle(int mat[][4],int x,int y,int goal[][4])
{
	NODE *node=createnode(mat,x,y,x,y,NULL,0);
	Queue *head=(Queue*)malloc(sizeof(Queue));
	int cost=misplacedtiles(mat,goal);
	node->cost=cost;

	int row[] = { 1, 0, -1, 0 };
	int col[] = { 0, -1, 0, 1 };
	//printf("%d",node->y);
	head=insertdata(head,node);
	int c=0;
	
	//printf("%d",(head->data).cost);
	Queue *temp=head;
	Queue *temp1=head;

	NODE *min;
	while(temp!=NULL)
	{
		temp1=head;
	//	printf("0\n");
		//printf("before extraction\n");
		min =extractmin(temp1);
	
	
		int flag=0;
		if(temp){
			pop(temp,min->matrix);
	}
		if(min->cost==0)
			{
				printpath(min);	
				printf("successed");
				break;
			}
		else{
			if(check_visited_closed(min)==0){

			int i;
	//		printf("3\n");
			for ( i = 0; i < 4; i++)
        	{
         	   if (isSafe(min->x + row[i], min->y + col[i]))
            	{
            		c++;
      //      		printf("8\n");
        			
               		 NODE* child = createnode(min->matrix, min->x,
                              min->y, min->x + row[i],
                              min->y + col[i], min,
                              min->level + 1);
                		child->cost = misplacedtiles(child->matrix, goal);
                	//printmat(child->matrix);
                	//printf("COST:%d\n", child->cost);
                	if(child->cost == 0)
                	{
                		printf("path:\n");
                		printpath(child);
                		
                		
                		printf("level:%d \nnumber nodes generated :%d\nnodes in the closed list:%d\nnodes in openlist:%d \n",child->level,c,findlength(closed),findlength1(temp));

                		flag = 1;
                		break;
                	}
 					temp=insertdata(temp,child);
                // Add child to list of live nodes
               }
        	}
			}
		}
		if(flag==1)
		{
		//printf("SUCCEEDED\n");
		break;	
		}
		
		mark_visited(min,min->parent);
	}
	
}

int getInvCount(int arr[])
{
	int i,j;
	int N=4;
    int inv_count = 0;
    for (i = 0; i < N * N - 1; i++)
    {
        for (j = i + 1; j < N * N; j++)
        {
            // count pairs(i, j) such that i appears
            // before j, but i > j.
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
        }
    }
    return inv_count;
}

int findXPosition(int puzzle[4][4])
{
	int i,N,j;
	N=4;
    for (i = N - 1; i >= 0; i--)
        for ( j = N - 1; j >= 0; j--)
            if (puzzle[i][j] == 0)
                return N - i;
}

_Bool isSolvable(int puzzle[4][4])
{
	int N=4;
    int invCount = getInvCount((int*)puzzle);
    if (N & 1)
        return !(invCount & 1);

    else 
    {
        int pos = findXPosition(puzzle);
        if (pos & 1)
            return !(invCount & 1);
        else
            return invCount & 1;
    }
}

int main()
{

	int matrix[4][4];
	int i,j,a,b;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			scanf("%d",&matrix[i][j]);
		}
		
	}
	scanf("%d %d",&a,&b);
/*	int matrix[4][4] =
    {
        {1, 2, 3,4},
        {5, 6, 7,8},
        {0, 9,10, 11},
        {13,14,15,12}
    };
 */
    int final[4][4] =
    {
        {1, 2, 3,4},
        {5, 6, 7,8},
        {9, 10, 11,12},
        {13,14,15,0}
    };
 
    int x = 2, y =0;
 	solvepuzzle(matrix,a,b,final);
 	if(isSolvable(matrix))
 		printf("\nsolvable\n");
 	else
 		printf("unsolvable");
	
	return 0;
}