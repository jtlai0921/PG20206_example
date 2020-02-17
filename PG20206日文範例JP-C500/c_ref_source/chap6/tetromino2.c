/*
 * tetromino2.c - �u�e�g���~�m�̔��l�߁v����]������������
 *
 * [how to compile]
 * >cl /O2 /nologo /W3 tetromino2.c && tetromino2
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 5�~8�̔ՖʂɌ��ԂȂ��e��s�[�X(2����)��~���l�߂�B
 * �E�ӂƉ��ӂɕǂ�u���B
 
   ������������
   ������������
   ������������
   ������������
   ������������
   ������������
   ������������
   ������������
   ������������
 */
#define WIDTH (5+1)        /* �Ֆʂ̉��T�C�Y�{�� */
#define HEIGHT (8+1)       /* �Ֆʂ̏c�T�C�Y�{�� */
#define POS(x,y) ((x) + (y)*WIDTH)
#define WALL -1

#define BITS_PIECES 4   /* �s�[�X�̍\���v�f�� */
#define PIECES 5       /* �s�[�X�̎�� */

char pieces[PIECES][4*4] = {
	{  /* I�e�g���~�m */
	"*---"
	"*---"
	"*---"
	"*---"
	},
	{  /* L�e�g���~�m */
	"----"
	"*---"
	"*---"
	"**--"
	},
	{  /* O�e�g���~�m */
	"----"
	"----"
	"**--"
	"**--"
	},
	{  /* T�e�g���~�m */
	"----"
	"----"
	"***-"
	"-*--"
	},
	{  /* Z�e�g���~�m */
	"----"
	"----"
	"**--"
	"-**-"
	},
};

int count_pieces[PIECES] = { 2, 2, 2, 2, 2 };
char face_pieces[PIECES] = { 'I', 'L', 'O', 'T', 'Z' };


typedef struct {
	int x;
	int y;
}point_t;
point_t Point[PIECES][BITS_PIECES]; /* XY���W�l�ɂ��s�[�X�f�[�^ */

typedef struct {
	int shape[8][BITS_PIECES];
	int n_shape;
}shape_t;
shape_t Shape[PIECES];    /* �I�t�Z�b�g�l�ɂ��s�[�X�f�[�^(�ő�8�p�^�[��) */


int board[WIDTH*HEIGHT];
int put_count = 0;
int ans_cnt = 0;
int ans_board[4000][WIDTH*HEIGHT];


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

/* �Ղ����E���Ԃ� */
void reverse_board(int board[])
{
	int x, y, tmp;
	
	for (y = 0 ; y < HEIGHT-1 ; y++) {
		for (x = 0 ; x < WIDTH/2 ; x++) {
			tmp = board[POS(x,y)];
			board[POS(x,y)] = board[POS(WIDTH-2-x,y)];
			board[POS(WIDTH-2-x,y)] = tmp;
		}
	}
}

/* �Ղ�180����] */
void rotate_board(int board[])
{
	static int tmp[WIDTH*HEIGHT];
	int x, y;
	
	for (y = 0 ; y < HEIGHT-1 ; y++) {
		for (x = 0 ; x < WIDTH-1 ; x++) {
			tmp[POS(WIDTH-2-x, HEIGHT-2-y)] = board[POS(x,y)];
		}
	}
	for (y = 0 ; y < HEIGHT-1 ; y++) {
		for (x = 0 ; x < WIDTH-1 ; x++) {
			board[POS(x,y)] = tmp[POS(x,y)];
		}
	}
}

/* ���`�`�F�b�N */
int is_same(int a_board[], int b_board[])
{
	int x, y;
	
	/* �ǂ͎�菜���Ĕ�r���� */
	for (y = 0 ; y < HEIGHT-1 ; y++) {
		for (x = 0 ; x < WIDTH-1 ; x++) {
			if (a_board[POS(x,y)] != b_board[POS(x,y)]) {
				return 0;  /* �ٌ` */
			}
		}
	}
	return 1;  /* ���� */
}

/* ��]�������̃`�F�b�N */
void check(void)
{
	int i, j;
	int k, tmp[WIDTH*HEIGHT];
	
	for (i = 0 ; i < ans_cnt ; i++) {
		for (k = 0; k < WIDTH*HEIGHT ; k++) {
			tmp[k] = ans_board[i][k];
		}

		for (j = 0 ; j < 2 ; j++) {
			if (is_same(ans_board[i], board))
				goto skip;
			rotate_board(ans_board[i]);
		}
		reverse_board(ans_board[i]);
		for (j = 0 ; j < 2 ; j++) {
			if (is_same(ans_board[i], board))
				goto skip;
			rotate_board(ans_board[i]);
		}
	}

skip:;
	if (i == ans_cnt) {  /* ���Ƃ��ċL�^ */
		assert(ans_cnt < 4000);
		for (j = 0 ; j < WIDTH*HEIGHT ; j++) {
			ans_board[ans_cnt][j] = board[j];
		}
		//display_board(ans_board[ans_cnt]);

		ans_cnt++;

	} else {
#if 0
		display_board(tmp);
		display_board(board);
		printf("����\n"); exit(1);
#endif
	}

}

/* �T������ */
void sub(int site)
{
	int recsite[BITS_PIECES];
	int i, j, k, tmp;
	
	if (put_count == PIECES*2) {  /* �� */
		check();
		return;
	}

	/* site�ʒu�ɒu���邩������ */
	for (k = 0 ; k < PIECES ; k++) {
		if (count_pieces[k] == 0)
			continue;

		count_pieces[k]--;

		for (i = 0; i < Shape[k].n_shape ; i++) {  /* �s�[�X�̃p�^�[�� */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				recsite[j] = site + Shape[k].shape[i][j];
				if (board[recsite[j]])  /* ���炩�̃s�[�X������ */
					break;
			}
			if (j != BITS_PIECES) 
				continue;
			
			/* �s�[�X��u�� */
			put_count++;
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = face_pieces[k];
			}
			tmp = site;
			while (board[++tmp] != 0)  /* �󂫂�T�� */
				;

			sub( tmp );  /* ���̒T���� */

			/* �s�[�X����� */
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
	board[POS(WIDTH-1,HEIGHT-1)] = 0;  /* �ԕ� */
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

/* ���E���] */
void reverse(point_t *p)
{
	int i;

	for (i = 0 ; i < BITS_PIECES ; i++) {
		p[i].x = -p[i].x;
	}
}

/* 90�x��] */
void rotate(point_t *p)
{
	int i, t;

	/*
	 * x' = cos��x - sin��y
	 * y' = sin��x + cos��y
	 * (��=90��)
	 */
	for (i = 0 ; i < BITS_PIECES ; i++) {
		t = p[i].x;
		p[i].x = -p[i].y;
		p[i].y = t;
	}
}

/* �����Ƀ\�[�g */
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

/* XY���W�����f�[�^���P�����z��Y�����p�ɕϊ� */
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
	for (i = 0 ; i < n ; i++) {   /* ���`�`�F�b�N */
		for (j = 0 ; j < BITS_PIECES ; j++)
			if (shape->shape[n][j] != shape->shape[i][j])
				break;
		if (j == BITS_PIECES) 
			return;
	}
	shape->n_shape++;
}

/* �e�g���~�m�r�b�g�}�b�v����s�[�X�����̎悷�� */
void init(void)
{
	int x, y, n, i, k;

	for (k = 0 ; k < PIECES ; k++) {
		/* �r�b�g�}�b�v����XY���W�l�𓾂� */
		n = 0;
		for (y = 0 ; y < 4 ; y++) {
			for (x = 0 ; x < 4 ; x++) {
				if (pieces[k][x + y*4] == '*') {
					assert(n < BITS_PIECES);
					Point[k][n].x = x;
					Point[k][n].y = y;
					n++;
				}
			}
		}

		/* XY���W�l����8�p�^�[�����̑��Έʒu�֕ϊ� */
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

	printf("�� %d �Ƃ���\n", ans_cnt);

	return 0;
}


