/*
 * ��8puzzle
 *
 * [how to compile]
 *  >cl /nologo /W3 /O2 8puzzle.c
 */
#include <stdio.h>
#include <stdlib.h>

/* ��X�}�C�s�������� */
#define POS(x,y) ((x) + (y)*3)

/* �}�l�L�� */
int start_board[9] = {
	4,1,3,
	7,2,6,
	0,5,8
};

/* �����L�� */
int goal_board[9] = {
	1,2,3,
	4,5,6,
	7,8,0
};


/* hash table�޲z���c */
#define HASH_SIZE 8192   /* hash size */
typedef struct hash {
	int board[9];   /* �L�� */
	int step;       /* �B�� */
	struct hash *next;  /* �U�@�Ӫ��L�� */
	struct hash *prev_board;  /* �W�@�B���L�� */
} hash_t;

hash_t *hash[HASH_SIZE];  /* hash table(chain�k) */


/* �^���L���A�ñq�Ĥ@�B�C�X�L�� */
void display_board(int *board)
{
	printf("�z�w�s�w�s�w�{\n"
		   "�x%2d�x%2d�x%2d�x\n"
		   "�u�w�q�w�q�w�t\n"
		   "�x%2d�x%2d�x%2d�x\n"
		   "�u�w�q�w�q�w�t\n"
		   "�x%2d�x%2d�x%2d�x\n"
		   "�|�w�r�w�r�w�}\n",
		   board[0], board[1], board[2],
		   board[3], board[4], board[5],
		   board[6], board[7], board[8]);
}


void sub_show(hash_t *hash)
{
	hash_t *prev = hash->prev_board;

	if (prev == NULL)
		return;

	sub_show(prev);
	display_board(prev->board);
}

/* �^���L���A�ñq�Ĥ@�B�C�X�L�� */
void show_answer(hash_t *hash)
{
	sub_show(hash);

	display_board(hash->board);
}


/* hash table����l�� */
void init_hash(void)
{
	int i;

	for (i = 0 ; i < HASH_SIZE ; i++) {
		hash[i] = NULL;
	}
}

/* �p��hash index */
int get_hash_index(int *board)
{
	int i, val;
	int offset[] = {40320, 5040, 720, 120, 24, 6, 2, 1};  /* 8! 7! 6! 5! 4! 3! 2! 1! */

	val = 0;
	for (i = 0 ; i < 9 ; i++) {
		val += (board[i] * offset[i]);
	}
	val &= (HASH_SIZE - 1);
	return (val);
}

/* �N�L��(board)�n����hash table�A�õn������step�B�C
 * prev�O���W�@�B���L���C
 */
hash_t *hash_board(int *board, int step, hash_t *prev)
{
	int i, key;
	hash_t *ptr;

	ptr = malloc(sizeof(hash_t));
	if (ptr == NULL)
		exit(1);
	for (i = 0 ; i < 9 ; i++) {
		ptr->board[i] = board[i];
	}
	ptr->next = NULL;
	ptr->prev_board = prev;
	ptr->step = step;

	key = get_hash_index(board);
	ptr->next = hash[key];
	hash[key] = ptr;

	return (ptr);
}

/* �qhash table��X�L�� */
hash_t *find_board_from_hash(int *board)
{
	int key, i;
	hash_t *ptr;

	key = get_hash_index(board);
	for (ptr = hash[key]; ptr ; ptr = ptr->next) {
		for (i = 0 ; i < 9 ; i++) 
			if (board[i] != ptr->board[i])
				break;
		if (i == 9)
			return (ptr);
	}
	return (NULL);
}

#if 0
void hash_display(void)
{
	int i, c;
	hash_t *ptr;

	for (i = 0 ; i < HASH_SIZE ; i++) {
		c = 0;
		for (ptr = hash[i]; ptr ; ptr = ptr->next) {
			if (c == 0)
				printf("%d ", i);
			c++;
			printf("*--");
#if 0
			printf("�� %d �B\n", ptr->step);
			for (n = 0 ; n < 9 ; n++) {
				if (n && n % 3 == 0)
					printf("\n");
				printf("%d ", ptr->board[n]);
			}
			printf("\n");
#endif
		}

		if (c)
			printf("\n");
	}

}
#endif


/* �����k(dir)�N�L��(org_board)�W���Ʀr������
 * �Y���ʦ��\���ܡA�h�s���s�L��(new_board)�C
 */
int move_board(int dir, int *org_board, int *new_board)
{
	int i, found, zx, zy, t;

	found = 0;
	for (i = 0 ; i < 9 ; i++) {
		new_board[i] = org_board[i];
		if (org_board[i] == 0) {
			found = 1;
			t = i;
		}
	}
	if (found == 0) {
		printf("�䤣��Ů�");
		exit(1);
	}
	zx = t % 3;   /* 0~2 */
	zy = t / 3;   /* 0~2 */
	//printf("(%d,%d)\n", zx, zy);

	switch (dir) {
	case 0:  /* ���k���� (s/(\d)0/0$1/)*/
		if (zx >= 1) {
			/* (zx-1,zy)<->(zx,zy) */
			new_board[POS(zx,zy)] = new_board[POS(zx-1,zy)];
			new_board[POS(zx-1,zy)] = 0;
			return 1;
		}
		break;

	case 1: /* �������� (s/0(\d)/${1}0/)*/
		if (zx <= 1) {
			/* (zx,zy)<->(zx+1,zy) */
			new_board[POS(zx,zy)] = new_board[POS(zx+1,zy)];
			new_board[POS(zx+1,zy)] = 0;
			return 1;
		}
		break;

	case 2:  /* ���U���� (s/(.)(.)(.)(.)0/0$2$3$4$1/)*/
		if (zy >= 1) {
			/* (zx,zy)<->(zx,zy-1) */
			new_board[POS(zx,zy)] = new_board[POS(zx,zy-1)];
			new_board[POS(zx,zy-1)] = 0;
			return 1;
		}
		break;

	case 3:  // ���W���� (s/0(.)(.)(.)(.)/$4$1$2${3}0/)
	default:
		if (zy <= 1) {
			/* (zx,zy)<->(zx,zy+1) */
			new_board[POS(zx,zy)] = new_board[POS(zx,zy+1)];
			new_board[POS(zx,zy+1)] = 0;
			return 1;
		}
		break;
	}

	return 0;  /* ���ʥ��� */
}

/* �e���u���j�M */
void sub(void)
{
	int i, j, k, step;
	int new_board[9];
	hash_t *ptr, *newhash;

	/* �q��1�B�̧ǼW�[�B�� */
	for (step = 1 ; step < 100 ; step++) {
		//printf("searching.. %d step\n", step);

		/* ���X��(step-1)�B���L�� */
		for (i = 0 ; i < HASH_SIZE ; i++) {
			for (ptr = hash[i]; ptr ; ptr = ptr->next) {
				if (ptr->step != step - 1)
					continue;

				//display_board(ptr->board);

				/* ���|�Ӥ�V���ʼƦr�ݬ� */
				for (j = 0 ; j < 4 ; j++) {
					if (move_board(j, ptr->board, new_board)) { /* ���ʦ��\ */
						if (find_board_from_hash(new_board) == NULL) { /* �Y�O�s�L������ */ 
							newhash = hash_board(new_board, step, ptr);
							//display_board(new_board);

							for (k = 0 ; k < 9 ; k++) {
								if (new_board[k] != goal_board[k])
									break;
							}
							if (k == 9) {
								printf("�b�� %d �B���ѵ�\n", step);
								show_answer(newhash);
								return;
							}
						}
					}
				}

			}
		}
	}
}

/* �D��� */
int main(void)
{
	init_hash();
	/* �N�}�l�L���n������0�B */
	hash_board(start_board, 0, NULL);

	sub();

	return 0;
}

