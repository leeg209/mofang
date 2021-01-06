#include<stdio.h>
#include<time.h>
#include<stdlib.h>


typedef enum color {
	bule = 'b',
	red = 'r',
	green = 'g',
	orange = 'o',
	yellow = 'y',
	white = 'w'
}Color;

/**
 * @brief ħ������ṹ��     Color ���͵�4x4����  ����ÿ��������3x3 ��С�� ����������ϰ������ȡ1-3
*/
typedef struct face {
	Color  s[4][4];
}Face;

/**
 * @brief   ħ���Ľṹ��   ���� �� �� ǰ �� �� �� ��
*/
typedef struct cube {
	Face up, down, front, back, left, right;
}Cube;

/*@} */



/*@defgroup ����ħ���ķ���{ */


void CW_Face(Face* f);   /* clockwise face ˳ʱ����ת�� */
void CCW_Face(Face* f);  /* counter-clockwise face ��ʱ��ʱ����ת�� */
void R(Cube* box);  /*  ˳ʱ����ת���� */
void CR(Cube* box);  /* ��ʱ����ת���� */
void L(Cube* box);  /*  ˳ʱ����ת���� */
void CL(Cube* box);  /* ��ʱ����ת���� */
void B(Cube* box);  /*  ˳ʱ����ת���� */
void CB(Cube* box);  /* ��ʱ����ת���� */
void F(Cube* box);  /*  ˳ʱ����תǰ�� */
void CF(Cube* box);  /* ��ʱ����תǰ�� */
void U(Cube* box);  /*  ˳ʱ����ת���� */
void CU(Cube* box);  /* ��ʱ����ת���� */
void InitFace(Face* f, char e);/* ��ʼ���� */
void InitCube(Cube* box);/* ��ʼ��ħ�� */
void PrintFace(Face* f); /* ��ӡ�� */
void PrintCube(Cube* box); /* ��ӡħ�� */


/*@}*/


void RdCune(Cube* box); //����ħ��



/*@defgroup ���ȷ���ħ����7���㷨 {*/
void SubfaceCross(Cube* box);				/* 1.����ʮ�� */
void SubfaxeCornerRestore(Cube* box);		/* 2.�ײ��ǿ黹ԭ */
void CentreEdgeRestore(Cube* box);			/* 3.�����λ */
void UpCross(Cube* box);				/* 4.����ʮ�� */
void UpSurfaceCornerRestore(Cube* box);		/* 5.������λ */
void UpCornerRestore(Cube* box);			/* 6.���ǻ�ԭ */
void UpEdgeRestore(Cube* box);				/* 7.���⻹ԭ */
/*@} */


/**
 * @brief
 * @param f
*/
void CW_Face(Face* f)
{
	Face t;     //����һ���ṹ��洢��ʼ״̬
	t = *f;
	f->s[1][1] = t.s[3][1];   // �����ɫ�仯
	f->s[1][2] = t.s[2][1];
	f->s[1][3] = t.s[1][1];
	f->s[2][1] = t.s[3][2];
	f->s[2][2] = t.s[2][2];
	f->s[2][3] = t.s[1][2];
	f->s[3][1] = t.s[3][3];
	f->s[3][2] = t.s[2][3];
	f->s[3][3] = t.s[1][3];
}
/**
 * @brief
 * @param f
*/
void CCW_Face(Face* f)
{
	///
	Face t;		//����һ���ṹ��洢��ʼ״̬
	t = *f;


	f->s[1][1] = t.s[1][3];    // �����ɫ�仯
	f->s[1][2] = t.s[2][3];
	f->s[1][3] = t.s[3][3];
	f->s[2][1] = t.s[1][2];
	f->s[2][2] = t.s[2][2];
	f->s[2][3] = t.s[3][2];
	f->s[3][1] = t.s[1][1];
	f->s[3][2] = t.s[2][1];
	f->s[3][3] = t.s[3][1];
}

/**
 * @brief  ˳ʱ����ת ����
 * @param box
*/
void R(Cube* box)
{
	Cube n;
	n = *box;
	CW_Face(&box->right); //right �����ɫ�仯

	box->up.s[1][3] = n.front.s[1][3];  // ��Ӧ up ��ı仯
	box->up.s[2][3] = n.front.s[2][3];
	box->up.s[3][3] = n.front.s[3][3];

	box->front.s[1][3] = n.down.s[1][3];	 // ��Ӧ front ��ı仯
	box->front.s[2][3] = n.down.s[2][3];
	box->front.s[3][3] = n.down.s[3][3];

	box->down.s[1][3] = n.back.s[1][3];		 // ��Ӧ down ��ı仯
	box->down.s[2][3] = n.back.s[2][3];
	box->down.s[3][3] = n.back.s[3][3];

	box->back.s[1][3] = n.up.s[1][3];		 // ��Ӧ back��ı仯
	box->back.s[2][3] = n.up.s[2][3];
	box->back.s[3][3] = n.up.s[3][3];
}
/**
 * @brief ��ʱ��ʱ����
 * @param box  ħ���ṹ��
*/
void CR(Cube* box)
{
	Cube n;
	n = *box;
	CCW_Face(&box->right);
	box->up.s[1][3] = n.back.s[1][3];
	box->up.s[2][3] = n.back.s[2][3];
	box->up.s[3][3] = n.back.s[3][3];
	box->front.s[1][3] = n.up.s[1][3];
	box->front.s[2][3] = n.up.s[2][3];
	box->front.s[3][3] = n.up.s[3][3];
	box->down.s[1][3] = n.front.s[1][3];
	box->down.s[2][3] = n.front.s[2][3];
	box->down.s[3][3] = n.front.s[3][3];
	box->back.s[1][3] = n.down.s[1][3];
	box->back.s[2][3] = n.down.s[2][3];
	box->back.s[3][3] = n.down.s[3][3];

}
/**
 * @brief
 * @param box
*/
void L(Cube* box)
{
	Cube n;
	n = *box;
	CW_Face(&box->left);
	box->up.s[1][1] = n.back.s[1][1];
	box->up.s[2][1] = n.back.s[2][1];
	box->up.s[3][1] = n.back.s[3][1];
	box->front.s[1][1] = n.up.s[1][1];
	box->front.s[2][1] = n.up.s[2][1];
	box->front.s[3][1] = n.up.s[3][1];
	box->down.s[1][1] = n.front.s[1][1];
	box->down.s[2][1] = n.front.s[2][1];
	box->down.s[3][1] = n.front.s[3][1];
	box->back.s[1][1] = n.down.s[1][1];
	box->back.s[2][1] = n.down.s[2][1];
	box->back.s[3][1] = n.down.s[3][1];

}
/**
 * @brief
 * @param box
*/
void CL(Cube* box)
{
	Cube n;
	n = *box;
	CCW_Face(&box->left);


	box->up.s[1][1] = n.front.s[1][1];
	box->up.s[2][1] = n.front.s[2][1];
	box->up.s[3][1] = n.front.s[3][1];
	box->front.s[1][1] = n.down.s[1][1];
	box->front.s[2][1] = n.down.s[2][1];
	box->front.s[3][1] = n.down.s[3][1];
	box->down.s[1][1] = n.back.s[1][1];
	box->down.s[2][1] = n.back.s[2][1];
	box->down.s[3][1] = n.back.s[3][1];
	box->back.s[1][1] = n.up.s[1][1];
	box->back.s[2][1] = n.up.s[2][1];
	box->back.s[3][1] = n.up.s[3][1];
}
/**
 * @brief
 * @param box
*/
void B(Cube* box)
{
	Cube n;
	n = *box;
	CW_Face(&box->back);
	box->up.s[1][1] = n.right.s[1][3];
	box->up.s[1][2] = n.right.s[2][3];
	box->up.s[1][3] = n.right.s[3][3];
	box->right.s[1][3] = n.down.s[3][3];
	box->right.s[2][3] = n.down.s[3][2];
	box->right.s[3][3] = n.down.s[3][1];
	box->down.s[3][1] = n.left.s[1][1];
	box->down.s[3][2] = n.left.s[2][1];
	box->down.s[3][3] = n.left.s[3][1];
	box->left.s[1][1] = n.up.s[1][3];
	box->left.s[2][1] = n.up.s[1][2];
	box->left.s[3][1] = n.up.s[1][1];

}
/**
 * @brief
 * @param box
*/
void CB(Cube* box)
{
	Cube n;
	n = *box;
	CCW_Face(&box->back);
	box->up.s[1][1] = n.left.s[3][1];
	box->up.s[1][2] = n.left.s[2][1];
	box->up.s[1][3] = n.left.s[1][1];
	box->right.s[1][3] = n.up.s[1][1];
	box->right.s[2][3] = n.up.s[1][2];
	box->right.s[3][3] = n.up.s[1][3];
	box->down.s[3][1] = n.right.s[3][3];
	box->down.s[3][2] = n.right.s[2][3];
	box->down.s[3][3] = n.right.s[1][3];
	box->left.s[1][1] = n.down.s[3][1];
	box->left.s[2][1] = n.down.s[3][2];
	box->left.s[3][1] = n.down.s[3][3];
}
/**
 * @brief
 * @param box
*/
void F(Cube* box)
{
	Cube n;
	n = *box;
	CW_Face(&box->front);
	box->up.s[3][1] = n.left.s[3][3];
	box->up.s[3][2] = n.left.s[2][3];
	box->up.s[3][3] = n.left.s[1][3];
	box->right.s[1][1] = n.up.s[3][1];
	box->right.s[2][1] = n.up.s[3][2];
	box->right.s[3][1] = n.up.s[3][3];
	box->down.s[1][1] = n.right.s[3][1];
	box->down.s[1][2] = n.right.s[2][1];
	box->down.s[1][3] = n.right.s[1][1];
	box->left.s[1][3] = n.down.s[1][1];
	box->left.s[2][3] = n.down.s[1][2];
	box->left.s[3][3] = n.down.s[1][3];
}
/**
 * @brief
 * @param box
*/
void CF(Cube* box)
{
	Cube n;
	n = *box;
	CCW_Face(&box->front);
	box->up.s[3][1] = n.right.s[1][1];
	box->up.s[3][2] = n.right.s[2][1];
	box->up.s[3][3] = n.right.s[3][1];
	box->right.s[1][1] = n.down.s[1][3];
	box->right.s[2][1] = n.down.s[1][2];
	box->right.s[3][1] = n.down.s[1][1];
	box->down.s[1][1] = n.left.s[1][3];
	box->down.s[1][2] = n.left.s[2][3];
	box->down.s[1][3] = n.left.s[3][3];
	box->left.s[1][3] = n.up.s[3][3];
	box->left.s[2][3] = n.up.s[3][2];
	box->left.s[3][3] = n.up.s[3][1];
}
/**
 * @brief
 * @param box
*/

void U(Cube* box)
{
	Cube n;
	n = *box;
	CW_Face(&box->up);
	box->front.s[1][1] = n.right.s[1][1];
	box->front.s[1][2] = n.right.s[1][2];
	box->front.s[1][3] = n.right.s[1][3];
	box->right.s[1][1] = n.back.s[3][3];
	box->right.s[1][2] = n.back.s[3][2];
	box->right.s[1][3] = n.back.s[3][1];
	box->back.s[3][1] = n.left.s[1][3];
	box->back.s[3][2] = n.left.s[1][2];
	box->back.s[3][3] = n.left.s[1][1];
	box->left.s[1][1] = n.front.s[1][1];
	box->left.s[1][2] = n.front.s[1][2];
	box->left.s[1][3] = n.front.s[1][3];

}
/**
 * @brief
 * @param box
*/
void CU(Cube* box)
{
	Cube n;
	n = *box;
	CCW_Face(&box->up);
	box->front.s[1][1] = n.left.s[1][1];
	box->front.s[1][2] = n.left.s[1][2];
	box->front.s[1][3] = n.left.s[1][3];
	box->right.s[1][1] = n.front.s[1][1];
	box->right.s[1][2] = n.front.s[1][2];
	box->right.s[1][3] = n.front.s[1][3];
	box->back.s[3][1] = n.right.s[1][3];
	box->back.s[3][2] = n.right.s[1][2];
	box->back.s[3][3] = n.right.s[1][1];
	box->left.s[1][1] = n.back.s[3][3];
	box->left.s[1][2] = n.back.s[3][2];
	box->left.s[1][3] = n.back.s[3][1];
}
/**
 * @brief
 * @param box
*/

/**
 * @brief
 * @param f
 * @param e
*/
void InitFace(Face* f, char c)
{
	int i, j;
	
	for (i = 1; i <= 3; i++)
		for (j = 1; j <= 3; j++)
		{

			f->s[i][j]=c;
		}
}
/**
 * @brief
 * @param box
*/
void InitCube(Cube* box)
{



	InitFace(&(box->up), 'y');

	InitFace(&(box->down), 'w');

	InitFace(&(box->front), 'b');

	InitFace(&(box->back), 'g');

	InitFace(&(box->left), 'o');

	InitFace(&(box->right), 'r');
}
/**
 * @brief �������ɫ
 * @param f
*/
void PrintFace(Face* f)
{
	int i, j;
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 3; j++)
			printf("%c", f->s[i][j]);
		printf("\n");
	}
}
/**
 * @brief ���ħ����ɫ
 * @param box
*/
void PrintCube(Cube* box)
{
	printf("\n������ɫ:\n");
	PrintFace(&box->up);
	printf("\n������ɫ:\n");
	PrintFace(&box->down);
	printf("\nǰ����ɫ:\n");
	PrintFace(&box->front);
	printf("\n������ɫ:\n");
	PrintFace(&box->back);
	printf("\n�����ɫ:\n");
	PrintFace(&box->left);
	printf("\n�ұ���ɫ:\n");
	PrintFace(&box->right);
}
/**
 * @brief ����ħ������
 * @param box
*/
void RdCune(Cube* box)
{
	F(box);


	U(box);
	B(box);
	U(box);
	U(box);

	F(box);

	CL(box);


}



/**
 * @brief  ����ʮ��
 * @param box
*/
void SubfaceCross(Cube* box)
{
	while (!((box->down.s[1][2] == 'w' && box->front.s[3][2] == 'b')
		&& (box->down.s[2][1] == 'w' && box->left.s[3][2] == 'o')
		&& (box->down.s[2][3] == 'w' && box->right.s[3][2] == 'r')
		&& (box->down.s[3][2] == 'w' && box->back.s[1][2] == 'g')))
	{

		/*@group  �ײ��ĸ����{*/
		/**
		 * @brief FD
		 *
		*/
		switch (box->down.s[1][2])
		{
		case 'w': //�ײ���
			switch (box->front.s[3][2])
			{
			case 'b':
				break;
			case 'o':
				F(box);
				F(box);
				U(box);
				L(box);
				L(box);
				break;
			case 'r':
				CF(box);
				CF(box);
				CU(box);
				CR(box);
				CR(box);


				break;
			case 'g':
				F(box);
				F(box);
				U(box);
				U(box);
				B(box);
				B(box);


				break;
			default:
				break;
			}
			break;
		case 'b':  //�ײ���
			switch (box->front.s[3][2])
			{
			case 'w':
				CF(box);
				R(box);
				U(box);
				CR(box);
				CF(box);
				CF(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->front.s[3][2])
			{
			case 'w':
				F(box);
				L(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->front.s[3][2])
			{
			case 'w':
				CF(box);
				CR(box);
				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->front.s[3][2])
			{
			case 'w':
				CF(box);
				CF(box);
				CU(box);
				R(box);
				CB(box);
				CR(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		/**
		 * @brief RD
		 *
		*/
		switch (box->down.s[2][3])
		{
		case 'w':
			switch (box->right.s[3][2])
			{
			case 'b':
				R(box);
				R(box);
				U(box);
				F(box);
				F(box);
				break;
			case 'o':
				R(box);
				R(box);
				U(box);
				U(box);
				L(box);
				L(box);

				break;
			case 'r':
				break;
			case 'g':
				R(box);
				R(box);
				CU(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':  //�ײ���
			switch (box->right.s[3][2])
			{
			case 'w':
				R(box);
				F(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[3][2])
			{
			case 'w':
				CR(box);
				CB(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[3][2])
			{
			case 'w':
				R(box);
				R(box);
				U(box);
				F(box);
				R(box);
				CF(box);
				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[3][2])
			{
			case 'w':
				CR(box);
				CB(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		/**
		 * @brief BD
		 *
		*/
		switch (box->down.s[3][2])
		{
		case 'w':
			switch (box->back.s[1][2])
			{
			case 'b':
				B(box);
				B(box);
				U(box);
				U(box);
				F(box);
				F(box);
				break;
			case 'o':
				B(box);
				B(box);
				CU(box);
				L(box);
				L(box);
				break;
			case 'r':
				B(box);
				B(box);
				U(box);
				R(box);
				R(box);
				break;
			case 'g':
				break;
			default:
				break;
			}
			break;

		case 'b':  //�ײ���
			switch (box->back.s[1][2])
			{
			case 'w':
				B(box);
				B(box);
				U(box);
				CR(box);
				F(box);
				R(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->back.s[1][2])
			{
			case 'w':
				CB(box);
				CL(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->back.s[1][2])
			{
			case 'w':
				B(box);
				R(box);

				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->back.s[1][2])
			{
			case 'w':
				B(box);
				CR(box);
				CU(box);
				B(box);
				B(box);
				R(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		/**
		 * @brief  LD
		 *
		*/
		switch (box->down.s[2][1])
		{
		case 'w':
			switch (box->left.s[3][2])
			{
			case 'b':
				CL(box);
				CL(box);
				CU(box);
				F(box);
				F(box);

				break;
			case 'o':
				break;
			case 'r':
				L(box);
				L(box);
				U(box);
				U(box);
				R(box);
				R(box);

				break;
			case 'g':
				L(box);
				L(box);
				U(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':  //�ײ���
			switch (box->left.s[3][2])
			{
			case 'w':
				CL(box);
				CF(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[3][2])
			{
			case 'w':
				B(box);
				B(box);
				CU(box);
				CF(box);
				L(box);
				F(box);

				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[3][2])
			{
			case 'w':
				B(box);
				B(box);
				U(box);
				U(box);
				R(box);
				R(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[3][2])
			{
			case 'w':
				L(box);
				B(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		/*@ }*/


		/*@group �м����{*/

		/**
		 * @brief  FR
		 *
		*/
		switch (box->front.s[2][3])
		{
		case 'w':
			switch (box->right.s[2][1])
			{
			case 'b':

				R(box);
				U(box);
				CR(box);
				F(box);
				F(box);

				break;
			case 'o':
				R(box);
				U(box);
				U(box);
				CR(box);
				L(box);
				L(box);
				break;
			case 'r':
				CR(box);
				break;
			case 'g':
				R(box);
				CU(box);
				CR(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->right.s[2][1])
			{
			case 'w':
				F(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[2][1])
			{
			case 'w':

				CF(box);
				CU(box);
				F(box);
				L(box);
				L(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[2][1])
			{
			case 'w':
				CF(box);
				CU(box);
				F(box);
				R(box);
				R(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[2][1])
			{
			case 'w':
				CF(box);
				CU(box);
				CU(box);
				F(box);
				B(box);
				B(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}




		/**
		 * @brief  FL
		 *
		*/
		switch (box->front.s[2][1])
		{
		case 'w':
			switch (box->left.s[2][3])
			{
			case 'b':

				CL(box);
				CU(box);
				L(box);
				F(box);
				F(box);

				break;
			case 'o':
				L(box);
				break;
			case 'r':
				F(box);
				F(box);
				R(box);
				CF(box);
				CF(box);

				break;
			case 'g':
				CL(box);
				U(box);
				L(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->left.s[2][3])
			{
			case 'w':
				CF(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[2][3])
			{
			case 'w':

				F(box);
				U(box);
				CF(box);
				L(box);
				L(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[2][3])
			{
			case 'w':
				F(box);
				CU(box);
				F(box);
				R(box);
				R(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[2][3])
			{
			case 'w':
				F(box);
				CU(box);
				CU(box);
				CF(box);
				B(box);
				B(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}


		/**
		 * @brief  BL
		 *
		*/
		switch (box->back.s[2][1])
		{
		case 'w':
			switch (box->left.s[2][1])
			{
			case 'b':

				L(box);
				CU(box);
				CL(box);
				F(box);
				F(box);

				break;
			case 'o':
				CL(box);
				break;
			case 'r':
				L(box);
				U(box);
				U(box);
				CL(box);
				R(box);
				R(box);
				break;
			case 'g':
				L(box);
				U(box);
				CL(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->left.s[2][1])
			{
			case 'w':
				L(box);
				L(box);
				CF(box);
				CL(box);
				CL(box);

				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[2][1])
			{
			case 'w':

				CB(box);
				CU(box);
				B(box);
				L(box);
				L(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[2][1])
			{
			case 'w':
				CB(box);
				U(box);
				B(box);
				R(box);
				R(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[2][1])
			{
			case 'w':
				B(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}


		/**
		 * @brief  BR
		 *
		*/
		switch (box->back.s[2][3])
		{
		case 'w':
			switch (box->right.s[2][3])
			{
			case 'b':

				CR(box);
				U(box);
				R(box);
				F(box);
				F(box);

				break;
			case 'o':
				B(box);
				B(box);
				CL(box);
				CB(box);
				CB(box);


				break;
			case 'r':
				R(box);
				break;
			case 'g':
				CR(box);
				CU(box);
				R(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->right.s[2][3])
			{
			case 'w':
				B(box);
				U(box);
				U(box);
				CB(box);
				F(box);
				F(box);

				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[2][3])
			{
			case 'w':

				B(box);
				CU(box);
				CB(box);
				L(box);
				L(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[2][3])
			{
			case 'w':
				B(box);
				U(box);
				CB(box);
				R(box);
				R(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[2][3])
			{
			case 'w':
				CB(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}




		/*@}*/

	/*@group �������{*/
	   /**
		 * @brief FU
		 *
		*/
		switch (box->up.s[3][2])
		{
		case 'w': //�ײ���
			switch (box->front.s[1][2])
			{
			case 'b':
				F(box);
				F(box);
				break;
			case 'o':

				U(box);
				L(box);
				L(box);
				break;
			case 'r':

				CU(box);
				CR(box);
				CR(box);


				break;
			case 'g':

				U(box);
				U(box);
				B(box);
				B(box);


				break;
			default:
				break;
			}
			break;
		case 'b':
			switch (box->front.s[1][2])
			{
			case 'w':

				U(box);
				L(box);
				CF(box);
				CL(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->front.s[1][2])
			{
			case 'w':
				CF(box);
				L(box);
				F(box);
				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->front.s[1][2])
			{
			case 'w':
				F(box);
				CR(box);
				CF(box);

				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->front.s[1][2])
			{
			case 'w':
				F(box);
				R(box);
				CU(box);
				CR(box);
				CF(box);
				B(box);
				B(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}


		/**
		 * @brief RU
		 *
		*/
		switch (box->up.s[2][3])
		{
		case 'w':
			switch (box->right.s[1][2])
			{
			case 'b':

				U(box);
				F(box);
				F(box);
				break;
			case 'o':

				U(box);
				U(box);
				L(box);
				L(box);

				break;
			case 'r':
				CR(box);
				CR(box);
				break;
			case 'g':

				CU(box);
				CB(box);
				CB(box);
				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->right.s[1][2])
			{
			case 'w':
				CR(box);
				F(box);
				R(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->right.s[1][2])
			{
			case 'w':
				CR(box);
				CF(box);
				U(box);
				R(box);
				F(box);
				L(box);
				L(box);


				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->right.s[1][2])
			{
			case 'w':

				U(box);
				F(box);
				CR(box);
				CF(box);
				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->right.s[1][2])
			{
			case 'w':
				R(box);
				CB(box);
				R(box);

				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		/**
		* @brief BU
		 *
		*/
		switch (box->up.s[1][2])
		{
		case 'w':
			switch (box->back.s[3][2])
			{
			case 'b':

				U(box);
				U(box);
				F(box);
				F(box);
				break;
			case 'o':

				CU(box);
				L(box);
				L(box);
				break;
			case 'r':

				U(box);
				R(box);
				R(box);
				break;
			case 'g':
				B(box);
				B(box);

				break;
			default:
				break;
			}
			break;

		case 'b':
			switch (box->back.s[3][2])
			{
			case 'w':
				B(box);
				B(box);
				U(box);
				CR(box);
				F(box);
				R(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->back.s[3][2])
			{
			case 'w':

				B(box);
				CL(box);
				CB(box);

				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->back.s[3][2])
			{
			case 'w':
				CB(box);
				R(box);
				B(box);

				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->back.s[3][2])
			{
			case 'w':

				U(box);
				R(box);
				CB(box);
				CR(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		/**
		 * @brief  LU
		 *
		*/
		switch (box->up.s[2][1])
		{
		case 'w':
			switch (box->left.s[1][2])
			{
			case 'b':

				CU(box);
				F(box);
				F(box);

				break;
			case 'o':
				L(box);
				L(box);
				break;
			case 'r':

				U(box);
				U(box);
				R(box);
				R(box);

				break;
			case 'g':

				U(box);
				B(box);
				B(box);
				break;
			default:
				break;
			}
			break;

		case 'b':  //�ײ���
			switch (box->left.s[1][2])
			{
			case 'w':
				L(box);
				CF(box);
				CL(box);
				break;

			default:
				break;
			}

			break;
		case 'o':
			switch (box->left.s[1][2])
			{
			case 'w':

				CU(box);
				CF(box);
				L(box);
				F(box);

				break;

			default:
				break;
			}
			break;
		case 'r':
			switch (box->left.s[1][2])
			{
			case 'w':

				U(box);
				F(box);
				CR(box);
				CF(box);


				break;

			default:
				break;
			}
			break;
		case 'g':
			switch (box->left.s[1][2])
			{
			case 'w':
				CL(box);
				B(box);
				L(box);
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}

		/*@}*/










	}

}











/**
 * @brief  �ײ��ǿ黹ԭ
 * @param box
 *
*/
void SubfaxeCornerRestore(Cube* box)
{
	while (!((box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')
		&& (box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')
		&& (box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')
		&& (box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')))
	{
		/**
		 * @brief	�ײ���
		 *
		*/
		if ((box->front.s[3][1] == 'w') || (box->left.s[3][3] == 'w') || (box->down.s[1][1] == 'w' && ((box->front.s[3][1] != 'b') || (box->left.s[3][3] != 'o'))))
		{
			U(box);
			F(box);
			CU(box);
			CF(box);
		}

		if ((box->front.s[3][3] == 'w') || (box->right.s[3][1] == 'w') || (box->down.s[1][3] == 'w' && !((box->front.s[3][3] == 'b') && (box->right.s[3][1] == 'r'))))
		{
			U(box);
			R(box);
			CU(box);
			CR(box);
		}
		if ((box->right.s[3][3] == 'w') || (box->back.s[1][3] == 'w') || (box->down.s[3][3] == 'w' && !((box->right.s[3][3] == 'r') && (box->back.s[1][3] == 'g'))))
		{
			U(box);
			B(box);
			CU(box);
			CB(box);
		}
		if ((box->left.s[3][1] == 'w') || (box->back.s[1][1] == 'w') || (box->down.s[3][1] == 'w' && !((box->left.s[3][1] == 'o') && (box->back.s[1][1] == 'g'))))
		{
			U(box);
			L(box);
			CU(box);
			CL(box);
		}

		switch (box->front.s[1][3])
		{
		case 'w':
			if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
				U(box);
				while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
					U(box);
					F(box);
					CU(box);
					CF(box);
				}


			}
			else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
				U(box);
				R(box);
				CU(box);
				CR(box);

			}
			else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
				U(box);
				U(box);
				U(box);
				L(box);
				CU(box);
				CL(box);

			}
			else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
				CU(box);
				U(box);
				B(box);
				CU(box);
				CB(box);


			}

			break;
		case 'b':
			if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
				while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
					U(box);
					R(box);
					CU(box);
					CR(box);
				}
			}
			else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
				U(box);
				while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
					U(box);
					L(box);
					CU(box);
					CL(box);
				}
			}



			break;
		case 'r':
			if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
				while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
					U(box);
					F(box);
					CU(box);
					CF(box);
				}
			}
			else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
				CU(box);
				while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
					U(box);
					B(box);
					CU(box);
					CB(box);
				}
			}
			break;
		case 'o':
			if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
				U(box);
				while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
					U(box);
					F(box);
					CU(box);
					CF(box);
				}
			}
			else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
				CU(box);
				CU(box);

				while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
					U(box);
					L(box);
					CU(box);
					CL(box);
				}
			}
			break;
		case 'g':
			if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
				CU(box);
				while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
					U(box);
					B(box);
					CU(box);
					CB(box);
				}
			}
			else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
				CU(box);
				CU(box);

				while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
					U(box);
					L(box);
					CU(box);
					CL(box);
				}
			}
			break;
		default:
			break;
		}



		if (box->up.s[3][1] == 'w' || box->front.s[1][1] == 'w' || box->left.s[1][3] == 'w') {
			CU(box);
			switch (box->front.s[1][3])
			{
			case 'w':
				if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
					U(box);
					U(box);
					F(box);
					CU(box);
					CF(box);


				}
				else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
					U(box);
					R(box);
					CU(box);
					CR(box);

				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
					U(box);
					U(box);
					U(box);
					L(box);
					CU(box);
					CL(box);

				}
				else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
					CU(box);
					U(box);
					B(box);
					CU(box);
					CB(box);


				}

				break;
			case 'b':
				if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						U(box);
						R(box);
						CU(box);
						CR(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
					U(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}



				break;
			case 'r':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						U(box);
						F(box);
						CU(box);
						CF(box);
					}
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
					CU(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						U(box);
						B(box);
						CU(box);
						CB(box);
					}
				}
				break;
			case 'o':
				if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
					U(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						U(box);
						F(box);
						CU(box);
						CF(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
					CU(box);
					CU(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}
				break;
			case 'g':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
					CU(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						U(box);
						B(box);
						CU(box);
						CB(box);
					}
				}
				else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
					CU(box);
					CU(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}
				break;
			default:
				break;
			}
		}
		if (box->up.s[1][1] == 'w' || box->back.s[3][1] == 'w' || box->left.s[1][1] == 'w') {
			CU(box);
			CU(box);
			switch (box->front.s[1][3])
			{
			case 'w':
				if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
					U(box);
					U(box);
					F(box);
					CU(box);
					CF(box);


				}
				else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
					U(box);
					R(box);
					CU(box);
					CR(box);

				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
					U(box);
					U(box);
					U(box);
					L(box);
					CU(box);
					CL(box);

				}
				else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
					CU(box);
					U(box);
					B(box);
					CU(box);
					CB(box);


				}

				break;
			case 'b':
				if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						U(box);
						R(box);
						CU(box);
						CR(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
					U(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}



				break;
			case 'r':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						U(box);
						F(box);
						CU(box);
						CF(box);
					}
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
					CU(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						U(box);
						B(box);
						CU(box);
						CB(box);
					}
				}
				break;
			case 'o':
				if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
					U(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						U(box);
						F(box);
						CU(box);
						CF(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
					CU(box);
					CU(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}
				break;
			case 'g':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
					CU(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						U(box);
						B(box);
						CU(box);
						CB(box);
					}
				}
				else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
					CU(box);
					CU(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}
				break;
			default:
				break;
			}

		}
		if (box->up.s[1][3] == 'w' || box->back.s[3][3] == 'w' || box->right.s[1][3] == 'w') {
			U(box);
			switch (box->front.s[1][3])
			{
			case 'w':
				if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'b') {
					U(box);
					U(box);
					F(box);
					CU(box);
					CF(box);


				}
				else if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'r') {
					U(box);
					R(box);
					CU(box);
					CR(box);

				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'o') {
					U(box);
					U(box);
					U(box);
					L(box);
					CU(box);
					CL(box);

				}
				else if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'g') {
					CU(box);
					U(box);
					B(box);
					CU(box);
					CB(box);


				}

				break;
			case 'b':
				if (box->up.s[3][3] == 'r' && box->right.s[1][1] == 'w') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						U(box);
						R(box);
						CU(box);
						CR(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'o') {
					U(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}



				break;
			case 'r':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'b') {
					while (!(box->down.s[1][3] == 'w' && box->front.s[3][3] == 'b' && box->right.s[3][1] == 'r')) {
						U(box);
						F(box);
						CU(box);
						CF(box);
					}
				}
				else if (box->up.s[3][3] == 'g' && box->right.s[1][1] == 'w') {
					CU(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						U(box);
						B(box);
						CU(box);
						CB(box);
					}
				}
				break;
			case 'o':
				if (box->up.s[3][3] == 'b' && box->right.s[1][1] == 'w') {
					U(box);
					while (!(box->down.s[1][1] == 'w' && box->front.s[3][1] == 'b' && box->left.s[3][3] == 'o')) {
						U(box);
						F(box);
						CU(box);
						CF(box);
					}
				}
				else if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'g') {
					CU(box);
					CU(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}
				break;
			case 'g':
				if (box->up.s[3][3] == 'w' && box->right.s[1][1] == 'r') {
					CU(box);
					while (!(box->down.s[3][3] == 'w' && box->back.s[1][3] == 'g' && box->right.s[3][3] == 'r')) {
						U(box);
						B(box);
						CU(box);
						CB(box);
					}
				}
				else if (box->up.s[3][3] == 'o' && box->right.s[1][1] == 'w') {
					CU(box);
					CU(box);

					while (!(box->down.s[3][1] == 'w' && box->left.s[3][1] == 'o' && box->back.s[1][1] == 'g')) {
						U(box);
						L(box);
						CU(box);
						CL(box);
					}
				}
				break;
			default:
				break;
			}
		}





	}


}


/**
 * @brief 3.�����λ
 * @param box
*/
void CentreEdgeRestore(Cube* box) {
	int counter = 0;
	while (!((box->front.s[2][1] == 'b' && box->front.s[2][3] == 'b')
		&& (box->left.s[2][1] == 'o' && box->left.s[2][3] == 'o')
		&& (box->back.s[2][1] == 'g' && box->back.s[2][3] == 'g')
		&& (box->right.s[2][1] == 'r' && box->right.s[2][3] == 'r')))
	{
		counter++;
		switch (box->front.s[1][2])
		{
		case 'b':
			switch (box->up.s[3][2])
			{
			case 'r':
				U(box);
				R(box);
				CU(box);
				CR(box);
				CU(box);
				CF(box);
				U(box);
				F(box);
				break;
			case 'o':
				CU(box);
				CL(box);
				U(box);
				L(box);
				U(box);
				F(box);
				CU(box);
				CF(box);
				break;
			default:
				break;
			}
		case 'r':
			switch (box->up.s[3][2])
			{
			case 'g':
				CU(box);
				U(box);
				B(box);
				CU(box);
				CB(box);
				CU(box);
				CR(box);
				U(box);
				R(box);
				break;
			case 'b':
				CU(box);
				CU(box);
				CF(box);
				U(box);
				F(box);
				U(box);
				R(box);
				CU(box);
				CR(box);
				break;
			default:
				break;
			}
			break;
		case 'g':
			switch (box->up.s[3][2])
			{
			case 'r':
				U(box);
				U(box);
				CU(box);
				CR(box);
				U(box);
				R(box);
				U(box);
				B(box);
				CU(box);
				CB(box);
				break;
			case 'o':
				U(box);
				U(box);
				U(box);
				L(box);
				CU(box);
				CL(box);
				CU(box);
				CB(box);
				U(box);
				B(box);
				break;

			default:
				break;
			}
			break;
		case 'o':
			switch (box->up.s[3][2])
			{
			case 'b':
				U(box);
				break;
			case 'g':
				U(box);
				U(box);
				F(box);
				CU(box);
				CF(box);
				CU(box);
				CL(box);
				U(box);
				L(box);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}



		if ((box->right.s[1][2] == 'r' && box->up.s[2][3] == 'b')
			|| (box->right.s[1][2] == 'r' && box->up.s[2][3] == 'g')
			|| (box->right.s[1][2] == 'b' && box->up.s[2][3] == 'r')
			|| (box->right.s[1][2] == 'b' && box->up.s[2][3] == 'o')
			|| (box->right.s[1][2] == 'o' && box->up.s[2][3] == 'g')
			|| (box->right.s[1][2] == 'o' && box->up.s[2][3] == 'b')
			|| (box->right.s[1][2] == 'g' && box->up.s[2][3] == 'r')
			|| (box->right.s[1][2] == 'g' && box->up.s[2][3] == 'o'))
		{
			U(box);
		}
		if ((box->back.s[3][2] == 'r' && box->up.s[1][2] == 'b')
			|| (box->back.s[3][2] == 'r' && box->up.s[1][2] == 'g')
			|| (box->back.s[3][2] == 'b' && box->up.s[1][2] == 'r')
			|| (box->back.s[3][2] == 'b' && box->up.s[1][2] == 'o')
			|| (box->back.s[3][2] == 'o' && box->up.s[1][2] == 'g')
			|| (box->back.s[3][2] == 'o' && box->up.s[1][2] == 'b')
			|| (box->back.s[3][2] == 'g' && box->up.s[1][2] == 'r')
			|| (box->back.s[3][2] == 'g' && box->up.s[1][2] == 'o'))
		{
			U(box);
			U(box);

		}
		if ((box->left.s[1][2] == 'r' && box->up.s[2][1] == 'b')
			|| (box->left.s[1][2] == 'r' && box->up.s[2][1] == 'g')
			|| (box->left.s[1][2] == 'b' && box->up.s[2][1] == 'r')
			|| (box->left.s[1][2] == 'b' && box->up.s[2][1] == 'o')
			|| (box->left.s[1][2] == 'o' && box->up.s[2][1] == 'g')
			|| (box->left.s[1][2] == 'o' && box->up.s[2][1] == 'b')
			|| (box->left.s[1][2] == 'g' && box->up.s[2][1] == 'r')
			|| (box->left.s[1][2] == 'g' && box->up.s[2][1] == 'o'))
		{
			CU(box);
		}
		/**
		 * @brief �м��������
		 *
		*/


		if (counter > 30)
		{
			if ((box->front.s[2][3] == 'g' && box->right.s[2][1] == 'o')
				|| (box->front.s[2][3] == 'r' && box->right.s[2][1] == 'b')
				|| (box->front.s[2][3] == 'r' && box->right.s[2][1] == 'g')
				|| (box->front.s[2][3] == 'b' && box->right.s[2][1] == 'r')
				|| (box->front.s[2][3] == 'b' && box->right.s[2][1] == 'o')
				|| (box->front.s[2][3] == 'o' && box->right.s[2][1] == 'g')
				|| (box->front.s[2][3] == 'o' && box->right.s[2][1] == 'b')
				|| (box->front.s[2][3] == 'g' && box->right.s[2][1] == 'r'))
			{
				U(box);
				R(box);
				CU(box);
				CR(box);
				CU(box);
				CF(box);
				U(box);
				F(box);
			}

			if ((box->left.s[2][3] == 'g' && box->front.s[2][1] == 'o')
				|| (box->left.s[2][3] == 'r' && box->front.s[2][1] == 'b')
				|| (box->left.s[2][3] == 'r' && box->front.s[2][1] == 'g')
				|| (box->left.s[2][3] == 'b' && box->front.s[2][1] == 'r')
				|| (box->left.s[2][3] == 'b' && box->front.s[2][1] == 'o')
				|| (box->left.s[2][3] == 'o' && box->front.s[2][1] == 'g')
				|| (box->left.s[2][3] == 'o' && box->front.s[2][1] == 'b')
				|| (box->left.s[2][3] == 'g' && box->front.s[2][1] == 'r'))
			{
				U(box);
				F(box);
				CU(box);
				CF(box);
				CU(box);
				CL(box);
				U(box);
				L(box);
			}
			if ((box->back.s[2][3] == 'g' && box->right.s[2][3] == 'o')
				|| (box->back.s[2][3] == 'r' && box->right.s[2][3] == 'b')
				|| (box->back.s[2][3] == 'r' && box->right.s[2][3] == 'g')
				|| (box->back.s[2][3] == 'b' && box->right.s[2][3] == 'r')
				|| (box->back.s[2][3] == 'b' && box->right.s[2][3] == 'o')
				|| (box->back.s[2][3] == 'o' && box->right.s[2][3] == 'g')
				|| (box->back.s[2][3] == 'o' && box->right.s[2][3] == 'b')
				|| (box->back.s[2][3] == 'g' && box->right.s[2][3] == 'r'))
			{
				U(box);
				B(box);
				CU(box);
				CB(box);
				CU(box);
				CR(box);
				U(box);
				R(box);
			}
			if ((box->back.s[2][1] == 'g' && box->left.s[2][1] == 'o')
				|| (box->back.s[2][1] == 'r' && box->left.s[2][1] == 'b')
				|| (box->back.s[2][1] == 'r' && box->left.s[2][1] == 'g')
				|| (box->back.s[2][1] == 'b' && box->left.s[2][1] == 'r')
				|| (box->back.s[2][1] == 'b' && box->left.s[2][1] == 'o')
				|| (box->back.s[2][1] == 'o' && box->left.s[2][1] == 'g')
				|| (box->back.s[2][1] == 'o' && box->left.s[2][1] == 'b')
				|| (box->back.s[2][1] == 'g' && box->left.s[2][1] == 'r'))
			{
				U(box);
				L(box);
				CU(box);
				CL(box);
				CU(box);
				CB(box);
				U(box);
				B(box);
			}

		}
	}

}


/**
 * @brief  ����ʮ��
 * @param box
*/
void UpCross(Cube* box) {
	while (!(box->up.s[1][2] == 'y' && box->up.s[2][1] == 'y'
		&& box->up.s[2][3] == 'y' && box->up.s[3][2] == 'y'))
	{
		if (box->up.s[1][2] != 'y' && box->up.s[2][1] != 'y' && box->up.s[2][3] != 'y' && box->up.s[3][2] != 'y' && box->front.s[1][2] == 'y' && box->right.s[1][2] == 'y')
		{
			F(box);
			R(box);
			U(box);
			CR(box);
			CU(box);
			CF(box);

			F(box);
			R(box);
			U(box);
			CR(box);
			CU(box);
			CF(box);
		}
		if (box->up.s[1][2] == 'y' && box->up.s[2][1] == 'y' && box->front.s[1][2] == 'y' && box->right.s[1][2] == 'y')
		{
			F(box);
			R(box);
			U(box);
			CR(box);
			CU(box);
			CF(box);

			F(box);
			R(box);
			U(box);
			CR(box);
			CU(box);
			CF(box);
		}
		if (box->up.s[2][1] == 'y' && box->up.s[2][3] == 'y' && box->front.s[1][2] == 'y')
		{
			F(box);
			R(box);
			U(box);
			CR(box);
			CU(box);
			CF(box);

		}
		if (box->up.s[1][2] == 'y' && box->up.s[3][2] == 'y' && box->right.s[1][2] == 'y')
		{
			U(box);
		}
		if (box->up.s[1][2] == 'y' && box->up.s[3][2] == 'y' && box->left.s[1][2] == 'y')
		{
			CU(box);
		}
		if (box->up.s[2][1] == 'y' && box->up.s[3][2] == 'y' && box->back.s[3][2] == 'y' && box->right.s[1][2] == 'y')
		{
			U(box);
		}
		if (box->up.s[2][3] == 'y' && box->up.s[3][2] == 'y' && box->back.s[3][2] == 'y' && box->left.s[1][2] == 'y')
		{
			U(box);
			U(box);

		}
		if (box->up.s[2][3] == 'y' && box->up.s[1][2] == 'y' && box->left.s[1][2] == 'y')
		{
			CU(box);
		}
		if (box->up.s[2][3] == 'y' && box->up.s[1][2] == 'y' && box->right.s[1][2] == 'y')
		{
			U(box);
		}

	}

}

/**
 * @brief ������λ
 * @param box
*/
void UpSurfaceCornerRestore(Cube* box) {

	while (!(box->up.s[1][1] == 'y' && box->up.s[1][3] == 'y'
		&& box->up.s[3][1] == 'y' && box->up.s[3][3] == 'y'))
	{
		if (box->up.s[3][1] == 'y' || box->right.s[1][3] == 'y' || box->front.s[1][1] == 'y') {
			R(box);
			U(box);
			CR(box);
			U(box);
			R(box);
			U(box);
			U(box);
			CR(box);
		}
		if (box->up.s[3][3] == 'y' || box->right.s[1][1] == 'y' || box->front.s[1][3] == 'y') {
			U(box);
		}
		if (box->up.s[1][3] == 'y' || box->left.s[1][3] == 'y' || box->back.s[3][3] == 'y') {
			U(box);
			U(box);

		}
		if (box->up.s[1][1] == 'y' || box->left.s[1][1] == 'y' || box->front.s[3][1] == 'y') {
			CU(box);
		}


	}

}
/**
 * @brief ���ǻ�ԭ
 * @param box
*/
void UpCornerRestore(Cube* box) {

	while (!((box->front.s[1][1] == 'b' && box->front.s[1][3] == 'b')
		&& (box->left.s[1][1] == 'o' && box->left.s[1][3] == 'o')
		&& (box->back.s[1][1] == 'g' && box->back.s[1][3] == 'g')
		&& (box->right.s[1][1] == 'r' && box->right.s[1][3] == 'r')))
	{
		if (box->right.s[1][1] == box->right.s[1][3]) {
			U(box);
			R(box);
			CB(box);
			R(box);
			F(box);
			F(box);
			CR(box);
			B(box);
			R(box);
			F(box);
			F(box);
			R(box);
			R(box);

		}
		if (box->left.s[1][1] == box->left.s[1][3]) {
			CU(box);
			R(box);
			CB(box);
			R(box);
			F(box);
			F(box);
			CR(box);
			B(box);
			R(box);
			F(box);
			F(box);
			R(box);
			R(box);

		}
		if (box->back.s[3][1] == box->back.s[3][3]) {
			U(box);
			U(box);
			R(box);
			CB(box);
			R(box);
			F(box);
			F(box);
			CR(box);
			B(box);
			R(box);
			F(box);
			F(box);
			R(box);
			R(box);

		}
		R(box);
		CB(box);
		R(box);
		F(box);
		F(box);
		CR(box);
		B(box);
		R(box);
		F(box);
		F(box);
		R(box);
		R(box);


	}

}





/**
 * @brief  ���⻹ԭ
 * @param box
*/
void UpEdgeRestore(Cube* box) {

	while (!(box->front.s[1][2] == 'b' && box->left.s[1][2] == 'o'
		&& box->back.s[1][2] == 'g' && box->right.s[1][2] == 'r'))
	{
		if (box->front.s[1][2] == 'b') {
			L(box);
			CU(box);
			L(box);
			U(box);
			L(box);
			U(box);
			L(box);
			CU(box);
			CL(box);
			CU(box);
			L(box);
			L(box);
		}
		else if (box->left.s[1][2] == 'o') {
			F(box);
			CU(box);
			F(box);
			U(box);
			F(box);
			U(box);
			F(box);
			CU(box);
			CR(box);
			CU(box);
			F(box);
			F(box);
		}
		else if (box->back.s[1][2] == 'g') {
			R(box);
			CU(box);
			R(box);
			U(box);
			R(box);
			U(box);
			R(box);
			CU(box);
			CR(box);
			CU(box);
			R(box);
			R(box);

		}
		else if (box->right.s[1][2] == 'r') {
			B(box);
			CU(box);
			B(box);
			U(box);
			B(box);
			U(box);
			B(box);
			CU(box);
			CB(box);
			CU(box);
			B(box);
			B(box);
		}
		else {
			R(box);
			CU(box);
			R(box);
			U(box);
			R(box);
			U(box);
			R(box);
			CU(box);
			CR(box);
			CU(box);
			R(box);
			R(box);
		}

	}

}

int main(void) {
	double start, finish;
	start = clock();
	Cube box;
	InitCube(&box);
	printf("\n -----------------------��ʼ��ħ��------------------------\n");
	PrintCube(&box);
	printf("\n -----------------------����ħ��------------------------\n");
	RdCune(&box);
	PrintCube(&box);
	printf("\n -----------------------��ԭ��ħ��------------------------\n");
	SubfaceCross(&box);
	printf("1�ײ�ʮ�����\n");
	SubfaxeCornerRestore(&box);
	printf("2�ײ��ǿ黹ԭ���\n");
	CentreEdgeRestore(&box);
	printf("3�����λ���\n");
	UpCross(&box);
	printf("4����ʮ�����\n");
	UpSurfaceCornerRestore(&box);
	printf("5.������λ���\n");
	UpCornerRestore(&box);
	printf("6.���ǻ�ԭ\n");
	UpEdgeRestore(&box);
	printf("7.���⻹ԭ\n");
	finish = clock();
	PrintCube(&box);

	printf("�����ʱ��  %f ms", (finish - start));
	return 0;

}