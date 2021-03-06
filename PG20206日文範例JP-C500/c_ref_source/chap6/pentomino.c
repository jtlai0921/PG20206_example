/*
 * pentomino.c - 「ペントミノの箱詰め」
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

/* 6×10の盤面に隙間なく各種ピース(1個ずつ)を敷き詰める。
 * 右辺と下辺に壁を置く。
 
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   □□□□□□■
   ■■■■■■■
 */
#define WIDTH (6+1)        /* 盤面の横サイズ＋壁 */
#define HEIGHT (10+1)       /* 盤面の縦サイズ＋壁 */
#define POS(x,y) ((x) + (y)*WIDTH)
#define WALL -1

#define BITS_PIECES 5   /* ピースの構成要素数 */
#define PIECES 12       /* ピースの種類 */

char pieces[PIECES][5*5] = {
	{  /* Iペントミノ */
	"*----"
	"*----"
	"*----"
	"*----"
	"*----"
	},
	{  /* Yペントミノ */
	"*----"
	"**---"
	"*----"
	"*----"
	"-----"
	},
	{  /* Pペントミノ */
	"**---"
	"**---"
	"*----"
	"-----"
	"-----"
	},
	{  /* Vペントミノ */
	"*----"
	"*----"
	"***--"
	"-----"
	"-----"
	},
	{  /* Wペントミノ */
	"*----"
	"**---"
	"-**--"
	"-----"
	"-----"
	},
	{  /* Lペントミノ */
	"**---"
	"*----"
	"*----"
	"*----"
	"-----"
	},
	{  /* Uペントミノ */
	"**---"
	"*----"
	"**---"
	"-----"
	"-----"
	},
	{  /* Nペントミノ */
	"*----"
	"*----"
	"**---"
	"-*---"
	"-----"
	},
	{  /* Fペントミノ */
	"-*---"
	"-**--"
	"**---"
	"-----"
	"-----"
	},
	{  /* Xペントミノ */
	"-*---"
	"***--"
	"-*---"
	"-----"
	"-----"
	},
	{  /* Tペントミノ */
	"*----"
	"***--"
	"*----"
	"-----"
	"-----"
	},
	{  /* Zペントミノ */
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
point_t Point[PIECES][BITS_PIECES]; /* XY座標値によるピースデータ */

typedef struct {
	int shape[8][BITS_PIECES];
	int n_shape;
}shape_t;
shape_t Shape[PIECES];    /* オフセット値によるピースデータ(最大8パターン) */


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

/* 探索処理 */
void sub(int site)
{
	int recsite[BITS_PIECES];
	int i, j, k, tmp;
	
	if (put_count == PIECES) {  /* 解 */
		ans_cnt++;
		//display_board(board);
		return;
	}

	/* site位置に置けるかを試す */
	for (k = 0 ; k < PIECES ; k++) {
		if (count_pieces[k] == 0)
			continue;

		count_pieces[k]--;

		for (i = 0; i < Shape[k].n_shape ; i++) {  /* ピースのパターン */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				recsite[j] = site + Shape[k].shape[i][j];
				if (board[recsite[j]])  /* 何らかのピースがある */
					break;
			}
			if (j != BITS_PIECES) 
				continue;
			
			/* ピースを置く */
			put_count++;
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = face_pieces[k];
			}
			tmp = site;
			while (board[++tmp] != 0)  /* 空きを探す */
				;

			sub( tmp );  /* 次の探索へ */

			/* ピースを取る */
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
	board[POS(WIDTH-1,HEIGHT-1)] = 0;  /* 番兵 */
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

/* 左右反転 */
void reverse(point_t *p)
{
	int i;

	for (i = 0 ; i < BITS_PIECES ; i++) {
		p[i].x = -p[i].x;
	}
}

/* 90度回転 */
void rotate(point_t *p)
{
	int i, t;

	/*
	 * x' = cosθx - sinθy
	 * y' = sinθx + cosθy
	 * (θ=90°)
	 */
	for (i = 0 ; i < BITS_PIECES ; i++) {
		t = p[i].x;
		p[i].x = -p[i].y;
		p[i].y = t;
	}
}

/* 昇順にソート */
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

/* XY座標を持つデータを１次元配列添え字用に変換 */
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
	for (i = 0 ; i < n ; i++) {   /* 同形チェック */
		for (j = 0 ; j < BITS_PIECES ; j++)
			if (shape->shape[n][j] != shape->shape[i][j])
				break;
		if (j == BITS_PIECES) 
			return;
	}
	shape->n_shape++;
}

/* テトロミノビットマップからピース情報を採取する */
void init(void)
{
	int x, y, n, i, k;

	for (k = 0 ; k < PIECES ; k++) {
		/* ビットマップからXY座標値を得る */
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

		/* XY座標値から8パターン分の相対位置へ変換 */
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

	printf("解 %d とおり\n", ans_cnt);

	return 0;
}


