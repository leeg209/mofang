#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef enum colors{
	blue=1,red,yellow,green,white,orange
}Colors;

typedef struct surface{
	Colors s[4][4];
}Surface;

typedef struct cube
{
	Surface up,down,front,back,left,right;
}Cube;

typedef struct snode{
	char *chbuf;
	int times;
	struct snode *next;
}SNode;

typedef struct sequence{
	SNode *head;
	int num;
}Sequence;

Sequence CD;

void SaveChBuf(char *sur,int i){
	char *str;
	int len=strlen(sur);
	SNode *p,*q;
	if(i%4)
	{
		str=(char *)malloc(sizeof(char)*(len+2));
		if(!str)
		{
			printf("\n");
			exit(0);
		}
		strcpy(str,sur);
		q=(SNode *)malloc(sizeof(SNode));
		if(!q)
		{
			printf("\n");
			exit(0);
		}
		q->chbuf=str;
		q->times=i;
		q->next=NULL;
		if(CD.head==NULL)
		{
			CD.head=q;
			CD.num++;
		}
		else
		{
			for(p=CD.head;p->next;p=p->next);
			if(!strcmp(p->chbuf,q->chbuf))
			{
				p->times=(p->times+q->times)%4;
				free(q->chbuf);free(q);
				if(!(p->times))
				{
					if(p==CD.head)
					{
						CD.head=NULL;
						free(p->chbuf);free(p);
						CD.num--;
					}
					else
					{
						for(q=CD.head;q->next!=p;q=q->next);
						q->next=NULL;
						free(p->chbuf);free(p);
						CD.num--;
					}
				}
			}
			else
			{
				p->next=q;
				CD.num++;
			}
		}
	}
}

void clockwise(Surface *sur,int i){
	Surface t;
	for(;i>0;i--){
		t=*sur;
		sur->s[1][1]=t.s[3][1];
		sur->s[1][2]=t.s[2][1];
		sur->s[1][3]=t.s[1][1];
		sur->s[2][1]=t.s[3][2];
		sur->s[2][2]=t.s[2][2];
		sur->s[2][3]=t.s[1][2];
		sur->s[3][1]=t.s[3][3];
		sur->s[3][2]=t.s[2][3];
		sur->s[3][3]=t.s[1][3];
	}
}
void F(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		clockwise(&m->front,1);
		m->right.s[1][1]=n.up.s[3][1];
		m->right.s[2][1]=n.up.s[3][2];
		m->right.s[3][1]=n.up.s[3][3];
		m->down.s[1][1]=n.right.s[3][1];
		m->down.s[1][2]=n.right.s[2][1];
		m->down.s[1][3]=n.right.s[1][1];
		m->left.s[1][3]=n.down.s[1][1];
		m->left.s[2][3]=n.down.s[1][2];
		m->left.s[3][3]=n.down.s[1][3];
		m->up.s[3][1]=n.left.s[3][3];
		m->up.s[3][2]=n.left.s[2][3];
		m->up.s[3][3]=n.left.s[1][3];
	}
}
void B(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		clockwise(&m->back,1);
		m->right.s[1][3]=n.down.s[3][3];
		m->right.s[2][3]=n.down.s[3][2];
		m->right.s[3][3]=n.down.s[3][1];
		m->down.s[3][1]=n.left.s[1][1];
		m->down.s[3][2]=n.left.s[2][1];
		m->down.s[3][3]=n.left.s[3][1];
		m->left.s[1][1]=n.up.s[1][3];
		m->left.s[2][1]=n.up.s[1][2];
		m->left.s[3][1]=n.up.s[1][1];
		m->up.s[1][1]=n.right.s[1][3];
		m->up.s[1][2]=n.right.s[2][3];
		m->up.s[1][3]=n.right.s[3][3];
	}
}

void R(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		clockwise(&m->right,1);
		m->up.s[1][3]=n.front.s[1][3];
		m->up.s[2][3]=n.front.s[2][3];
		m->up.s[3][3]=n.front.s[3][3];
		m->front.s[1][3]=n.down.s[1][3];
		m->front.s[2][3]=n.down.s[2][3];
		m->front.s[3][3]=n.down.s[3][3];
		m->down.s[1][3]=n.back.s[3][1];
		m->down.s[2][3]=n.back.s[2][1];
		m->down.s[3][3]=n.back.s[1][1];
		m->back.s[3][1]=n.up.s[1][3];
		m->back.s[2][1]=n.up.s[2][3];
		m->back.s[1][1]=n.up.s[3][3];
	}
}

void L(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		clockwise(&m->left,1);
		m->up.s[1][1]=n.back.s[3][3];
		m->up.s[2][1]=n.back.s[2][3];
		m->up.s[3][1]=n.back.s[1][3];
		m->back.s[1][3]=n.down.s[3][1];
		m->back.s[2][3]=n.down.s[2][1];
		m->back.s[3][3]=n.down.s[1][1];
		m->down.s[1][1]=n.front.s[1][1];
		m->down.s[2][1]=n.front.s[2][1];
		m->down.s[3][1]=n.front.s[3][1];
		m->front.s[1][1]=n.up.s[1][1];
		m->front.s[2][1]=n.up.s[2][1];
		m->front.s[3][1]=n.up.s[3][1];
	}
}

void U(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		clockwise(&m->up,1);
		m->front.s[1][1]=n.right.s[1][1];
		m->front.s[1][2]=n.right.s[1][2];
		m->front.s[1][3]=n.right.s[1][3];
		m->right.s[1][1]=n.back.s[1][1];
		m->right.s[1][2]=n.back.s[1][2];
		m->right.s[1][3]=n.back.s[1][3];
		m->back.s[1][1]=n.left.s[1][1];
		m->back.s[1][2]=n.left.s[1][2];
		m->back.s[1][3]=n.left.s[1][3];
		m->left.s[1][1]=n.front.s[1][1];
		m->left.s[1][2]=n.front.s[1][2];
		m->left.s[1][3]=n.front.s[1][3];
	}
}

void D(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		clockwise(&m->down,1);
		m->front.s[3][1]=n.left.s[3][1];
		m->front.s[3][2]=n.left.s[3][2];
		m->front.s[3][3]=n.left.s[3][3];
		m->left.s[3][1]=n.back.s[3][1];
		m->left.s[3][2]=n.back.s[3][2];
		m->left.s[3][3]=n.back.s[3][3];
		m->back.s[3][1]=n.right.s[3][1];
		m->back.s[3][2]=n.right.s[3][2];
		m->back.s[3][3]=n.right.s[3][3];
		m->right.s[3][1]=n.front.s[3][1];
		m->right.s[3][2]=n.front.s[3][2];
		m->right.s[3][3]=n.front.s[3][3];
	}
}

void MR(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		m->up.s[1][2]=n.front.s[1][2];
		m->up.s[2][2]=n.front.s[2][2];
		m->up.s[3][2]=n.front.s[3][2];
		m->front.s[1][2]=n.down.s[1][2];
		m->front.s[2][2]=n.down.s[2][2];
		m->front.s[3][2]=n.down.s[3][2];
		m->down.s[1][2]=n.back.s[3][2];
		m->down.s[2][2]=n.back.s[2][2];
		m->down.s[3][2]=n.back.s[1][2];
		m->back.s[3][2]=n.up.s[1][2];
		m->back.s[2][2]=n.up.s[2][2];
		m->back.s[1][2]=n.up.s[3][2];
	}
}

void MF(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		m->right.s[1][2]=n.up.s[2][1];
		m->right.s[2][2]=n.up.s[2][2];
		m->right.s[3][2]=n.up.s[2][3];
		m->up.s[2][1]=n.left.s[3][2];
		m->up.s[2][2]=n.left.s[2][2];
		m->up.s[2][3]=n.left.s[1][2];
		m->left.s[1][2]=n.down.s[2][1];
		m->left.s[2][2]=n.down.s[2][2];
		m->left.s[3][2]=n.down.s[2][3];
		m->down.s[2][1]=n.right.s[3][2];
		m->down.s[2][2]=n.right.s[2][2];
		m->down.s[2][3]=n.right.s[1][2];
	}
}

void MU(Cube *m,int i){
	Cube n;
	for(;i>0;i--){
		n=*m;
		m->front.s[2][1]=n.right.s[2][1];
		m->front.s[2][2]=n.right.s[2][2];
		m->front.s[2][3]=n.right.s[2][3];
		m->right.s[2][1]=n.back.s[2][1];
		m->right.s[2][2]=n.back.s[2][2];
		m->right.s[2][3]=n.back.s[2][3];
		m->back.s[2][1]=n.left.s[2][1];
		m->back.s[2][2]=n.left.s[2][2];
		m->back.s[2][3]=n.left.s[2][3];
		m->left.s[2][1]=n.front.s[2][1];
		m->left.s[2][2]=n.front.s[2][2];
		m->left.s[2][3]=n.front.s[2][3];
	}
}

void MoveCube(Cube *m,char *sur,int i){
	SaveChBuf(sur,i);
	if(!strcmp(sur,"f"))
		F(m,i);
	if(!strcmp(sur,"b"))
		B(m,i);
	if(!strcmp(sur,"r"))
		R(m,i);
	if(!strcmp(sur,"l"))
		L(m,i);
	if(!strcmp(sur,"u"))
		U(m,i);
	if(!strcmp(sur,"d"))
		D(m,i);
			if(!strcmp(sur,"mr"))
		MR(m,i);	if(!strcmp(sur,"mf"))
		MF(m,i);	if(!strcmp(sur,"mu"))
		MU(m,i);
		}

void InputSurface(Surface *sur){
	int i,j,a;
	for(i=1;i<=3;i++){
		for(j=1;j<=3;j++){
			scanf("%d",&a);
			sur->s[i][j]=(Colors)a;
		}
	}	
}

void Input(Cube *magiccube){
	printf("Input the colors of the Magiccube:\n");
	printf("Blue--------1\tRed---------2\tYellow------3\n");
	printf("Green-------4\tWhite-------5\tOrange------6\n\n");
	printf("Input the colors of Up:\n");
	InputSurface(&(magiccube->up));
	printf("Input the colors of Down:\n");
	InputSurface(&(magiccube->down));
	printf("Input the colors of Front:\n");
	InputSurface(&(magiccube->front));
	printf("Input the colors of Back:\n");
	InputSurface(&(magiccube->back));
	printf("Input the colors of Left:\n");
	InputSurface(&(magiccube->left));
	printf("Input the colors of Right:\n");
	InputSurface(&(magiccube->right));
}

void DownCross(Cube *magiccube){
	while(!((magiccube->down.s[1][2]==magiccube->down.s[2][2]&&magiccube->front.s[3][2]==magiccube->front.s[2][2])
		&&(magiccube->down.s[2][1]==magiccube->down.s[2][2]&&magiccube->left.s[3][2]==magiccube->left.s[2][2])
		&&(magiccube->down.s[2][3]==magiccube->down.s[2][2]&&magiccube->right.s[3][2]==magiccube->right.s[2][2])
		&&(magiccube->down.s[3][2]==magiccube->down.s[2][2]&&magiccube->back.s[3][2]==magiccube->back.s[2][2])))
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int subscript_of_down[4][2]={{1,2},{2,1},{3,2},{2,3}};
		int subscript_of_up[4][2]={{3,2},{2,1},{1,2},{2,3}};
		char ch[3];
		int n;
		for(int i=0;i<4;i++){
			if(magiccube->down.s[subscript_of_down[i][0]][subscript_of_down[i][1]]==magiccube->down.s[2][2]
				&&sur[i]->s[3][2]!=sur[i]->s[2][2])
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,2);
			}
			if(magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]==magiccube->down.s[2][2])
			{
				n=0;
				while(sur[(i+n)%4]->s[2][2]!=sur[(i+n)%4]->s[1][2])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				strcpy(ch,s[(i+n)%4]);
				MoveCube(magiccube,ch,2);
			}
			if(sur[i]->s[1][2]==magiccube->down.s[2][2])
			{
				n=0;
				while(sur[(i+n+1)%4]->s[2][2]!=magiccube->up.s[subscript_of_up[(i+n)%4][0]][subscript_of_up[(i+n)%4][1]])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				strcpy(ch,s[(i+n)%4]);
				MoveCube(magiccube,ch,3);
				strcpy(ch,s[(n+1+i)%4]);
				MoveCube(magiccube,ch,1);
				strcpy(ch,s[(i+n)%4]);
				MoveCube(magiccube,ch,1);
			}
		
			if(sur[i]->s[2][1]==magiccube->down.s[2][2]){
				strcpy(ch,s[(i+1)%4]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,1);
			}
			
			if(sur[i]->s[2][3]==magiccube->down.s[2][2]){
				strcpy(ch,s[(i+3)%4]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
			}
			
			if(sur[i]->s[3][2]==magiccube->down.s[2][2]){
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,1);
				strcpy(ch,s[(i+1)%4]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,1);
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,3);
			}
		}
	}
}

void DownCornerRestore(Cube *magiccube){
	while(!((magiccube->down.s[1][1]==magiccube->down.s[2][2]&&magiccube->front.s[3][1]==magiccube->front.s[2][2]&&magiccube->left.s[3][3]==magiccube->left.s[2][2])
		&&(magiccube->down.s[1][3]==magiccube->down.s[2][2]&&magiccube->front.s[3][3]==magiccube->front.s[2][2]&&magiccube->right.s[3][1]==magiccube->right.s[2][2])
		&&(magiccube->down.s[3][1]==magiccube->down.s[2][2]&&magiccube->right.s[3][1]==magiccube->right.s[2][2]&&magiccube->back.s[3][3]==magiccube->back.s[2][2])
		&&(magiccube->down.s[3][3]==magiccube->down.s[2][2]&&magiccube->back.s[3][1]==magiccube->back.s[2][2]&&magiccube->right.s[3][3]==magiccube->right.s[2][2])))//鐩村埌搴曡鍏ㄩ儴褰掍綅
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int subscript_of_down[4][2]={{1,1},{3,1},{3,3},{1,3}};
		int subscript_of_up[4][2]={{3,1},{1,1},{1,3},{3,3}};	
		char ch[3];
		int n;
		for(int i=0;i<4;i++)
		{
			if(magiccube->down.s[subscript_of_down[i][0]][subscript_of_down[i][1]]==magiccube->down.s[2][2]&&
				(sur[i]->s[3][1]!=sur[i]->s[2][2]||sur[(i+1)%4]->s[3][3]!=sur[(i+1)%4]->s[2][2]))
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
			}
			if(magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]==magiccube->down.s[2][2])
			{
				n=0;
				while(sur[(i+n)%4]->s[1][1]!=sur[(i+n+1)%4]->s[2][2])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				strcpy(ch,s[(i+n)%4]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",3);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",2);
			}
			if(sur[i]->s[1][1]==magiccube->down.s[2][2])
			{
				n=0;
				while(sur[(i+n+1)%4]->s[2][2]!=sur[(i+n+1)%4]->s[1][3])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				strcpy(ch,s[(n+i)%4]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
			}
			if(sur[i]->s[1][3]==magiccube->down.s[2][2])
			{
				n=0;
				while(sur[(i+n+3)%4]->s[2][2]!=sur[(i+n+3)%4]->s[1][1])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				strcpy(ch,s[(n+i)%4]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",3);
				MoveCube(magiccube,ch,1);
			}
			if(sur[i]->s[3][1]==magiccube->down.s[2][2])
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
			}
			if(sur[i]->s[3][3]==magiccube->down.s[2][2])
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",3);
				MoveCube(magiccube,ch,1);
			}
		}
	}
}

void CentreEdgeRestore(Cube *magiccube)
{
	while(!((magiccube->front.s[2][1]==magiccube->front.s[2][2]&&magiccube->front.s[2][3]==magiccube->front.s[2][2])
		&&(magiccube->left.s[2][1]==magiccube->left.s[2][2]&&magiccube->left.s[2][3]==magiccube->left.s[2][2])
		&&(magiccube->back.s[2][1]==magiccube->back.s[2][2]&&magiccube->back.s[2][3]==magiccube->back.s[2][2])
		&&(magiccube->right.s[2][1]==magiccube->right.s[2][2]&&magiccube->right.s[2][3]==magiccube->right.s[2][2])))
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int subscript_of_up[4][2]={{3,2},{2,1},{1,2},{2,3}};
		char ch[3];
		int n;
		for(int i=0;i<4;i++)
		{
			if(!(sur[i]->s[2][1]==sur[i]->s[2][2]&&sur[(i+1)%4]->s[2][3]==sur[(i+1)%4]->s[2][2])
				&&(sur[i]->s[2][1]!=magiccube->up.s[2][2]&&sur[(i+1)%4]->s[2][3]!=magiccube->up.s[2][2]))
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",3);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",3);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",2);
			}
			if(sur[i]->s[1][2]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]!=magiccube->up.s[2][2])
			{
				n=0;
				while(sur[(i+n)%4]->s[1][2]!=sur[(i+n)%4]->s[2][2])
				{
					n++;
					MoveCube(magiccube,"u",1);
				}
				if(magiccube->up.s[subscript_of_up[(i+n)%4][0]][subscript_of_up[(i+n)%4][1]]==sur[(i+n+3)%4]->s[2][2])
				{
					strcpy(ch,s[(i+n)%4]);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",3);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",3);
					MoveCube(magiccube,ch,3);
				}
				if(magiccube->up.s[subscript_of_up[(i+n)%4][0]][subscript_of_up[(i+n)%4][1]]==sur[(i+n+1)%4]->s[2][2])
				{
					strcpy(ch,s[(i+n)%4]);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",3);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",3);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
				}
			}
		}
	}
}

void UpCross(Cube *magiccube)
{
	while(!(magiccube->up.s[1][2]==magiccube->up.s[2][2]&&magiccube->up.s[2][1]==magiccube->up.s[2][2]
		&&magiccube->up.s[2][3]==magiccube->up.s[2][2]&&magiccube->up.s[3][2]==magiccube->up.s[2][2]))
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int subscript_of_up[4][2]={{3,2},{2,1},{1,2},{2,3}};
		char ch[3];
		if(magiccube->up.s[1][2]!=magiccube->up.s[2][2]&&magiccube->up.s[2][1]!=magiccube->up.s[2][2]
		&&magiccube->up.s[2][3]!=magiccube->up.s[2][2]&&magiccube->up.s[3][2]!=magiccube->up.s[2][2])
		{
			MoveCube(magiccube,"f",1);
			MoveCube(magiccube,"r",1);
			MoveCube(magiccube,"u",1);
			MoveCube(magiccube,"r",3);
			MoveCube(magiccube,"u",3);
			MoveCube(magiccube,"f",3);
		}
		for(int i=0;i<4;i++)
		{
			if(magiccube->up.s[subscript_of_up[(i+1)%4][0]][subscript_of_up[(i+1)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+2)%4][0]][subscript_of_up[(i+2)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+3)%4][0]][subscript_of_up[(i+3)%4][1]]!=magiccube->up.s[2][2])
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,1);
				strcpy(ch,s[(i+3)%4]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",3);
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,3);
			}
			if(magiccube->up.s[subscript_of_up[(i+1)%4][0]][subscript_of_up[(i+1)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+3)%4][0]][subscript_of_up[(i+3)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+2)%4][0]][subscript_of_up[(i+2)%4][1]]!=magiccube->up.s[2][2])
			{
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,1);
				strcpy(ch,s[(i+3)%4]);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",3);
				strcpy(ch,s[i]);
				MoveCube(magiccube,ch,3);
			}
		}
	}
}

void UpSurfaceCornerRestore(Cube *magiccube)
{
	while(!(magiccube->up.s[1][1]==magiccube->up.s[2][2]&&magiccube->up.s[1][3]==magiccube->up.s[2][2]
		&&magiccube->up.s[3][1]==magiccube->up.s[2][2]&&magiccube->up.s[3][3]==magiccube->up.s[2][2]))
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int subscript_of_up[4][2]={{3,1},{1,1},{1,3},{3,3}};
		char ch[3];
		int n;
		for(int i=0;i<4;i++)
		{
			if((magiccube->up.s[1][1]!=magiccube->up.s[2][2]&&magiccube->up.s[1][3]!=magiccube->up.s[2][2]
				&&magiccube->up.s[3][1]!=magiccube->up.s[2][2]&&magiccube->up.s[3][3]!=magiccube->up.s[2][2])
				&&(sur[i]->s[1][1]==magiccube->up.s[2][2]&&sur[i]->s[1][3]==magiccube->up.s[2][2]))
			{
				n=0;
				while(sur[(i+n)%4]->s[1][2]!=sur[(i+n)%4]->s[2][2])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				strcpy(ch,s[(i+n+3)%4]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",2);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,1);
			}
			if(magiccube->up.s[subscript_of_up[(i+3)%4][0]][subscript_of_up[(i+3)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+1)%4][0]][subscript_of_up[(i+1)%4][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+2)%4][0]][subscript_of_up[(i+2)%4][1]]!=magiccube->up.s[2][2])
			{
				if(sur[i]->s[1][1]!=magiccube->up.s[2][2])
				{
					strcpy(ch,s[(i+3)%4]);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",2);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
				}
				else
				{
					MoveCube(magiccube,"u",3);
					strcpy(ch,s[(i+3)%4]);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",2);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",3);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",3);
					MoveCube(magiccube,ch,3);
				}
			}
			if(magiccube->up.s[subscript_of_up[(i+1)%4][0]][subscript_of_up[(i+1)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+3)%4][0]][subscript_of_up[(i+3)%4][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+2)%4][0]][subscript_of_up[(i+2)%4][1]]==magiccube->up.s[2][2])
			{
				if(sur[i]->s[1][1]==magiccube->up.s[2][2]&&sur[i]->s[1][3]==magiccube->up.s[2][2])
				{
					strcpy(ch,s[(i+1)%4]);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",2);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
				}
				else
				{
					strcpy(ch,s[(i+2)%4]);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",2);
					MoveCube(magiccube,ch,1);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,3);
					MoveCube(magiccube,"u",1);
					MoveCube(magiccube,ch,1);
				}
			}
			if(magiccube->up.s[subscript_of_up[(i+3)%4][0]][subscript_of_up[(i+3)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[i][0]][subscript_of_up[i][1]]!=magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+1)%4][0]][subscript_of_up[(i+1)%4][1]]==magiccube->up.s[2][2]
				&&magiccube->up.s[subscript_of_up[(i+2)%4][0]][subscript_of_up[(i+2)%4][1]]!=magiccube->up.s[2][2])
			{
				MoveCube(magiccube,"u",3);
				strcpy(ch,s[(i+3)%4]);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",2);
				MoveCube(magiccube,ch,1);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,3);
				MoveCube(magiccube,"u",1);
				MoveCube(magiccube,ch,1);
			}
		}
	}
}

void UpCornerRestore(Cube *magiccube)
{
	while(magiccube->front.s[1][1]!=magiccube->front.s[2][2])
		MoveCube(magiccube,"u",1);
	while(!((magiccube->front.s[1][1]==magiccube->front.s[2][2]&&magiccube->front.s[1][3]==magiccube->front.s[2][2])
		&&(magiccube->left.s[1][1]==magiccube->left.s[2][2]&&magiccube->left.s[1][3]==magiccube->left.s[2][2])
		&&(magiccube->back.s[1][1]==magiccube->back.s[2][2]&&magiccube->back.s[1][3]==magiccube->back.s[2][2])
		&&(magiccube->right.s[1][1]==magiccube->right.s[2][2]&&magiccube->right.s[1][3]==magiccube->right.s[2][2])))
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int n;
		char ch[3];
		for(int i=0;i<4;i++)
		{
			n=0;
			if(sur[i]->s[1][1]==sur[i]->s[1][3])
			{
				while(sur[(i+n)%4]->s[1][1]!=sur[(i+n)%4]->s[2][2])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				break;
			}
		}
		strcpy(ch,s[(i+n+3)%4]);
		MoveCube(magiccube,ch,1);
		strcpy(ch,s[(i+n+2)%4]);
		MoveCube(magiccube,ch,3);
		strcpy(ch,s[(i+n+3)%4]);
		MoveCube(magiccube,ch,1);
		strcpy(ch,s[(i+n)%4]);
		MoveCube(magiccube,ch,2);
		strcpy(ch,s[(i+n+3)%4]);
		MoveCube(magiccube,ch,3);
		strcpy(ch,s[(i+n+2)%4]);
		MoveCube(magiccube,ch,1);
		strcpy(ch,s[(i+n+3)%4]);
		MoveCube(magiccube,ch,1);
		strcpy(ch,s[(i+n)%4]);
		MoveCube(magiccube,ch,2);
		strcpy(ch,s[(i+n+3)%4]);
		MoveCube(magiccube,ch,2);
		while(magiccube->front.s[1][1]!=magiccube->front.s[2][2])
			MoveCube(magiccube,"u",1);
	}
}

void UpEdgeRestore(Cube *magiccube)
{
	while(magiccube->front.s[1][1]!=magiccube->front.s[2][2])
		MoveCube(magiccube,"u",1);
	while(!(magiccube->front.s[1][2]==magiccube->front.s[2][2]&&magiccube->left.s[1][2]==magiccube->left.s[2][2]
		&&magiccube->back.s[1][2]==magiccube->back.s[2][2]&&magiccube->right.s[1][2]==magiccube->right.s[2][2]))
	{
		Surface *sur[4]={&magiccube->front,&magiccube->left,&magiccube->back,&magiccube->right};
		char *s[4]={"f","l","b","r"};
		int n;
		char ch[3];
		for(int i=0;i<4;i++)
		{
			n=0;
			if(sur[i]->s[1][1]==sur[i]->s[1][2]&&sur[i]->s[1][2]==sur[i]->s[1][3])
			{
				while(sur[(i+n)%4]->s[1][1]!=sur[(i+n)%4]->s[2][2])
				{
					MoveCube(magiccube,"u",1);
					n++;
				}
				break;
			}
		}
		strcpy(ch,s[(i+n+1)%4]);
		MoveCube(magiccube,ch,1);
		MoveCube(magiccube,"u",3);
		MoveCube(magiccube,ch,1);
		MoveCube(magiccube,"u",1);
		MoveCube(magiccube,ch,1);
		MoveCube(magiccube,"u",1);
		MoveCube(magiccube,ch,1);
		MoveCube(magiccube,"u",3);
		MoveCube(magiccube,ch,3);
		MoveCube(magiccube,"u",3);
		MoveCube(magiccube,ch,2);
		while(magiccube->front.s[1][1]!=magiccube->front.s[2][2])
			MoveCube(magiccube,"u",1);
	}
}

void printsurface(Surface sur)
{
	int i,j;
	for(i=1;i<=3;i++)
	{
		for(j=1;j<=3;j++)
			printf("%d ",(int)sur.s[i][j]);
		printf("\n");
	}
}

void PrintMagicCube(Cube m)
{
	printf("\nThe Colors of Up:\n");
	printsurface(m.up);
	printf("\nThe Colors of Down:\n");
	printsurface(m.down);
	printf("\nThe Colors of Front:\n");
	printsurface(m.front);
	printf("\nThe Colors of Back:\n");
	printsurface(m.back);
	printf("\nThe Colors of Left:\n");
	printsurface(m.left);
	printf("\nThe Colors of Right:\n");
	printsurface(m.right);
}

void PrintBuf()
{
	SNode *p;
	int i;
	printf("The Sequence of the change of the Magiccube is:\n");
	for(p=CD.head,i=1;p;p=p->next,i++)
	{
		printf("%s%d\t",p->chbuf,p->times);
		if(i==5)
		{
			putchar('\n');
			printf("------------------------------------\n");
			i=0;
		}
	}
	printf("\n\n\n",CD.num);
}

void InitializationMagiccube(Cube *m)
{

	m->up.s[1][1]=(Colors)2;m->up.s[1][2]=(Colors)4;m->up.s[1][3]=(Colors)4;
	m->up.s[2][1]=(Colors)3;m->up.s[2][2]=(Colors)5;m->up.s[2][3]=(Colors)6;
	m->up.s[3][1]=(Colors)2;m->up.s[3][2]=(Colors)1;m->up.s[3][3]=(Colors)5;

	m->down.s[1][1]=(Colors)3;m->down.s[1][2]=(Colors)3;m->down.s[1][3]=(Colors)6;
	m->down.s[2][1]=(Colors)5;m->down.s[2][2]=(Colors)3;m->down.s[2][3]=(Colors)1;
	m->down.s[3][1]=(Colors)4;m->down.s[3][2]=(Colors)6;m->down.s[3][3]=(Colors)6;

	m->front.s[1][1]=(Colors)5;m->front.s[1][2]=(Colors)5;m->front.s[1][3]=(Colors)1;
	m->front.s[2][1]=(Colors)2;m->front.s[2][2]=(Colors)4;m->front.s[2][3]=(Colors)6;
	m->front.s[3][1]=(Colors)2;m->front.s[3][2]=(Colors)2;m->front.s[3][3]=(Colors)3;

	m->back.s[1][1]=(Colors)5;m->back.s[1][2]=(Colors)2;m->back.s[1][3]=(Colors)3;
	m->back.s[2][1]=(Colors)6;m->back.s[2][2]=(Colors)1;m->back.s[2][3]=(Colors)4;
	m->back.s[3][1]=(Colors)3;m->back.s[3][2]=(Colors)3;m->back.s[3][3]=(Colors)6;
	
	m->left.s[1][1]=(Colors)1;m->left.s[1][2]=(Colors)4;m->left.s[1][3]=(Colors)1;
	m->left.s[2][1]=(Colors)5;m->left.s[2][2]=(Colors)6;m->left.s[2][3]=(Colors)1;
	m->left.s[3][1]=(Colors)5;m->left.s[3][2]=(Colors)2;m->left.s[3][3]=(Colors)4;

	m->right.s[1][1]=(Colors)6;m->right.s[1][2]=(Colors)5;m->right.s[1][3]=(Colors)2;
	m->right.s[2][1]=(Colors)1;m->right.s[2][2]=(Colors)2;m->right.s[2][3]=(Colors)4;
	m->right.s[3][1]=(Colors)1;m->right.s[3][2]=(Colors)3;m->right.s[3][3]=(Colors)4;
}

void Exit()
{
	SNode *p,*q;
	for(p=CD.head;p;p=q)
	{
		q=p->next;
		free(p->chbuf);free(p);
	}
	printf("Press any key to exit...");
	getch();
}

void main()
{
	Cube magiccube;
	int i=0;
	CD.num=0;
	CD.head=NULL;
	Input(&magiccube);

	DownCross(&magiccube);	
	DownCornerRestore(&magiccube);
	CentreEdgeRestore(&magiccube);
	UpCross(&magiccube);
	UpSurfaceCornerRestore(&magiccube);
	UpCornerRestore(&magiccube);
	UpEdgeRestore(&magiccube);
	PrintMagicCube(magiccube);
	PrintBuf();
	Exit();
}
