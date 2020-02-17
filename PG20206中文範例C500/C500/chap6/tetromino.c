/*
 * tetromino.c - 「四方塊的魔術方塊」
 *
 * [how to compile]
 * >cl /O2 /nologo /W3 tetromino.c && tetromino
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

 /* 在5×8的盤面上放置各種零件(各兩個)。
 * 在右邊和下面做出牆壁
    □□□□□■
    □□□□□■
    □□□□□■
    □□□□□■
    □□□□□■
    □□□□□■
    □□□□□■

    □□□□□■
    ■■■■■■
 */
#define WIDTH (5+1)        /* 盤面的橫向寬度+牆壁 */
#define HEIGHT (8+1)       /* 盤面的縱向高度+牆壁 */
#define POS(x,y) ((x) + (y)*WIDTH)
#define WALL -1

#define BITS_PIECES 4   /* 零件的組成要素數 */
#define PIECES 5       /* 零件的種類 */

char pieces[PIECES][4*4] = {
	{  /* I型方塊 */
	"*---"
	"*---"
	"*---"
	"*---"
	},
	{  /* L型方塊 */
	"----"
	"*---"
	"*---"
	"**--"
	},
	{  /* O型方塊 */
	"----"
	"----"
	"**--"
	"**--"
	},
	{  /* T型方塊 */
	"----"
	"----"
	"***-"
	"-*--"
	},
	{  /* Z型方塊 */
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
point_t Point[PIECES][BITS_PIECES]; /* 用XY座標值表示的零件資料 */

typedef struct {
	int shape[8][BITS_PIECES];
	int n_shape;
}shape_t;
shape_t Shape[PIECES];    /* 由偏移量來表示的零件資料(最多8種) */


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

/* 搜尋處理 */
void sub(int site)
{
	int recsite[BITS_PIECES];
	int i, j, k, tmp;
	
	if (put_count == PIECES*2) {  /* 解 */
		ans_cnt++;
		//display_board(board);
		return;
	}

	/* 嘗試site位置是否可以放置 */
	for (k = 0 ; k < PIECES ; k++) {
		if (count_pieces[k] == 0)
			continue;

		count_pieces[k]--;

		for (i = 0; i < Shape[k].n_shape ; i++) {  /* 零件的類型 */
			for (j = 0 ; j < BITS_PIECES ; j++) {
				recsite[j] = site + Shape[k].shape[i][j];
				if (board[recsite[j]])  /* 空格已被使用 */
					break;
			}
			if (j != BITS_PIECES) 
				continue;
			
			/* 放置零件 */
			put_count++;
			for (j = 0 ; j < BITS_PIECES ; j++) {
				board[recsite[j]] = face_pieces[k];
			}
			tmp = site;
			while (board[++tmp] != 0)  /* 找空格 */
				;

			sub( tmp );  /* 到下一個搜尋步驟 */

			/* 把零件拿起來 */
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
	board[POS(WIDTH-1,HEIGHT-1)] = 0;  /* 衛兵 */
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

/* 左右翻轉 */
void reverse(point_t *p)
{
	int i;

	for (i = 0 ; i < BITS_PIECES ; i++) {
		p[i].x = -p[i].x;
	}
}

/* 旋轉90° */
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

/* 遞增排序 */
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

/* 將持有XY座標的資料，轉換成一維陣列用的編號 */
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
	for (i = 0 ; i < n ; i++) {   /* 檢查是否已有同型者 */
		for (j = 0 ; j < BITS_PIECES ; j++)
			if (shape->shape[n][j] != shape->shape[i][j])
				break;
		if (j == BITS_PIECES) 
			return;
	}
	shape->n_shape++;
}

/* 從四方塊點陣圖取得零件資訊 */
void init(void)
{
	int x, y, n, i, k;

	for (k = 0 ; k < PIECES ; k++) {
		/* 從點陣圖取得XY座標值 */
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

		/* 從XY座標值轉換成8種類型的相對位置 */
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

	printf("共 %d 種解\n", ans_cnt);

	return 0;
}


