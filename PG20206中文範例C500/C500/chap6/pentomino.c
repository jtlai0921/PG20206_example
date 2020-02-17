/*
 * pentomino.c - �u��������]�N����v
 *
 * [how to compile]
 * >cl /O2 /nologo /W3 pentomino.c && pentomino
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* �b6��10���L���W��m�U�عs��(�U�@��)�C
 * �b�k��M�U�����X���
 
	��������������
	��������������
	��������������
	��������������
	��������������
	��������������
	��������������
	��������������
	��������������
	��������������
	��������������
 */
#define WIDTH (6+1)        /* �L������V�e��+��� */
#define HEIGHT (10+1)      /* �L�����a�V����+��� */
#define POS(x,y) ((x) + (y)*WIDTH)
#define WALL -1

#define BITS_PIECES 5   /* �s�󪺲զ��n���� */
#define PIECES 12       /* �s�󪺺��� */

char pieces[PIECES][5*5] = {
	{  /* I����� */
	"*----"
	"*----"
	"*----"
	"*----"
	"*----"
	},
	{  /* Y����� */
	"*----"
	"**---"
	"*----"
	"*----"
	"-----"
	},
	{  /* P����� */
	"**---"
	"**---"
	"*----"
	"-----"
	"-----"
	},
	{  /* V����� */
	"*----"
	"*----"
	"***--"
	"-----"
	"-----"
	},
	{  /* W����� */
	"*----"
	"**---"
	"-**--"
	"-----"
	"-----"
	},
	{  /* L����� */
	"**---"
	"*----"
	"*----"
	"*----"
	"-----"
	},
	{  /* U����� */
	"**---"
	"*----"
	"**---"
	"-----"
	"-----"
	},
	{  /* N����� */
	"*----"
	"*----"
	"**---"
	"-*---"
	"-----"
	},
	{  /* F����� */
	"-*---"
	"-**--"
	"**---"
	"-----"
	"-----"
	},
	{  /* X����� */
	"-*---"
	"***--"
	"-*---"
	"-----"
	"-----"
	},
	{  /* T����� */
	"*----"
	"***--"
	"*----"
	"-----"
	"-----"
	},
	{  /* Z����� */
	"**---"
	"-*---"
	"-**--"
	"-----"
	"-----"
	},
};

int count_pieces[PIECES] = { 
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1,
	1, 1,
};
char face_pieces[PIECES] = { 'I', 'Y', 'P', 'V', 'W', 'L', 'U', 'N', 'F', 'X', 'T', 'Z' };

typedef struct {
	int x;
	int y;
}point_t;
point_t Point[PIECES][BITS_PIECES]; /* ��XY�y�ЭȪ�ܪ��s���� */

typedef struct {
	int shape[8][BITS_PIECES];
	int n_shape;
}shape_t;
shape_t Shape[PIECES];    /* �Ѱ����q�Ӫ�ܪ��s����(�̦h8��) */


int board[WIDTH*HEIGHT];
int put_count = 0;
int ans_cnt = 0;


void display_board(int *board)
{
	int x, y;
	char c;

	for (y = 0 ; y < HEIGHT-1 ; y++) {
		for (x = 0 ; x < WIDTH-1 ; x++) {
			c = board[POS(x,y)];
			printf("%c", c);
		}
		printf("\n");
	}
	printf("\n");
}

/* �j�M�B�z */
void sub(int site)
{
	int recsite[BITS_PIECES];
	int i, j, k, tmp;
	
	if (put_count == PIECES) {  /* �� */
		ans_cnt++;
		//display_board(board);
		return;
	}

	/* ����site��m�O�_�i�H��m */
	for (k = 0 ; k < PIECES ; k++) {
		if (count_pieces[k] == 0)
			continue;

		count_pieces[k]--;

		for (i = 0; i < Shape[k].n_shape ; i++) {  /* �s������ */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				recsite[j] = site + Shape[k].shape[i][j];
				if (board[recsite[j]])  /* �Ů�w�Q�ϥ� */
					break;
			}
			if (j != BITS_PIECES) 
				continue;
			
			/* ��m�s�� */
			put_count++;
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = face_pieces[k];
			}
			tmp = site;
			while (board[++tmp] != 0)  /* ��Ů� */
				;

			sub( tmp );  /* ��U�@�ӷj�M�B�J */

			/* ��s�󮳰_�� */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = 0;
			}
			put_count--;
		}

		count_pieces[k]++;
	}
}

void init_board(void)
{
	int x, y;
	
	for (y = 0 ; y < HEIGHT ; y++) {
		for (x = 0 ; x < WIDTH ; x++) {
			if (x == WIDTH - 1 || y == HEIGHT - 1) 
				board[POS(x,y)] = WALL;
			else
				board[POS(x,y)] = 0;
		}
	}
	board[POS(WIDTH-1,HEIGHT-1)] = 0;  /* �çL */
}

void shape_disp(shape_t s)
{
	int i, j;
	
	printf("%d pattern(s)\n", s.n_shape);
	for (i = 0 ; i < s.n_shape; i++) {
		for (j = 0 ; j < BITS_PIECES ; j++) 
			printf("%2d, ", s.shape[i][j]);
		printf("\n");
	}
}

/* ���k½�� */
void reverse(point_t *p)
{
	int i;

	for (i = 0 ; i < BITS_PIECES ; i++) {
		p[i].x = -p[i].x;
	}
}

/* ����90�X */
void rotate(point_t *p)
{
	int i, t;

	/*
	 * x' = cos��x - sin��y
	 * y' = sin��x + cos��y
	 * (��=90?)
	 */
	for (i = 0 ; i < BITS_PIECES ; i++) {
		t = p[i].x;
		p[i].x = -p[i].y;
		p[i].y = t;
	}
}

/* ���W�Ƨ� */
void sort(int s[], int n)
{
	int i, j;
	int a;
	
	for (i = 0 ; i < n ; i++) {
		for (j = n - 1 ; j > i ; j--) {
			if (s[j] < s[j-1]) {
				a = s[j];
				s[j] = s[j-1];
				s[j-1] = a;
			}
        }
    }
}

/* �N����XY�y�Ъ���ơA�ഫ���@���}�C�Ϊ��s�� */
void convert_shape_to_index(shape_t *shape, point_t *point)
{
	int i, j, n;
	int tmp[BITS_PIECES];
	
	n = shape->n_shape;
	for (i = 0 ; i < BITS_PIECES ; i++) {
		tmp[i] = POS(point[i].x, point[i].y);
    }
    
    sort(tmp, BITS_PIECES);
    
	for (i = 0 ; i < BITS_PIECES ; i++) {
		shape->shape[n][i] = tmp[i] - tmp[0];
	}
	for (i = 0 ; i < n ; i++) {   /* �ˬd�O�_�w���P���� */
		for (j = 0 ; j < BITS_PIECES ; j++)
			if (shape->shape[n][j] != shape->shape[i][j])
				break;
		if (j == BITS_PIECES) 
			return;
	}
	shape->n_shape++;
}

/* �q������I�}�Ϩ��o�s���T */
void init(void)
{
	int x, y, n, i, k;

	for (k = 0 ; k < PIECES ; k++) {
		/* �q�I�}�Ϩ��oXY�y�Э� */
		n = 0;
		for (y = 0 ; y < 5 ; y++) {
			for (x = 0 ; x < 5 ; x++) {
				if (pieces[k][x + y*5] == '*') {
					assert(n < BITS_PIECES);
					Point[k][n].x = x;
					Point[k][n].y = y;
					n++;
				}
			}
		}

		/* �qXY�y�Э��ഫ��8���������۹��m */
		Shape[k].n_shape = 0;
		for (i = 0 ; i < 4; i++) {
			convert_shape_to_index(&Shape[k] ,Point[k]);
			rotate(Point[k]);
		}
		reverse(Point[k]);
		for (i = 0 ; i < 4; i++) {
			convert_shape_to_index(&Shape[k] ,Point[k]);
			rotate(Point[k]);
		}
		//shape_disp(Shape[k]);
	}
}


int main(void)
{
	init();
	init_board();
	sub(0);

	printf("�@ %d �ظ�\n", ans_cnt);

	return 0;
}


