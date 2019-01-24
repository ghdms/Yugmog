// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI 코드 작성 방법]

1. char info[]의 배열 안에					"TeamName:자신의 팀명,Department:자신의 소속"					순서로 작성합니다.
( 주의 ) Teamname:과 Department:는 꼭 들어가야 합니다.
"자신의 팀명", "자신의 소속"을 수정해야 합니다.

2. 아래의 myturn() 함수 안에 자신만의 AI 코드를 작성합니다.

3. AI 파일을 테스트 하실 때는 "육목 알고리즘대회 툴"을 사용합니다.

4. 육목 알고리즘 대회 툴의 연습하기에서 바둑돌을 누른 후, 자신의 "팀명" 이 들어간 알고리즘을 추가하여 테스트 합니다.



[변수 및 함수]
myturn(int cnt) : 자신의 AI 코드를 작성하는 메인 함수 입니다.
int cnt (myturn()함수의 파라미터) : 돌을 몇 수 둬야하는지 정하는 변수, cnt가 1이면 육목 시작 시  한 번만  두는 상황(한 번), cnt가 2이면 그 이후 돌을 두는 상황(두 번)
int  x[0], y[0] : 자신이 둘 첫 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
int  x[1], y[1] : 자신이 둘 두 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
void domymove(int x[], int y[], cnt) : 둘 돌들의 좌표를 저장해서 출력


//int board[BOARD_SIZE][BOARD_SIZE]; 바둑판 현재상황 담고 있어 바로사용 가능함. 단, 원본데이터로 수정 절대금지
// 놓을수 없는 위치에 바둑돌을 놓으면 실격패 처리.

boolean ifFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int showBoard(int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:삼삼,Department:경희대학교" };

void myturn(int cnt) {

	int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.

	if (terminateAI) return;

	int d = 0;
	int dd = 0;
	int l = 0;
	int a = 0;
	int aa = 0;
	int as = 0;
	if (cnt == 1) first(x,y);
	else
	{
		d = defense(x, y, 0, 0);
		if (d == 0)
		{
			dd = defense(x, y, 0, 1);
			if (dd == 0)
			{
				as = allsearch(x, y, 0);
				if (as == 0)
				{
					l = last_defense(x, y);
					if (l == 0)
					{
						a = attack(x, y, 0, 0);
						if (a == 0)
						{
							aa = attack(x, y, 0, 1);
							if (aa == 0)
								example_random(x, y, 2);
							else if (aa == 1)
								example_random(x, y, 1);
						}
						else if (a == 1)
						{
							aa = attack(x, y, 1, 1);
							if (aa == 0)
								example_random(x, y, 1);
						}
					}
					else if (l == 1)
					{
						a = attack(x, y, 1, 0);
						if (a == 0)
						{
							aa = attack(x, y, 1, 1);
							if (aa == 0)
								example_random(x, y, 1);
						}
					}
				}
				else if (as == 1)
				{
					a = attack(x, y, 1, 0);
					if (a == 0)
					{
						aa = attack(x, y, 1, 1);
						if (aa == 0)
							example_random(x, y, 1);
					}
				}
			}
			else if (dd == 1)
			{
				as = allsearch(x, y, 1);
				if (as == 0)
				{
					a = attack(x, y, 1, 0);
					if (a == 0)
					{
						aa = attack(x, y, 1, 1);
						if (aa == 0)
							example_random(x, y, 1);
					}
				}
			}
		}
		else if (d == 1)
		{
			dd = defense(x, y, 1, 1);
			if (dd == 0)
			{
				as = allsearch(x, y, 1);
				if (as == 0)
				{
					a = attack(x, y, 1, 0);
					if (a == 0)
					{
						aa = attack(x, y, 1, 1);
						if (aa == 0)
							example_random(x, y, 1);
					}
				}
			}
		}
	}

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	domymove(x, y, cnt);
}

void example_random(int x[], int y[], int cnt)
{
	srand((unsigned)time(NULL));

	if (cnt == 2)
	{
		for (int i = 0; i < cnt; i++) {
			do {
				x[i] = rand() % width;
				y[i] = rand() % height;
			} while (!isFree(x[i], y[i]));

			if (x[1] == x[0] && y[1] == y[0]) i--;
		}
	}
	else
	{
		do {
			x[1] = rand() % width;
			y[1] = rand() % height;
		} while (!isFree(x[1], y[1]) || (x[1] == x[0] && y[1] == y[0]));
	}
}

void first(int x[], int y[])
{
	if (block_num > 0)
	{
		int optidx = 0;
		int opt = abs(9 - blockx[0]) + abs(9 - blocky[0]);
		for (int i = 1; i < block_num; i++)
		{
			if (opt > abs(9 - blockx[i]) + abs(9 - blocky[i]))
			{
				opt = abs(9 - blockx[i]) + abs(9 - blocky[i]);
				optidx = i;
			}
		}

		if (blockx[optidx] > 9)
		{
			x[0] = blockx[optidx] - 1;
			y[0] = blocky[optidx];
		}
		else
		{
			x[0] = blockx[optidx] + 1;
			y[0] = blocky[optidx];
		}
	}
	else
	{
		x[0] = 9;
		y[0] = 9;
	}
}

int next_de(int x[], int y[], int mode, int num, int my)
{
	if (mode == 1)
	{
		return defense_v(x, y, num, my);
	}
	else if (mode == 2)
	{
		return defense_nw(x, y, num, my);
	}
	else if (mode == 3)
	{
		return defense_ne(x, y, num, my);
	}
	else
	{
		return 0;
	}
}

int defended(bool lc, bool rc, int x[], int y[], int lempty, int rempty, int i, int j, int mode, int num, int ex, int ey, int opnum, int my)
{
	int eidx = lempty + rempty;

	if (opnum < 3)
	{
		return next_de(x, y, mode, num, my);
	}
	if (opnum == 3)
	{
		if (lc == false && rc == false)
		{
			return next_de(x, y, mode, num, my);
		}
		else if (lc == false)
		{
			for (int a = 2; a < 5; a++)
			{
				if (showBoard(ox[my] + a * i, oy[my] + a * j) == 1)
				{
					for (int b = 1; b < a; b++)
					{
						if (showBoard(ox[my] + b * i, oy[my] + b * j) == 2 || showBoard(ox[my] + b * i, oy[my] + b * j) == 3)
						{
							return next_de(x, y, mode, num, my);
						}
					}
					a = 6;
					break;
				}
			}
			if (showBoard(ox[my] - 5 * i, oy[my] - 5 * j) == 2 || showBoard(ox[my] - 5 * i, oy[my] - 5 * j) == 3)
			{
				if (num == 0)
				{
					x[0] = ex;
					y[0] = ey;
					return 1 + next_de(x, y, mode, 1, my);
				}
				else
				{
					if (x[0] == ex && y[0] == ey)
					{
						return next_de(x, y, mode, num, my);
					}
					x[1] = ex;
					y[1] = ey;
					return 1;
				}
			}
		}
		else if (rc == false)
		{
			for (int a = 2; a < 5; a++)
			{
				if (showBoard(ox[my] - a * i, oy[my] - a * j) == 1)
				{
					for (int b = 1; b < a; b++)
					{
						if (showBoard(ox[my] - b * i, oy[my] - b * j) == 2 || showBoard(ox[my] - b * i, oy[my] - b * j) == 3)
						{
							return next_de(x, y, mode, num, my);
						}
					}
					a = 6;
					break;
				}
			}
			if (showBoard(ox[my] + 5 * i, oy[my] + 5 * j) == 2 || showBoard(ox[my] + 5 * i, oy[my] + 5 * j) == 3)
			{
				if (num == 0)
				{
					x[0] = ex;
					y[0] = ey;
					return 1 + next_de(x, y, mode, 1, my);
				}
				else
				{
					if (x[0] == ex && y[0] == ey)
					{
						return next_de(x, y, mode, num, my);
					}
					x[1] = ex;
					y[1] = ey;
					return 1;
				}
			}
		}
		return next_de(x, y, mode, num, my);
	}
	if (lc == false && rc == false)
	{
		if (ex != -1 && ey != -1)
		{
			if (num == 0)
			{
				x[0] = ex;
				y[0] = ey;
				return 1 + next_de(x, y, mode, 1, my);
			}
			else
			{
				if (x[0] == ex && y[0] == ey)
				{
					return next_de(x, y, mode, num, my);
				}
				x[1] = ex;
				y[1] = ey;
				return 1;
			}
		}
		else
		{
			for (int a = 1; a < 4; a++)
			{
				if (showBoard(ox[my] + a * i, oy[my] + a * j) == 0)
				{
					if (num == 0)
					{
						x[0] = ox[my] + a * i;
						y[0] = oy[my] + a * j;
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						if (x[0] == ox[my] + a * i && y[0] == oy[my] + a * j)
						{
							return next_de(x, y, mode, num, my);
						}
						x[1] = ox[my] + a * i;
						y[1] = oy[my] + a * j;
						return 1;
					}
				}
			}
			return next_de(x, y, mode, num, my);
		}
	}
	if (lc == false)
	{
		if (ex != -1 && ey != -1)
		{
			if (num == 1)
			{
				if (x[0] == ex && y[0] == ey)
				{
					return next_de(x, y, mode, num, my);
				}
				x[1] = ex;
				y[1] = ey;
				return 1;
			}
			else
			{
				x[0] = ex;
				y[0] = ey;
				if (showBoard(ox[my] + i, oy[my] + j) == 1 || showBoard(ox[my] + i, oy[my] + j) == -1 || showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == 1 || showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == -1)
				{
					return 1 + next_de(x, y, mode, 1, my);
				}
				if (showBoard(ox[my] + 3 * i, oy[my] + 3 * j) == 1 || showBoard(ox[my] + 3 * i, oy[my] + 3 * j) == -1)
				{
					if (abs(ox[my] - ex) <= 3 && abs(oy[my] - ey) <= 3)
					{
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						if (showBoard(ox[my] + i, oy[my] + j) == 0)
						{
							x[1] = ox[my] + i;
							y[1] = oy[my] + j;
							return 2;
						}
						else if (showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == 0)
						{
							x[1] = ox[my] + 2 * i;
							y[1] = oy[my] + 2 * j;
							return 2;
						}
					}
				}
				if (showBoard(ox[my] + 4 * i, oy[my] + 4 * j) == 1 || showBoard(ox[my] + 4 * i, oy[my] + 4 * j) == -1)
				{
					if (abs(ox[my] - ex) <= 2 && abs(oy[my] - ey) <= 2)
					{
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						for (int a = 1; a < 4; a++)
						{
							if (showBoard(ox[my] + a * i, oy[my] + a * j) == 0)
							{
								x[1] = ox[my] + a * i;
								y[1] = oy[my] + a * j;
								return 2;
							}
						}
					}
				}
				return 1 + next_de(x, y, mode, 1, my);
			}
		}
		else
		{
			if (showBoard(ox[my] - 5 * i, oy[my] - 5 * j) == 0)
			{
				if (num == 1)
				{
					if (x[0] == ox[my] - 5 * i && y[0] == oy[my] - 5 * j)
					{
						return next_de(x, y, mode, num, my);
					}
					x[1] = ox[my] - 5 * i;
					y[1] = oy[my] - 5 * j;
					return 1;
				}
				else
				{
					x[0] = ox[my] - 5 * i;
					y[0] = oy[my] - 5 * j;
					if (showBoard(ox[my] + i, oy[my] + j) == 0)
					{
						if (showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == 2 || showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == 3)
						{
							return 1 + next_de(x, y, mode, 1, my);
						}
						else
						{
							x[1] = ox[my] + i;
							y[1] = oy[my] + j;
							return 2;
						}
					}
					return 1 + next_de(x, y, mode, 1, my);
				}
			}
			if (showBoard(ox[my] + i, oy[my] + j) == 1 || showBoard(ox[my] + i, oy[my] + j) == -1)
			{
				return next_de(x, y, mode, num, my);
			}
			else if(showBoard(ox[my] + i, oy[my] + j) == 0)
			{
				if (showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == 2 || showBoard(ox[my] + 2 * i, oy[my] + 2 * j) == 3)
				{
					return next_de(x, y, mode, num, my);
				}
				else
				{
					if (num == 0)
					{
						x[0] = ox[my] + i;
						y[0] = oy[my] + j;
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						if (x[0] == ox[my] + i && y[0] == oy[my] + j)
						{
							return next_de(x, y, mode, num, my);
						}
						x[1] = ox[my] + i;
						y[1] = oy[my] + j;
						return 1;
					}
				}
				return next_de(x, y, mode, num, my);
			}
		}
	}
	if (rc == false)
	{
		if (ex != -1 && ey != -1)
		{
			if (num == 1)
			{
				if (x[0] == ex && y[0] == ey)
				{
					return next_de(x, y, mode, num, my);
				}
				x[1] = ex;
				y[1] = ey;
				return 1;
			}
			else
			{
				x[0] = ex;
				y[0] = ey;
				if (showBoard(ox[my] - i, oy[my] - j) == 1 || showBoard(ox[my] - i, oy[my] - j) == -1 || showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == 1 || showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == -1)
				{
					return 1 + next_de(x, y, mode, 1, my);
				}
				if (showBoard(ox[my] - 3 * i, oy[my] - 3 * j) == 1 || showBoard(ox[my] - 3 * i, oy[my] - 3 * j) == -1)
				{
					if (abs(ox[my] - ex) <= 3 && abs(oy[my] - ey) <= 3)
					{
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						if (showBoard(ox[my] - i, oy[my] - j) == 0)
						{
							x[1] = ox[my] - i;
							y[1] = oy[my] - j;
							return 2;
						}
						else if (showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == 0)
						{
							x[1] = ox[my] - 2 * i;
							y[1] = oy[my] - 2 * j;
							return 2;
						}
					}
				}
				if (showBoard(ox[my] - 4 * i, oy[my] - 4 * j) == 1 || showBoard(ox[my] - 4 * i, oy[my] - 4 * j) == -1)
				{
					if (abs(ox[my] - ex) <= 2 && abs(oy[my] - ey) <= 2)
					{
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						for (int a = 1; a < 4; a++)
						{
							if (showBoard(ox[my] - a * i, oy[my] - a * j) == 0)
							{
								x[1] = ox[my] - a * i;
								y[1] = oy[my] - a * j;
								return 2;
							}
						}
					}
				}
				return 1 + next_de(x, y, mode, 1, my);
			}
		}
		else
		{
			if (showBoard(ox[my] + 5 * i, oy[my] + 5 * j) == 0)
			{
				if (num == 1)
				{
					if (x[0] == ox[my] + 5 * i && y[0] == oy[my] + 5 * j)
					{
						return next_de(x, y, mode, num, my);
					}
					x[1] = ox[my] + 5 * i;
					y[1] = oy[my] + 5 * j;
					return 1;
				}
				else
				{
					x[0] = ox[my] + 5 * i;
					y[0] = oy[my] + 5 * j;
					if (showBoard(ox[my] - i, oy[my] - j) == 0)
					{
						if (showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == 2 || showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == 3)
						{
							return 1 + next_de(x, y, mode, 1, my);
						}
						else
						{
							x[1] = ox[my] - i;
							y[1] = oy[my] - j;
							return 2;
						}
					}
					return 1 + next_de(x, y, mode, 1, my);
				}
			}
			if (showBoard(ox[my] - i, oy[my] - j) == 1 || showBoard(ox[my] - i, oy[my] - j) == -1)
			{
				return next_de(x, y, mode, num, my);
			}
			else if (showBoard(ox[my] - i, oy[my] - j) == 0)
			{
				if (showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == 2 || showBoard(ox[my] - 2 * i, oy[my] - 2 * j) == 3)
				{
					return next_de(x, y, mode, num, my);
				}
				else
				{
					if (num == 0)
					{
						x[0] = ox[my] - i;
						y[0] = oy[my] - j;
						return 1 + next_de(x, y, mode, 1, my);
					}
					else
					{
						if (x[0] == ox[my] - i && y[0] == oy[my] - j)
						{
							return next_de(x, y, mode, num, my);
						}
						x[1] = ox[my] - i;
						y[1] = oy[my] - j;
						return 1;
					}
				}
				return next_de(x, y, mode, num, my);
			}
		}
	}
	return next_de(x, y, mode, num, my);
}

int defense(int x[], int y[], int num, int my)
{
	int lempty = 0;
	int rempty = 0;
	int lempty_x[4] = { -1, -1, -1, -1};
	int rempty_x[4] = { -1, -1, -1, -1 };
	int eidx = 0;
	bool lc = true;
	bool rc = true;
	int opnum = 9;
	for (int i = 1;i < 5;i++)
	{
		if (lc && (showBoard(ox[my] - i, oy[my]) == 1 || showBoard(ox[my] - i, oy[my]) == -1)) //왼쪽이 이미 내 돌로 막혀있거나 범위 밖일 때
		{
			opnum = opnum - (5 - i);
			lc = false; 
		}
		if (rc && (showBoard(ox[my] + i, oy[my]) == 1 || showBoard(ox[my] + i, oy[my]) == -1)) //오른쪽이 이미 내 돌로 막혀있거나 범위 밖일 때
		{
			opnum = opnum - (5 - i);
			rc = false;
		}

		if (lc && showBoard(ox[my] - i, oy[my]) == 0) //왼쪽에 비어있는 칸 확인
		{
			lempty_x[lempty] = ox[my] - i;
			lempty++;
			eidx++;
			opnum--;
		}
		if (rc && showBoard(ox[my] + i, oy[my]) == 0) //오른쪽에 비어있는 칸 확인
		{
			rempty_x[rempty] = ox[my] + i;
			rempty++;
			eidx++;
			opnum--;
		}
	}

	if (lc == false)
	{
		return defended(lc, rc, x, y, lempty, rempty, -1, 0, 1, num, rempty_x[0], oy[my], opnum, my);
	}
	if (rc == false)
	{
		return defended(lc, rc, x, y, lempty, rempty, -1, 0, 1, num, lempty_x[0], oy[my], opnum, my);
	}

	if (eidx > 6) //7칸 이상 비어있으면 무시하고 다른 방향으로
	{
		return defense_v(x, y, num, my);
	}
	else if(eidx >= 1 && eidx <= 4) //1~4칸 비어있을 경우
	{
		if (lempty == 0)
		{
			if (num == 0)
			{
				x[0] = rempty_x[0];
				y[0] = oy[my];
				if (showBoard(ox[my] - 5, oy[my]) == 0)
				{
					x[1] = ox[my] - 5;
					y[1] = oy[my];
					return 2;
				}
				return 1 + defense_v(x, y, 1, my);
			}
			else
			{
				if (x[0] == rempty_x[0] && y[0] == oy[my])
				{
					return defense_v(x, y, num, my);
				}
				x[1] = rempty_x[0];
				y[1] = oy[my];
				return 1;
			}
		}
		if (rempty == 0)
		{
			if (num == 0)
			{
				x[0] = lempty_x[0];
				y[0] = oy[my];
				if (showBoard(ox[my] + 5, oy[my]) == 0)
				{
					x[1] = ox[my] + 5;
					y[1] = oy[my];
					return 2;
				}
				return 1 + defense_v(x, y, 1, my);
			}
			else
			{
				if (x[0] == lempty_x[0] && y[0] == oy[my])
				{
					return defense_v(x, y, num, my);
				}
				x[1] = lempty_x[0];
				y[1] = oy[my];
				return 1;
			}
		}
		if (eidx == 2 || eidx == 3)
		{
			if (num == 0)
			{
				x[0] = lempty_x[0];
				y[0] = oy[my];
				x[1] = rempty_x[0];
				y[1] = oy[my];
				return 2;
			}
			else
			{
				if (x[0] == lempty_x[0] && y[0] == oy[my])
				{
					return defense_v(x, y, num, my);
				}
				x[1] = lempty_x[0];
				y[1] = oy[my];
				return 1;
			}
		}
		if (eidx == 4)
		{
			if (lempty == 1 || rempty == 1)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = oy[my];
					x[1] = rempty_x[0];
					y[1] = oy[my];
					return 2;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = lempty_x[0];
					y[1] = oy[my];
					return 1;
				}
			}
			else
			{
				if ((showBoard(ox[my] - 4, oy[my]) != 0 && showBoard(ox[my] - 3, oy[my]) != 0) || (showBoard(ox[my] + 4, oy[my]) != 0 && showBoard(ox[my] + 3, oy[my]) != 0))
				{
					if (showBoard(ox[my] - 1, oy[my]) == 0 && showBoard(ox[my] + 1, oy[my]) == 0)
					{
						return defense_v(x, y, num, my);
					}
					else if (showBoard(ox[my] - 1, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - 1;
							y[0] = oy[my];
							return 1 + defense_v(x, y, 1, my);
						}
						else
						{
							if (x[0] == ox[my] - 1 && y[0] == oy[my])
							{
								return defense_v(x, y, num, my);
							}
							x[1] = ox[my] - 1;
							y[1] = oy[my];
							return 1;
						}
					}
					else
					{
						if (num == 0)
						{
							x[0] = ox[my] + 1;
							y[0] = oy[my];
							return 1 + defense_v(x, y, 1, my);
						}
						else
						{
							if (x[0] == ox[my] + 1 && y[0] == oy[my])
							{
								return defense_v(x, y, num, my);
							}
							x[1] = ox[my] + 1;
							y[1] = oy[my];
							return 1;
						}
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = oy[my];
						x[1] = rempty_x[0];
						y[1] = oy[my];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
			}
		}
		return defense_v(x, y, num, my);
	}
	else if (eidx == 5)
	{
		if (lempty == 1)
		{
			if (abs(ox[my] - lempty_x[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = oy[my];
					x[1] = ox[my] + 1;
					y[1] = oy[my];
					return 2;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = lempty_x[0];
					y[1] = oy[my];
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = oy[my];
					return 1 + defense_v(x, y, 1, my);
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = lempty_x[0];
					y[1] = oy[my];
					return 1;
				}
			}
		}
		else if (lempty == 2)
		{
			if (showBoard(ox[my] + 1, oy[my]) != 0)
			{
				if (showBoard(ox[my] - 1, oy[my]) == 0 || showBoard(ox[my] - 2, oy[my]) == 0)
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = oy[my];
						return 1 + defense_v(x, y, 1, my);
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = oy[my];
						x[1] = rempty_x[0];
						y[1] = oy[my];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my] + 2, oy[my]) != 0)
			{
				if (showBoard(ox[my] - 4, oy[my]) == 0)
				{
					if (num == 0)
					{
						x[0] = rempty_x[0];
						y[0] = oy[my];
						return 1 + defense_v(x, y, 1, my);
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = rempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
				return defense_v(x, y, num, my);
			}
			return defense_v(x, y, num, my);
		}
		else if (lempty == 3)
		{
			if (showBoard(ox[my] - 1, oy[my]) != 0)
			{
				if (showBoard(ox[my] + 1, oy[my]) == 0 || showBoard(ox[my] + 2, oy[my]) == 0)
				{
					if (num == 0)
					{
						x[0] = rempty_x[0];
						y[0] = oy[my];
						return 1 + defense_v(x, y, 1, my);
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = rempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = oy[my];
						x[1] = rempty_x[0];
						y[1] = oy[my];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my] - 2, oy[my]) != 0)
			{
				if (showBoard(ox[my] + 4, oy[my]) == 0)
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = oy[my];
						return 1 + defense_v(x, y, 1, my);
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == oy[my])
						{
							return defense_v(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = oy[my];
						return 1;
					}
				}
				return defense_v(x, y, num, my);
			}
			return defense_v(x, y, num, my);
		}
		else
		{
			if (abs(ox[my] - rempty_x[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = rempty_x[0];
					y[0] = oy[my];
					x[1] = ox[my] - 1;
					y[1] = oy[my];
					return 2;
				}
				else
				{
					if (x[0] == rempty_x[0] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = rempty_x[0];
					y[1] = oy[my];
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = rempty_x[0];
					y[0] = oy[my];
					return 1 + defense_v(x, y, 1, my);
				}
				else
				{
					if (x[0] == rempty_x[0] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = rempty_x[0];
					y[1] = oy[my];
					return 1;
				}
			}
		}
	}
	else if (eidx == 6)
	{
		if (lempty == 4)
		{
			if (showBoard(ox[my] + 5, oy[my]) == 2 || showBoard(ox[my] + 5, oy[my]) == 3)
			{
				if (num == 0)
				{
					x[0] = rempty_x[1];
					y[0] = oy[my];
					return 1 + defense_v(x, y, 1, my);
				}
				else
				{
					if (x[0] == rempty_x[1] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = rempty_x[1];
					y[1] = oy[my];
					return 1;
				}
			}
			else
			{
				return defense_v(x, y, num, my);
			}
		}
		else if (rempty == 4)
		{
			if (showBoard(ox[my] - 5, oy[my]) == 2 || showBoard(ox[my] - 5, oy[my]) == 3)
			{
				if (num == 0)
				{
					x[0] = lempty_x[1];
					y[0] = oy[my];
					return 1 + defense_v(x, y, 1, my);
				}
				else
				{
					if (x[0] == lempty_x[1] && y[0] == oy[my])
					{
						return defense_v(x, y, num, my);
					}
					x[1] = lempty_x[1];
					y[1] = oy[my];
					return 1;
				}
			}
			else
			{
				return defense_v(x, y, num, my);
			}
		}
		return defense_v(x, y, num, my);
	}
	return defense_v(x, y, num, my);
}

int defense_v(int x[], int y[], int num, int my)
{
	int uempty = 0;
	int dempty = 0;
	int uempty_y[4] = { -1, -1, -1, -1 };
	int dempty_y[4] = { -1, -1, -1, -1 };
	int eidx = 0;
	bool uc = true;
	bool dc = true;
	int opnum = 9;
	for (int i = 1;i < 5;i++)
	{
		if (uc && (showBoard(ox[my], oy[my] - i) == 1 || showBoard(ox[my], oy[my] - i) == -1)) //위쪽이 이미 내 돌로 막혀있을 때
		{
			opnum = opnum - (5 - i);
			uc = false;
		}
		if (dc && (showBoard(ox[my], oy[my] + i) == 1 || showBoard(ox[my], oy[my] + i) == -1)) //아래쪽이 이미 내 돌로 막혀있을 때
		{
			opnum = opnum - (5 - i);
			dc = false;
		}

		if (uc && showBoard(ox[my], oy[my] - i) == 0) //위쪽에 비어있는 칸 확인
		{
			uempty_y[uempty] = oy[my] - i;
			uempty++;
			eidx++;
			opnum--;
		}
		if (dc && showBoard(ox[my], oy[my] + i) == 0) //아래쪽에 비어있는 칸 확인
		{
			dempty_y[dempty] = oy[my] + i;
			dempty++;
			eidx++;
			opnum--;
		}
	}

	if (uc == false)
	{
		return defended(uc, dc, x, y, uempty, dempty, 0, -1, 2, num, ox[my], dempty_y[0], opnum, my);
	}
	if (dc == false)
	{
		return defended(uc, dc, x, y, uempty, dempty, 0, -1, 2, num, ox[my], uempty_y[0], opnum, my);
	}

	if (eidx > 6) //7칸 이상 비어있으면 무시하고 다른 방향으로
	{
		return defense_nw(x, y, num, my);
	}
	else if(eidx >= 1 && eidx <= 4) //1~4칸 비어있을 경우
	{
		if (uempty == 0)
		{
			if (num == 0)
			{
				x[0] = ox[my];
				y[0] = dempty_y[0];
				if (showBoard(ox[my], oy[my] - 5) == 0)
				{
					x[1] = ox[my];
					y[1] = oy[my] - 5;
					return 2;
				}
				return 1 + defense_nw(x, y, 1, my);
			}
			else
			{
				if (x[0] == ox[my] && y[0] == dempty_y[0])
				{
					return defense_nw(x, y, num, my);
				}
				x[1] = ox[my];
				y[1] = dempty_y[0];
				return 1;
			}
			return defense_nw(x, y, num, my);
		}
		if (dempty == 0)
		{
			if (num == 0)
			{
				x[0] = ox[my];
				y[0] = uempty_y[0];
				if (showBoard(ox[my], oy[my] + 5) == 0)
				{
					x[1] = ox[my];
					y[1] = oy[my] + 5;
					return 2;
				}
				return 1 + defense_nw(x, y, 1, my);
			}
			else
			{
				if (x[0] == ox[my] && y[0] == uempty_y[0])
				{
					return defense_nw(x, y, num, my);
				}
				x[1] = ox[my];
				y[1] = uempty_y[0];
				return 1;
			}
			return defense_nw(x, y, num, my);
		}
		if (eidx == 2 || eidx == 3)
		{
			if (num == 0)
			{
				x[0] = ox[my];
				y[0] = uempty_y[0];
				x[1] = ox[my];
				y[1] = dempty_y[0];
				return 2;
			}
			else
			{
				if (abs(oy[my] - uempty_y[0]) > abs(oy[my] - dempty_y[0]))
				{
					if (x[0] == ox[my] && y[0] == dempty_y[0])
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = dempty_y[0];
					return 1;
				}
				else
				{
					if (x[0] == ox[my] && y[0] == uempty_y[0])
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = uempty_y[0];
					return 1;
				}
			}
			return defense_nw(x, y, num, my);
		}
		if (eidx == 4)
		{
			if (uempty == 1 || dempty == 1)
			{
				if (num == 0)
				{
					x[0] = ox[my];
					y[0] = uempty_y[0];
					x[1] = ox[my];
					y[1] = dempty_y[0];
					return 2;
				}
				else
				{
					if (uempty == 1)
					{
						if (x[0] == ox[my] && y[0] == dempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == ox[my] && y[0] == uempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = uempty_y[0];
						return 1;
					}
				}
				return defense_nw(x, y, num, my);
			}
			else
			{
				if ((showBoard(ox[my], oy[my] - 4) != 0 && showBoard(ox[my], oy[my] - 3) != 0) || (showBoard(ox[my], oy[my] + 4) != 0 && showBoard(ox[my], oy[my] + 3) != 0))
				{
					if (showBoard(ox[my], oy[my] - 1) == 0 && showBoard(ox[my], oy[my] + 1) == 0)
					{
						return defense_nw(x, y, num, my);
					}
					else if (showBoard(ox[my], oy[my] - 1) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] - 1;
							return 1 + defense_nw(x, y, 1, my);
						}
						else
						{
							if (x[0] == ox[my] && y[0] == oy[my] - 1)
							{
								return defense_nw(x, y, num, my);
							}
							x[1] = ox[my];
							y[1] = oy[my] - 1;
							return 1;
						}
					}
					else
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] + 1;
							return 1 + defense_nw(x, y, 1, my);
						}
						else
						{
							if (x[0] == ox[my] && y[0] == oy[my] + 1)
							{
								return defense_nw(x, y, num, my);
							}
							x[1] = ox[my];
							y[1] = oy[my] + 1;
							return 1;
						}
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = uempty_y[0];
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == ox[my] && y[0] == dempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 1;
					}
				}
				return defense_nw(x, y, num, my);
			}
			return defense_nw(x, y, num, my);
		}
		return defense_nw(x, y, num, my);
	}
	else if (eidx == 5)
	{
		if (uempty == 1)
		{
			if (abs(oy[my] - uempty_y[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = ox[my];
					y[0] = uempty_y[0];
					x[1] = ox[my];
					y[1] = oy[my] + 1;
					return 2;
				}
				else
				{
					if (x[0] == ox[my] && y[0] == oy[my] + 1)
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = oy[my] + 1;
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = ox[my];
					y[0] = uempty_y[0];
					return 1 + defense_nw(x, y, 1, my);
				}
				else
				{
					if (x[0] == ox[my] && y[0] == uempty_y[0])
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = uempty_y[0];
					return 1;
				}
			}
		}
		else if (uempty == 2)
		{
			if (showBoard(ox[my], oy[my] + 1) != 0)
			{
				if (showBoard(ox[my], oy[my] - 1) == 0 || showBoard(ox[my], oy[my] - 2) == 0)
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = uempty_y[0];
						return 1 + defense_nw(x, y, 1, my);
					}
					else
					{
						if (x[0] == ox[my] && y[0] == uempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = uempty_y[0];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = uempty_y[0];
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == ox[my] && y[0] == uempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = uempty_y[0];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my], oy[my] + 2) != 0)
			{
				if (showBoard(ox[my], oy[my] - 4) == 0)
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = dempty_y[0];
						return 1 + defense_nw(x, y, 1, my);
					}
					else
					{
						if (x[0] == ox[my] && y[0] == dempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 1;
					}
				}
				return defense_nw(x, y, num, my);
			}
			return defense_nw(x, y, num, my);
		}
		else if (uempty == 3)
		{
			if (showBoard(ox[my], oy[my] - 1) != 0)
			{
				if (showBoard(ox[my], oy[my] + 1) == 0 || showBoard(ox[my], oy[my] + 2) == 0)
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = dempty_y[0];
						return 1 + defense_nw(x, y, 1, my);
					}
					else
					{
						if (x[0] == ox[my] && y[0] == dempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = uempty_y[0];
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == ox[my] && y[0] == dempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = dempty_y[0];
						return 1;
					}
				}
				if (num == 0)
				{
					x[0] = ox[my];
					y[0] = dempty_y[0];
					x[1] = ox[my];
					y[1] = uempty_y[0];
					return 2;
				}
				else
				{
					if (x[0] == ox[my] && y[0] == dempty_y[0])
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = dempty_y[0];
					return 1;
				}
			}
			else if (showBoard(ox[my], oy[my] - 2) != 0)
			{
				if (showBoard(ox[my], oy[my] + 4) == 0)
				{
					if (num == 0)
					{
						x[0] = ox[my];
						y[0] = uempty_y[0];
						return 1 + defense_nw(x, y, 1, my);
					}
					else
					{
						if (x[0] == ox[my] && y[0] == uempty_y[0])
						{
							return defense_nw(x, y, num, my);
						}
						x[1] = ox[my];
						y[1] = uempty_y[0];
						return 1;
					}
				}
				return defense_nw(x, y, num, my);
			}
			return defense_nw(x, y, num, my);
		}
		else
		{
			if (num == 0)
			{
				x[0] = ox[my];
				y[0] = dempty_y[0];
				x[1] = ox[my];
				y[1] = oy[my] - 1;
				return 2;
			}
			else
			{
				if (x[0] == ox[my] && y[0] == dempty_y[0])
				{
					return defense_nw(x, y, num, my);
				}
				x[1] = ox[my];
				y[1] = dempty_y[0];
				return 1;
			}
		}
	}
	else if (eidx == 6)
	{
		if (uempty == 4)
		{
			if (showBoard(ox[my], oy[my] + 5) == 2 || showBoard(ox[my], oy[my] + 5) == 3)
			{
				if (num == 0)
				{
					x[0] = ox[my];
					y[0] = dempty_y[1];
					return 1 + defense_nw(x, y, 1, my);
				}
				else
				{
					if (x[0] == ox[my] && y[0] == dempty_y[1])
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = dempty_y[1];
					return 1;
				}
			}
			else
			{
				return defense_nw(x, y, num, my);
			}
		}
		else if (dempty == 4)
		{
			if (showBoard(ox[my], oy[my] - 5) == 2 || showBoard(ox[my], oy[my] - 5) == 3)
			{
				if (num == 0)
				{
					x[0] = ox[my];
					y[0] = uempty_y[1];
					return 1 + defense_nw(x, y, 1, my);
				}
				else
				{
					if (x[0] == ox[my] && y[0] == dempty_y[1])
					{
						return defense_nw(x, y, num, my);
					}
					x[1] = ox[my];
					y[1] = dempty_y[1];
					return 1;
				}
			}
			else
			{
				return defense_nw(x, y, num, my);
			}
		}
		return defense_nw(x, y, num, my);
	}
	return defense_nw(x, y, num, my);
}

int defense_nw(int x[], int y[], int num, int my)
{
	int nwempty = 0;
	int seempty = 0;
	int lempty_x[4] = { -1, -1, -1, -1 };
	int lempty_y[4] = { -1, -1, -1, -1 };
	int rempty_x[4] = { -1, -1, -1, -1 };
	int rempty_y[4] = { -1, -1, -1, -1 };
	int eidx = 0;
	bool nwc = true;
	bool sec = true;
	int opnum = 9;
	for (int i = 1;i < 5;i++)
	{
		if (nwc && (showBoard(ox[my] - i, oy[my] - i) == 1 || showBoard(ox[my] - i, oy[my] - i) == -1)) //왼쪽 위쪽이 이미 내 돌로 막혀있을 때
		{
			opnum = opnum - (5 - i);
			nwc = false;
		}
		if (sec && (showBoard(ox[my] + i, oy[my] + i) == 1 || showBoard(ox[my] + i, oy[my] + i) == -1)) //오른쪽 아래쪽이 이미 내 돌로 막혀있을 때
		{
			opnum = opnum - (5 - i);
			sec = false;
		}

		if (nwc && showBoard(ox[my] - i, oy[my] - i) == 0) //왼쪽 위쪽에 비어있는 칸 확인
		{
			lempty_x[nwempty] = ox[my] - i;
			lempty_y[nwempty] = oy[my] - i;
			nwempty++;
			eidx++;
			opnum--;
		}
		if (sec && showBoard(ox[my] + i, oy[my] + i) == 0) //오른쪽 아래쪽에 비어있는 칸 확인
		{
			rempty_x[seempty] = ox[my] + i;
			rempty_y[seempty] = oy[my] + i;
			seempty++;
			eidx++;
			opnum--;
		}
	}

	if (nwc == false)
	{
		return defended(nwc, sec, x, y, nwempty, seempty, -1, -1, 3, num, rempty_x[0], rempty_y[0], opnum, my);
	}
	if (sec == false)
	{
		return defended(nwc, sec, x, y, nwempty, seempty, -1, -1, 3, num, lempty_x[0], lempty_y[0], opnum, my);
	}

	if (eidx > 6) //7칸 이상 비어있으면 무시하고 다른 방향으로
	{
		return defense_ne(x, y, num, my);
	}
	else if(eidx >=1 && eidx <= 4)//1~4개 비어있을 경우
	{
		if (nwempty == 0)
		{
			if (num == 0)
			{
				x[0] = rempty_x[0];
				y[0] = rempty_y[0];
				if (showBoard(ox[my] - 5, oy[my] - 5) == 0)
				{
					x[1] = ox[my] - 5;
					y[1] = oy[my] - 5;
					return 2;
				}
				return 1 + defense_ne(x, y, 1, my);
			}
			else
			{
				if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
				{
					return defense_ne(x, y, num, my);
				}
				x[1] = rempty_x[0];
				y[1] = rempty_y[0];
				return 1;
			}
			return defense_ne(x, y, num, my);
		}
		if (seempty == 0)
		{
			if (num == 0)
			{
				x[0] = lempty_x[0];
				y[0] = lempty_y[0];
				if (showBoard(ox[my] + 5, oy[my] + 5) == 0)
				{
					x[1] = ox[my] + 5;
					y[1] = oy[my] + 5;
					return 2;
				}
				return 1 + defense_ne(x, y, 1, my);
			}
			else
			{
				if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
				{
					return defense_ne(x, y, num, my);
				}
				x[1] = lempty_x[0];
				y[1] = lempty_y[0];
				return 1;
			}
			return defense_ne(x, y, num, my);
		}
		if (eidx == 2 || eidx == 3)
		{
			if (num == 0)
			{
				x[0] = lempty_x[0];
				y[0] = lempty_y[0];
				x[1] = rempty_x[0];
				y[1] = rempty_y[0];
				return 2;
			}
			else
			{
				if (abs(oy[my] - lempty_y[0]) > abs(oy[my] - rempty_y[0]))
				{
					if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 1;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = lempty_x[0];
					y[1] = lempty_y[0];
					return 1;
				}
			}
			return defense_ne(x, y, num, my);
		}
		if (eidx == 4)
		{
			if (nwempty == 1 || seempty == 1)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 2;
				}
				else
				{
					if (nwempty == 1)
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				return defense_ne(x, y, num, my);
			}
			else
			{
				if ((showBoard(ox[my] - 4, oy[my] - 4) != 0 && showBoard(ox[my] - 3, oy[my] - 3) != 0) || (showBoard(ox[my] + 4, oy[my] + 4) != 0 && showBoard(ox[my] + 3, oy[my] + 3) != 0))
				{
					if (showBoard(ox[my] - 1, oy[my] - 1) == 0 && showBoard(ox[my] + 1, oy[my] + 1) == 0)
					{
						return defense_ne(x, y, num, my);
					}
					else if (showBoard(ox[my] - 1, oy[my] - 1) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - 1;
							y[0] = oy[my] - 1;
							return 1 + defense_ne(x, y, 1, my);
						}
						else
						{
							if (x[0] == ox[my] - 1 && y[0] == oy[my] - 1)
							{
								return defense_ne(x, y, num, my);
							}
							x[1] = ox[my] - 1;
							y[1] = oy[my] - 1;
							return 1;
						}
					}
					else
					{
						if (num == 0)
						{
							x[0] = ox[my] + 1;
							y[0] = oy[my] + 1;
							return 1 + defense_ne(x, y, 1, my);
						}
						else
						{
							if (x[0] == ox[my] + 1 && y[0] == oy[my] + 1)
							{
								return defense_ne(x, y, num, my);
							}
							x[1] = ox[my] + 1;
							y[1] = oy[my] + 1;
							return 1;
						}
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				return defense_ne(x, y, num, my);
			}
			return defense_ne(x, y, num, my);
		}
		return defense_ne(x, y, num, my);
	}
	else if (eidx == 5)
	{
		if (nwempty == 1)
		{
			if (abs(oy[my] - lempty_y[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 2;
				}
				else
				{
					if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					return 1 + defense_ne(x, y, 1, my);
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = lempty_x[0];
					y[1] = lempty_y[0];
					return 1;
				}
			}
		}
		else if (nwempty == 2)
		{
			if (showBoard(ox[my] + 1, oy[my] + 1) != 0)
			{
				if (showBoard(ox[my] - 1, oy[my] - 1) == 0 || showBoard(ox[my] - 2, oy[my] - 2) == 0)
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						return 1 + defense_ne(x, y, 1, my);
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my] + 2, oy[my] + 2) != 0)
			{
				if (showBoard(ox[my] - 4, oy[my] - 4) == 0)
				{
					if (num == 0)
					{
						x[0] = rempty_x[0];
						y[0] = rempty_y[0];
						return 1 + defense_ne(x, y, 1, my);
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
				return defense_ne(x, y, num, my);
			}
			return defense_ne(x, y, num, my);
		}
		else if (nwempty == 3)
		{
			if (showBoard(ox[my] - 1, oy[my] - 1) != 0)
			{
				if (showBoard(ox[my] + 1, oy[my] + 1) == 0 || showBoard(ox[my] + 2, oy[my] + 2) == 0)
				{
					if (num == 0)
					{
						x[0] = rempty_x[0];
						y[0] = rempty_y[0];
						return 1 + defense_ne(x, y, 1, my);
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my] - 2, oy[my] - 2) != 0)
			{
				if (showBoard(ox[my] + 4, oy[my] + 4) == 0)
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						return 1 + defense_ne(x, y, 1, my);
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return defense_ne(x, y, num, my);
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				return defense_ne(x, y, num, my);
			}
			return defense_ne(x, y, num, my);
		}
		else
		{
			if (abs(oy[my] - rempty_y[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 2;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = lempty_x[0];
					y[1] = lempty_y[0];
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = rempty_x[0];
					y[0] = rempty_y[0];
					return 1 + defense_ne(x, y, 1, my);
				}
				else
				{
					if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 1;
				}
			}
		}
		return defense_ne(x, y, num, my);
	}
	else if (eidx == 6)
	{
		if (nwempty == 4)
		{
			if (showBoard(ox[my] + 5, oy[my] + 5) == 2 || showBoard(ox[my] + 5, oy[my] + 5) == 3)
			{
				if (num == 0)
				{
					x[0] = rempty_x[1];
					y[0] = rempty_y[1];
					return 1 + defense_ne(x, y, 1, my);
				}
				else
				{
					if (x[0] == rempty_x[1] && y[0] == rempty_y[1])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = rempty_x[1];
					y[1] = rempty_y[1];
					return 1;
				}
			}
			else
			{
				return defense_ne(x, y, num, my);
			}
		}
		else if (seempty == 4)
		{
			if (showBoard(ox[my] - 5, oy[my] - 5) == 2 || showBoard(ox[my] - 5, oy[my] - 5) == 3)
			{
				if (num == 0)
				{
					x[0] = lempty_x[1];
					y[0] = lempty_y[1];
					return 1 + defense_ne(x, y, 1, my);
				}
				else
				{
					if (x[0] == lempty_x[1] && y[0] == lempty_y[1])
					{
						return defense_ne(x, y, num, my);
					}
					x[1] = lempty_x[1];
					y[1] = lempty_y[1];
					return 1;
				}
			}
			else
			{
				return defense_ne(x, y, num, my);
			}
		}
		return defense_ne(x, y, num, my);
	}
	return defense_ne(x, y, num, my);
}

int defense_ne(int x[], int y[], int num, int my)
{
	int neempty = 0;
	int swempty = 0;
	int rempty_x[4] = { -1, -1, -1, -1 };
	int rempty_y[4] = { -1, -1, -1, -1 };
	int lempty_x[4] = { -1, -1, -1, -1 };
	int lempty_y[4] = { -1, -1, -1, -1 };
	int eidx = 0;
	bool nec = true;
	bool swc = true;
	int opnum = 9;
	for (int i =1;i < 5;i++)
	{
		if (nec && (showBoard(ox[my] + i, oy[my] - i) == 1 || showBoard(ox[my] + i, oy[my] - i) == -1)) //오른쪽 위쪽이 이미 내 돌로 막혀있을 때
		{
			opnum = opnum - (5 - i);
			nec = false;
		}
		if (swc && (showBoard(ox[my] - i, oy[my] + i) == 1 || showBoard(ox[my] - i, oy[my] + i) == -1)) //왼쪽 아래쪽이 이미 내 돌로 막혀있을 때
		{
			opnum = opnum - (5 - i);
			swc = false;
		}

		if (nec && showBoard(ox[my] + i, oy[my] - i) == 0) //오른쪽 위쪽에 비어있는 칸 확인
		{
			rempty_x[neempty] = ox[my] + i;
			rempty_y[neempty] = oy[my] - i;
			neempty++;
			eidx++;
			opnum--;
		}
		if (swc && showBoard(ox[my] - i, oy[my] + i) == 0) //왼쪽 아래쪽에 비어있는 칸 확인
		{
			lempty_x[swempty] = ox[my] - i;
			lempty_y[swempty] = oy[my] + i;
			swempty++;
			eidx++;
			opnum--;
		}
	}

	if (nec == false)
	{
		return defended(nec, swc, x, y, neempty, swempty, 1, -1, 4, num, lempty_x[0], lempty_y[0], opnum, my);
	}
	if (swc == false)
	{
		return defended(nec, swc, x, y, neempty, swempty, 1, -1, 4, num, rempty_x[0], rempty_y[0], opnum, my);
	}

	if (eidx > 6) //7칸 이상 비어있으면 무시하고 끝
	{
		return 0;
	}
	else if(eidx >= 1 && eidx <= 4) //1~4개 비어있을 경우
	{
		if (neempty == 0)
		{
			if (num == 0)
			{
				x[0] = lempty_x[0];
				y[0] = lempty_y[0];
				if (showBoard(ox[my] + 5, oy[my] - 5) == 0)
				{
					x[1] = ox[my] + 5;
					y[1] = oy[my] - 5;
					return 2;
				}
				return 1;
			}
			else
			{
				if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
				{
					return 0;
				}
				x[1] = lempty_x[0];
				y[1] = lempty_y[0];
				return 1;
			}
			return 0;
		}
		if (swempty == 0)
		{
			if (num == 0)
			{
				x[0] = rempty_x[0];
				y[0] = rempty_y[0];
				if (showBoard(ox[my] - 5, oy[my] + 5) == 0)
				{
					x[1] = ox[my] - 5;
					y[1] = oy[my] + 5;
					return 2;
				}
				return 1;
			}
			else
			{
				if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
				{
					return 0;
				}
				x[1] = rempty_x[0];
				y[1] = rempty_y[0];
				return 1;

			}
			return 0;
		}
		if (eidx == 2 || eidx == 3)
		{
			if (num == 0)
			{
				x[0] = lempty_x[0];
				y[0] = lempty_y[0];
				x[1] = rempty_x[0];
				y[1] = rempty_y[0];
				return 2;
			}
			else
			{
				if (abs(oy[my] - lempty_y[0]) > abs(oy[my] - rempty_y[0]))
				{
					if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
					{
						return 0;
					}
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 1;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
					{
						return 0;
					}
					x[1] = lempty_x[0];
					y[1] = lempty_y[0];
					return 1;
				}
			}
			return 0;
		}
		if (eidx == 4)
		{
			if (neempty == 1 || swempty == 1)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 2;
				}
				else
				{
					if (neempty == 1)
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return 0;
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return 0;
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
				return 0;
			}
			else
			{
				if ((showBoard(ox[my] + 4, oy[my] - 4) != 0 && showBoard(ox[my] + 3, oy[my] - 3) != 0) || (showBoard(ox[my] - 4, oy[my] + 4) != 0 && showBoard(ox[my] - 3, oy[my] + 3) != 0))
				{
					if (showBoard(ox[my] + 1, oy[my] - 1) == 0 && showBoard(ox[my] - 1, oy[my] + 1) == 0)
					{
						return 0;
					}
					else if (showBoard(ox[my] + 1, oy[my] - 1) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + 1;
							y[0] = oy[my] - 1;
							return 1;
						}
						else
						{
							if (x[0] == ox[my] + 1 && y[0] == oy[my] - 1)
							{
								return 0;
							}
							x[1] = ox[my] + 1;
							y[1] = oy[my] - 1;
							return 1;
						}
					}
					else
					{
						if (num == 0)
						{
							x[0] = ox[my] - 1;
							y[0] = oy[my] + 1;
							return 1;
						}
						else
						{
							if (x[0] == ox[my] - 1 && y[0] == oy[my] + 1)
							{
								return 0;
							}
							x[1] = ox[my] - 1;
							y[1] = oy[my] + 1;
							return 1;
						}
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return 0;
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				return 0;
			}
			return 0;
		}
		return 0;
	}
	else if (eidx == 5)
	{
		if (neempty == 1)
		{
			if (abs(oy[my] - rempty_y[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 2;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
					{
						return 0;
					}
					x[1] = lempty_x[0];
					y[1] = lempty_y[0];
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = rempty_x[0];
					y[0] = rempty_y[0];
					return 1;
				}
				else
				{
					if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
					{
						return 0;
					}
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 1;
				}
			}
		}
		else if (neempty == 2)
		{
			if (showBoard(ox[my] - 1, oy[my] + 1) != 0)
			{
				if (showBoard(ox[my] + 1, oy[my] - 1) == 0 || showBoard(ox[my] + 2, oy[my] - 2) == 0)
				{
					if (num == 0)
					{
						x[0] = rempty_x[0];
						y[0] = rempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return 0;
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return 0;
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my] - 2, oy[my] + 2) != 0)
			{
				if (showBoard(ox[my] + 4, oy[my] - 4) == 0)
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return 0;
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				return 0;
			}
			return 0;
		}
		else if (neempty == 3)
		{
			if (showBoard(ox[my] + 1, oy[my] - 1) != 0)
			{
				if (showBoard(ox[my] - 1, oy[my] + 1) == 0 || showBoard(ox[my] - 2, oy[my] + 2) == 0)
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return 0;
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
				else
				{
					if (num == 0)
					{
						x[0] = lempty_x[0];
						y[0] = lempty_y[0];
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 2;
					}
					else
					{
						if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
						{
							return 0;
						}
						x[1] = lempty_x[0];
						y[1] = lempty_y[0];
						return 1;
					}
				}
			}
			else if (showBoard(ox[my] + 2, oy[my] - 2) != 0)
			{
				if (showBoard(ox[my] - 4, oy[my] + 4) == 0)
				{
					if (num == 0)
					{
						x[0] = rempty_x[0];
						y[0] = rempty_y[0];
						return 1;
					}
					else
					{
						if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
						{
							return 0;
						}
						x[1] = rempty_x[0];
						y[1] = rempty_y[0];
						return 1;
					}
				}
				return 0;
			}
			return 0;
		}
		else
		{
			if (abs(oy[my] - lempty_y[0]) == 4)
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 2;
				}
				else
				{
					if (x[0] == rempty_x[0] && y[0] == rempty_y[0])
					{
						return 0;
					}
					x[1] = rempty_x[0];
					y[1] = rempty_y[0];
					return 1;
				}
			}
			else
			{
				if (num == 0)
				{
					x[0] = lempty_x[0];
					y[0] = lempty_y[0];
					return 1;
				}
				else
				{
					if (x[0] == lempty_x[0] && y[0] == lempty_y[0])
					{
						return 0;
					}
					x[1] = lempty_x[0];
					y[1] = lempty_y[0];
					return 1;
				}
			}
		}
		return 0;
	}
	else if (eidx == 6)
	{
		if (neempty == 4)
		{
			if (showBoard(ox[my] - 5, oy[my] + 5) == 2 || showBoard(ox[my] - 5, oy[my] + 5) == 3)
			{
				if (num == 0)
				{
					x[0] = lempty_x[1];
					y[0] = lempty_y[1];
					return 1;
				}
				else
				{
					if (x[0] == lempty_x[1] && y[0] == lempty_y[1])
					{
						return 0;
					}
					x[1] = lempty_x[1];
					y[1] = lempty_y[1];
					return 1;
				}
			}
			else
			{
				return 0;
			}
		}
		else if (swempty == 4)
		{
			if (showBoard(ox[my] + 5, oy[my] - 5) == 2 || showBoard(ox[my] + 5, oy[my] - 5) == 3)
			{
				if (num == 0)
				{
					x[0] = rempty_x[1];
					y[0] = rempty_y[1];
					return 1;
				}
				else
				{
					if (x[0] == rempty_x[1] && y[0] == rempty_y[1])
					{
						return 0;
					}
					x[1] = rempty_x[1];
					y[1] = rempty_y[1];
					return 1;
				}
			}
			else
			{
				return 0;
			}
		}
		return 0;
	}
	return 0;
}

int last_defense(int x[], int y[])
{
	int op1 = 0;
	op1 = each(x, y, 0, 0);
	int op2 = 0;
	if (op1 == 2)
	{
		return 2;
	}
	else if (op1 == 1)
	{
		op2 = each(x, y, 1, 1);
	}
	else
	{
		op2 = each(x, y, 1, 0);
	}
	
	int num = op1 + op2;
	if (num == 2)
	{
		return 2;
	}
	if (num == 1)
	{
		return 1;
	}
	
	bool firstl = true;		bool firstr = true;
	bool secondl = true;	bool secondr = true;
	int lx0[4] = { -1, -1, -1, -1 };	int ly0[4] = { -1, -1, -1, -1 };
	int rx0[4] = { -1, -1, -1, -1 };	int ry0[4] = { -1, -1, -1, -1 };
	int lx1[4] = { -1, -1, -1, -1 };	int ly1[4] = { -1, -1, -1, -1 };
	int rx1[4] = { -1, -1, -1, -1 };	int ry1[4] = { -1, -1, -1, -1 };
	int l0 = 0;	int r0 = 0;
	int l1 = 0;	int r1 = 0;
	int i0 = 0;	int j0 = 0;
	int i1 = 0;	int j1 = 0;

	check(firstl, firstr, l0, r0, lx0, ly0, rx0, ry0, 0, -1, 0); i0 = -1; j0 = 0;
	if ((firstl == false && firstr == false) || (l0 + r0 < 2))
	{
		firstl = true;
		firstr = true;
		for (int a = 0; a < 4; a++)
		{
			lx0[a] = -1;
			ly0[a] = -1;
			rx0[a] = -1;
			ry0[a] = -1;
		}
		l0 = 0;
		r0 = 0;
		check(firstl, firstr, l0, r0, lx0, ly0, rx0, ry0, 0, 0, -1); i0 = 0; j0 = -1;
		if ((firstl == false && firstr == false) || (l0 + r0 < 2))
		{
			firstl = true;
			firstr = true;
			for (int a = 0; a < 4; a++)
			{
				lx0[a] = -1;
				ly0[a] = -1;
				rx0[a] = -1;
				ry0[a] = -1;
			}
			l0 = 0;
			r0 = 0;
			check(firstl, firstr, l0, r0, lx0, ly0, rx0, ry0, 0, -1, -1); i0 = -1; j0 = -1;
			if ((firstl == false && firstr == false) || (l0 + r0 < 2))
			{
				firstl = true;
				firstr = true;
				for (int a = 0; a < 4; a++)
				{
					lx0[a] = -1;
					ly0[a] = -1;
					rx0[a] = -1;
					ry0[a] = -1;
				}
				l0 = 0;
				r0 = 0;
				check(firstl, firstr, l0, r0, lx0, ly0, rx0, ry0, 0, -1, 1); i0 = -1; j0 = 1;
				if ((firstl == false && firstr == false) || (l0 + r0 < 2))
				{
					return 0;
				}
			}
		}
	}

	check(secondl, secondr, l1, r1, lx1, ly1, rx1, ry1, 1, -1, 0); i1 = -1; j1 = 0;
	if ((secondl == false && secondr == false) || (l1 + r1 < 2))
	{
		secondl = true;
		secondr = true;
		for (int a = 0; a < 4; a++)
		{
			lx1[a] = -1;
			ly1[a] = -1;
			rx1[a] = -1;
			ry1[a] = -1;
		}
		l1 = 0;
		r1 = 0;
		check(secondl, secondr, l1, r1, lx1, ly1, rx1, ry1, 1, 0, -1); i1 = 0; j1 = -1;
		if ((secondl == false && secondr == false) || (l1 + r1 < 2))
		{
			secondl = true;
			secondr = true;
			for (int a = 0; a < 4; a++)
			{
				lx1[a] = -1;
				ly1[a] = -1;
				rx1[a] = -1;
				ry1[a] = -1;
			}
			l1 = 0;
			r1 = 0;
			check(secondl, secondr, l1, r1, lx1, ly1, rx1, ry1, 1, -1, -1); i1 = -1; j1 = -1;
			if ((secondl == false && secondr == false) || (l1 + r1 < 2))
			{
				secondl = true;
				secondr = true;
				for (int a = 0; a < 4; a++)
				{
					lx1[a] = -1;
					ly1[a] = -1;
					rx1[a] = -1;
					ry1[a] = -1;
				}
				l1 = 0;
				r1 = 0;
				check(secondl, secondr, l1, r1, lx1, ly1, rx1, ry1, 1, -1, 1); i1 = -1; j1 = 1;
				if ((secondl == false && secondr == false) || (l1 + r1 < 2))
				{
					return 0;
				}
			}
		}
	}

	if (ox[0] == ox[1] && abs(oy[0] - oy[1]) <= 4 && (i0 == 0 && j0 == -1 && i1 == 0 && j1 == -1))
	{
		return 0;
	}
	if (oy[0] == oy[1] && abs(ox[0] - ox[1]) <= 4 && (i0 == -1 && j0 == 0 && i1 == -1 && j1 == 0))
	{
		return 0;
	}
	if (ox[0] - oy[0] == ox[1] - oy[1] && abs(ox[0] - ox[1]) <= 4 && (i0 == -1 && j0 == -1 && i1 == -1 && j1 == -1))
	{
		return 0;
	}
	if (ox[0] + oy[0] == ox[1] + oy[1] && abs(ox[0] - ox[1]) <= 4 && (i0 == -1 && j0 == 1 && i1 == -1 && j1 == 1))
	{
		return 0;
	}

	if ((firstl == false || firstr == false) && (secondl == false || secondr == false))
	{
		return 0;
	}

	if (firstl == false || firstr == false)
	{
		if (l1 == 2)
		{
			if (showBoard(ox[1] + 4 * i1, oy[1] + 4 * j1) == 0)
			{
				if (showBoard(ox[1] - i1, oy[1] - j1) == 0)
				{
					x[0] = ox[1] - i1;
					y[0] = oy[1] - j1;
					return 1;
				}
			}
		}
		else if (l1 == 1)
		{
			if ((abs(lx1[0] - ox[1]) + abs(rx1[0] - ox[1] > 3)) || (abs(ly1[0] - oy[1]) + abs(ry1[0] - oy[1] > 3)))
			{
				return 0;
			}
			else
			{
				for (int c = 1; c < 5; c++)
				{
					if (showBoard(ox[1] - c * i1, oy[1] - c * j1) == 0)
					{
						x[0] = ox[1] - c * i1;
						y[0] = oy[1] - c * j1;
						return 1;
					}
					else if (showBoard(ox[1] + c * i1, oy[1] + c * j1) == 0)
					{
						x[0] = ox[1] + c * i1;
						y[0] = oy[1] + c * j1;
						return 1;
					}
				}
			}
		}
		else
		{
			if (showBoard(ox[1] - 4 * i1, oy[1] - 4 * j1) == 0)
			{
				if (showBoard(ox[1] + i1, oy[1] + j1) == 0)
				{
					x[0] = ox[1] + i1;
					y[0] = oy[1] + j1;
					return 1;
				}
			}
		}
		return 0;
	}
	else if (secondl == false || secondr == false)
	{
		if (l0 == 2)
		{
			if (showBoard(ox[0] + 4 * i0, oy[0] + 4 * j0) == 0)
			{
				if (showBoard(ox[0] - i0, oy[0] - j0) == 0)
				{
					x[0] = ox[0] - i0;
					y[0] = oy[0] - j0;
					return 1;
				}
			}
		}
		else if (l0 == 1)
		{
			if ((abs(lx0[0] - ox[0]) + abs(rx0[0] - ox[0] > 3)) || (abs(ly0[0] - oy[0]) + abs(ry0[0] - oy[0] > 3)))
			{
				return 0;
			}
			else
			{
				for (int c = 1; c < 5; c++)
				{
					if (showBoard(ox[0] - c * i0, oy[0] - c * j0) == 0)
					{
						x[0] = ox[0] - c * i0;
						y[0] = oy[0] - c * j0;
						return 1;
					}
					else if (showBoard(ox[0] + c * i0, oy[0] + c * j0) == 0)
					{
						x[0] = ox[0] + c * i0;
						y[0] = oy[0] + c * j0;
						return 1;
					}
				}
			}
		}
		else
		{
			if (showBoard(ox[0] - 4 * i0, oy[0] - 4 * j0) == 0)
			{
				if (showBoard(ox[0] + i0, oy[0] + j0) == 0)
				{
					x[0] = ox[0] + i0;
					y[0] = oy[0] + j0;
					return 1;
				}
			}
		}
		return 0;
	}

	int rv = 0;
	if (l0 == 2)
	{
		if (showBoard(ox[0] + 4 * i0, oy[0] + 4 * j0) == 0)
		{
			x[0] = ox[0] - i0;
			y[0] = oy[0] - j0;
			rv++;
		}
		if (l1 == 2)
		{
			if (showBoard(ox[1] + 4 * i1, oy[1] + 4 * j1) == 0)
			{
				x[rv] = ox[1] - i1;
				y[rv] = oy[1] - j1;
				rv++;
			}
		}
		else if (l1 == 1)
		{
			if ((abs(lx1[0] - ox[1]) + abs(rx1[0] - ox[1] > 3)) || (abs(ly1[0] - oy[1]) + abs(ry1[0] - oy[1] > 3)) == false)
			{
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[1] - c * i1, oy[1] - c * j1) == 0)
					{
						x[rv] = ox[1] - c * i1;
						y[rv] = oy[1] - c * j1;
						rv++;
						c = 4;
						break;
					}
					else if (showBoard(ox[1] + c * i1, oy[1] + c * j1) == 0)
					{
						x[rv] = ox[1] + c * i1;
						y[rv] = oy[1] + c * j1;
						rv++;
						c = 4;
						break;
					}
				}
			}
		}
		else
		{
			if (showBoard(ox[1] - 4 * i1, oy[1] - 4 * j1) == 0)
			{
				x[rv] = ox[1] + i1;
				y[rv] = oy[1] + j1;
				rv++;
			}
		}
		return rv;
	}
	else if (l0 == 1)
	{
		if ((abs(lx0[0] - ox[0]) >= 2 || abs(ly0[0] - oy[0] >= 2)) || (abs(rx0[0] - ox[0]) >= 2 || abs(ry0[0] - oy[0] >= 2)) == false)
		{
			for (int c = 1; c < 3; c++)
			{
				if (showBoard(ox[0] - c * i0, oy[0] - c * j0) == 0)
				{
					x[0] = ox[0] - c * i0;
					y[0] = oy[0] - c * j0;
					rv++;
					c = 4;
					break;
				}
				else if (showBoard(ox[0] + c * i0, oy[0] + c * j0) == 0)
				{
					x[0] = ox[0] + c * i0;
					y[0] = oy[0] + c * j0;
					rv++;
					c = 4;
					break;
				}
			}
		}
		if (l1 == 2)
		{
			if (showBoard(ox[1] + 4 * i1, oy[1] + 4 * j1) == 0)
			{
				x[rv] = ox[1] - i1;
				y[rv] = oy[1] - j1;
				rv++;
			}
		}
		else if (l1 == 1)
		{
			if ((abs(lx1[0] - ox[1]) + abs(rx1[0] - ox[1] > 3)) || (abs(ly1[0] - oy[1]) + abs(ry1[0] - oy[1] > 3)) == false)
			{
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[1] - c * i1, oy[1] - c * j1) == 0)
					{
						x[rv] = ox[1] - c * i1;
						y[rv] = oy[1] - c * j1;
						rv++;
						c = 4;
						break;
					}
					else if (showBoard(ox[1] + c * i1, oy[1] + c * j1) == 0)
					{
						x[rv] = ox[1] + c * i1;
						y[rv] = oy[1] + c * j1;
						rv++;
						c = 4;
						break;
					}
				}
			}
		}
		else
		{
			if (showBoard(ox[1] - 4 * i1, oy[1] - 4 * j1) == 0)
			{
				x[rv] = ox[1] + i1;
				y[rv] = oy[1] + j1;
				rv++;
			}
		}
		return rv;
	}
	else
	{
		if (showBoard(ox[0] - 4 * i0, oy[0] - 4 * j0) == 0)
		{
			x[0] = ox[0] + i0;
			y[0] = oy[0] + j0;
			rv++;
		}
		if (l1 == 2)
		{
			if (showBoard(ox[1] + 4 * i1, oy[1] + 4 * j1) == 0)
			{
				x[rv] = ox[1] - i1;
				y[rv] = oy[1] - j1;
				rv++;
			}
		}
		else if (l1 == 1)
		{
			if ((abs(lx1[0] - ox[1]) + abs(rx1[0] - ox[1] > 3)) || (abs(ly1[0] - oy[1]) + abs(ry1[0] - oy[1] > 3)) == false)
			{
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[1] - c * i1, oy[1] - c * j1) == 0)
					{
						x[rv] = ox[1] - c * i1;
						y[rv] = oy[1] - c * j1;
						rv++;
						c = 4;
						break;
					}
					else if (showBoard(ox[1] + c * i1, oy[1] + c * j1) == 0)
					{
						x[rv] = ox[1] + c * i1;
						y[rv] = oy[1] + c * j1;
						rv++;
						c = 4;
						break;
					}
				}
			}
		}
		else
		{
			if (showBoard(ox[1] - 4 * i1, oy[1] - 4 * j1) == 0)
			{
				x[rv] = ox[1] + i1;
				y[rv] = oy[1] + j1;
				rv++;
			}
		}
		return rv;
	}

	return 0;
}

void check(bool & left, bool & right, int & l, int & r, int lx[], int ly[], int rx[], int ry[], int my, int i, int j)
{
	for (int c = 1; c < 5; c++)
	{
		if (left && (showBoard(ox[my] + c * i, oy[my] + c * j) == 1 || showBoard(ox[my] + c * i, oy[my] + c * j) == -1)) //왼쪽이 이미 내 돌로 막혀있거나 범위 밖일 때
		{
			left = false;
		}
		if (right && (showBoard(ox[my] - c * i, oy[my] - c * j) == 1 || showBoard(ox[my] - c * i, oy[my] - c * j) == -1)) //오른쪽이 이미 내 돌로 막혀있거나 범위 밖일 때
		{
			right = false;
		}

		if (left && (showBoard(ox[my] + c * i, oy[my] + c * j) == 2 || showBoard(ox[my] + c * i, oy[my] + c * j) == 3)) //왼쪽에 상대 돌/블로킹 확인
		{
			lx[l] = ox[my] + c * i;
			ly[l] = oy[my] + c * j;
			l++;
		}
		if (right && (showBoard(ox[my] - c * i, oy[my] - c * j) == 2 || showBoard(ox[my] - c * i, oy[my] - c * j) == 3)) //오른쪽에 상대돌/블로킹 확인
		{
			rx[r] = ox[my] - c * i;
			ry[r] = oy[my] - c * j;
			r++;
		}
	}
}

int each(int x[], int y[], int my, int num)
{
	bool hl = true;		bool hr = true;
	bool vl = true;		bool vr = true;
	bool nwl = true;	bool nwr = true;
	bool nel = true;	bool ner = true;
	int hlx[4] = { -1, -1, -1, -1 };	int hly[4] = { -1, -1, -1, -1 };
	int hrx[4] = { -1, -1, -1, -1 };	int hry[4] = { -1, -1, -1, -1 };
	int vlx[4] = { -1, -1, -1, -1 };	int vly[4] = { -1, -1, -1, -1 };
	int vrx[4] = { -1, -1, -1, -1 };	int vry[4] = { -1, -1, -1, -1 };
	int nwlx[4] = { -1, -1, -1, -1 };	int nwly[4] = { -1, -1, -1, -1 };
	int nwrx[4] = { -1, -1, -1, -1 };	int nwry[4] = { -1, -1, -1, -1 };
	int nelx[4] = { -1, -1, -1, -1 };	int nely[4] = { -1, -1, -1, -1 };
	int nerx[4] = { -1, -1, -1, -1 };	int nery[4] = { -1, -1, -1, -1 };
	int Hl = 0;		int Hr = 0;
	int Vl = 0;		int Vr = 0;
	int Nwl = 0;	int Nwr = 0;
	int Nel = 0;	int Ner = 0;

	check(hl, hr, Hl, Hr, hlx, hly, hrx, hry, my, -1, 0);
	check(vl, vr, Vl, Vr, vlx, vly, vrx, vry, my, 0, -1);
	check(nwl, nwr, Nwl, Nwr, nwlx, nwly, nwrx, nwry, my, -1, -1);
	check(nel, ner, Nel, Ner, nelx, nely, nerx, nery, my, -1, 1);

	bool h = (hl == false && hr == false) || (Hl + Hr < 2);
	bool v = (vl == false && vr == false) || (Vl + Vr < 2);
	bool nw = (nwl == false && nwr == false) || (Nwl + Nwr < 2);
	bool ne = (nel == false && ner == false) || (Nel + Ner < 2);

	int hxx = 0;	int hyy = 0;
	int hii = 0;	int hjj = 0;
	int vxx = 0;	int vyy = 0;
	int vii = 0;	int vjj = 0;
	int nwxx = 0;	int nwyy = 0;
	int nwii = 0;	int nwjj = 0;
	int nexx = 0;	int neyy = 0;
	int neii = 0;	int nejj = 0;
	if (Hl == 2)
	{
		hxx = abs(hlx[0] - ox[my]) + abs(hlx[1] - ox[my]);
		hyy = abs(hly[0] - oy[my]) + abs(hly[1] - oy[my]);
	}
	if (Hl == 1 && Hr == 1)
	{
		hxx = abs(hlx[0] - ox[my]) + abs(hrx[0] - ox[my]);
		hyy = abs(hly[0] - oy[my]) + abs(hry[0] - oy[my]);
	}
	if (Hr == 2)
	{
		hxx = abs(hrx[0] - ox[my]) + abs(hrx[1] - ox[my]);
		hyy = abs(hry[0] - oy[my]) + abs(hry[1] - oy[my]);
	}
	if (Vl == 2)
	{
		vxx = abs(vlx[0] - ox[my]) + abs(vlx[1] - ox[my]);
		vyy = abs(vly[0] - oy[my]) + abs(vly[1] - oy[my]);
	}
	if (Vl == 1 && Vr == 1)
	{
		vxx = abs(vlx[0] - ox[my]) + abs(vrx[0] - ox[my]);
		vyy = abs(vly[0] - oy[my]) + abs(vry[0] - oy[my]);
	}
	if (Vr == 2)
	{
		vxx = abs(vrx[0] - ox[my]) + abs(vrx[1] - ox[my]);
		vyy = abs(vry[0] - oy[my]) + abs(vry[1] - oy[my]);
	}
	if (Nwl == 2)
	{
		nwxx = abs(nwlx[0] - ox[my]) + abs(nwlx[1] - ox[my]);
		nwyy = abs(nwly[0] - oy[my]) + abs(nwly[1] - oy[my]);
	}
	if (Nwl == 1 && Nwr == 1)
	{
		nwxx = abs(nwlx[0] - ox[my]) + abs(nwrx[0] - ox[my]);
		nwyy = abs(nwly[0] - oy[my]) + abs(nwry[0] - oy[my]);
	}
	if (Nwr == 2)
	{
		nwxx = abs(nwrx[0] - ox[my]) + abs(nwrx[1] - ox[my]);
		nwyy = abs(nwry[0] - oy[my]) + abs(nwry[1] - oy[my]);
	}
	if (Nel == 2)
	{
		nexx = abs(nelx[0] - ox[my]) + abs(nelx[1] - ox[my]);
		neyy = abs(nely[0] - oy[my]) + abs(nely[1] - oy[my]);
	}
	if (Nel == 1 && Ner == 1)
	{
		nexx = abs(nelx[0] - ox[my]) + abs(nerx[0] - ox[my]);
		neyy = abs(nely[0] - oy[my]) + abs(nery[0] - oy[my]);
	}
	if (Ner == 2)
	{
		nexx = abs(nerx[0] - ox[my]) + abs(nerx[1] - ox[my]);
		neyy = abs(nery[0] - oy[my]) + abs(nery[1] - oy[my]);
	}

	if (h && v && nw && ne)
	{
		return 0;
	}
	else if ((h && v && nw) || (h && v && ne) || (h && nw && ne) || (v && nw && ne))
	{
		return 0;
	}
	else if (h && v) //nw ne
	{
		if (nwxx > 3 || nwyy > 3)
		{
			if (nexx > 3 || neyy > 3)
			{
				return 0;
			}
			else
			{
				if (nel == false || ner == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] + c, oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my] - c, oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if (nexx > 3 || neyy > 3)
			{
				if (nwl == false || nwr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my] + c, oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
			else
			{
				if ((nel == false || ner == false) && (nwl == false || nwr == false))
				{
					return 0;
				}
				if (nel == false || ner == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my] - c;
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my] + c;
								return 1;
							}
						}
					}
				}
				if (nwl == false || nwr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my] + c;
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my] - c;
								return 1;
							}
						}
					}
				}
				if (num == 1)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] - c) == 0)
					{
						x[0] = ox[my] - c;
						y[0] = oy[my] - c;
						break;
					}
					else if (showBoard(ox[my] + c, oy[my] + c) == 0)
					{
						x[0] = ox[my] + c;
						y[0] = oy[my] + c;
						break;
					}
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] + c) == 0)
					{
						x[1] = ox[my] - c;
						y[1] = oy[my] + c;
						return 2;
					}
					else if (showBoard(ox[my] + c, oy[my] - c) == 0)
					{
						x[1] = ox[my] + c;
						y[1] = oy[my] - c;
						return 2;
					}
				}
			}
		}
	}
	else if (h && nw) // v ne
	{
		if (vxx > 3 || vyy > 3)
		{
			if (nexx > 3 || neyy > 3)
			{
				return 0;
			}
			else
			{
				if (nel == false || ner == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] + c, oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my] - c, oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if (nexx > 3 || neyy > 3)
			{
				if (vl == false || vr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my], oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my];
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my], oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my];
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
			else
			{
				if ((vl == false || vr == false) && (nel == false || ner == false))
				{
					return 0;
				}
				if (vl == false || vr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] + c, oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my] - c;
								return 1;
							}
						}
						else if (showBoard(ox[my] - c, oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my] + c;
								return 1;
							}
						}
					}
				}
				if (nel == false || ner == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my], oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my];
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my];
								y[1] = oy[my] + c;
								return 1;
							}
						}
						else if (showBoard(ox[my], oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my];
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my];
								y[1] = oy[my] - c;
								return 1;
							}
						}
					}
				}
				if (num == 1)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my], oy[my] - c) == 0)
					{
						x[0] = ox[my];
						y[0] = oy[my] - c;
						break;
					}
					else if (showBoard(ox[my], oy[my] + c) == 0)
					{
						x[0] = ox[my];
						y[0] = oy[my] + c;
						break;
					}
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] + c) == 0)
					{
						x[1] = ox[my] - c;
						y[1] = oy[my] + c;
						return 2;
					}
					else if (showBoard(ox[my] + c, oy[my] - c) == 0)
					{
						x[1] = ox[my] + c;
						y[1] = oy[my] - c;
						return 2;
					}
				}
			}
		}
	}
	else if (h && ne) //v nw
	{
		if (vxx > 3 || vyy > 3)
		{
			if (nwxx > 3 || nwyy > 3)
			{
				return 0;
			}
			else
			{
				if (nwl == false || nwr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my] + c, oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if (nwxx > 3 || nwyy > 3)
			{
				if (vl == false || vr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my], oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my];
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my], oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my];
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
			else
			{
				if ((vl == false || vr == false) && (nwl == false || nwr == false))
				{
					return 0;
				}
				if (vl == false || vr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my] - c;
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my] + c;
								return 1;
							}
						}
					}
				}
				if (nwl == false || nwr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my], oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my];
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my];
								y[1] = oy[my] + c;
								return 1;
							}
						}
						else if (showBoard(ox[my], oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my];
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my];
								y[1] = oy[my] - c;
								return 1;
							}
						}
					}
				}
				if (num == 1)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] - c) == 0)
					{
						x[0] = ox[my] - c;
						y[0] = oy[my] - c;
						break;
					}
					else if (showBoard(ox[my] + c, oy[my] + c) == 0)
					{
						x[0] = ox[my] + c;
						y[0] = oy[my] + c;
						break;
					}
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my], oy[my] + c) == 0)
					{
						x[1] = ox[my];
						y[1] = oy[my] + c;
						return 2;
					}
					else if (showBoard(ox[my], oy[my] - c) == 0)
					{
						x[1] = ox[my];
						y[1] = oy[my] - c;
						return 2;
					}
				}
			}
		}
	}
	else if (v && nw) //h ne
	{
		if (hxx > 3 || hyy > 3)
		{
			if (nexx > 3 || neyy > 3)
			{
				return 0;
			}
			else
			{
				if (nel == false || ner == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] + c, oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my] - c, oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if (nexx > 3 || neyy > 3)
			{
				if (hl == false || hr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my];
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my];
							return 1;
						}
					}
					else if (showBoard(ox[my] + c, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my];
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my];
							return 1;
						}
					}
				}
			}
			else
			{
				if ((hl == false || hr == false) && (nel == false || ner == false))
				{
					return 0;
				}
				if (hl == false || hr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] + c, oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my] - c;
								return 1;
							}
						}
						else if (showBoard(ox[my] - c, oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my] + c;
								return 1;
							}
						}
					}
				}
				if (nel == false || ner == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my]) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my];
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my];
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my]) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my];
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my];
								return 1;
							}
						}
					}
				}
				if (num == 1)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my]) == 0)
					{
						x[0] = ox[my] - c;
						y[0] = oy[my];
						break;
					}
					else if (showBoard(ox[my] + c, oy[my]) == 0)
					{
						x[0] = ox[my] + c;
						y[0] = oy[my];
						break;
					}
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] + c) == 0)
					{
						x[1] = ox[my] - c;
						y[1] = oy[my] + c;
						return 2;
					}
					else if (showBoard(ox[my] + c, oy[my] - c) == 0)
					{
						x[1] = ox[my] + c;
						y[1] = oy[my] - c;
						return 2;
					}
				}
			}
		}
	}
	else if (v && ne) //h nw
	{
		if (hxx > 3 || hyy > 3)
		{
			if (nwxx > 3 || nwyy > 3)
			{
				return 0;
			}
			else
			{
				if (nwl == false || nwr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] + c, oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my] + c;
							return 1;
						}
					}
					else if (showBoard(ox[my] - c, oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my] - c;
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if (nwxx > 3 || nwyy > 3)
			{
				if (hl == false || hr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my];
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my];
							return 1;
						}
					}
					else if (showBoard(ox[my] + c, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my];
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my];
							return 1;
						}
					}
				}
			}
			else
			{
				if ((hl == false || hr == false) && (nwl == false || nwr == false))
				{
					return 0;
				}
				if (hl == false || hr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my] - c;
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my] + c;
								return 1;
							}
						}
					}
				}
				if (nwl == false || nwr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my]) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my];
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my];
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my]) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my];
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my];
								return 1;
							}
						}
					}
				}
				if (num == 1)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my] - c) == 0)
					{
						x[0] = ox[my] - c;
						y[0] = oy[my] - c;
						break;
					}
					else if (showBoard(ox[my] + c, oy[my] + c) == 0)
					{
						x[0] = ox[my] + c;
						y[0] = oy[my] + c;
						break;
					}
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my]) == 0)
					{
						x[1] = ox[my] - c;
						y[1] = oy[my];
						return 2;
					}
					else if (showBoard(ox[my] + c, oy[my]) == 0)
					{
						x[1] = ox[my] + c;
						y[1] = oy[my];
						return 2;
					}
				}
			}
		}
	}
	else if (nw && ne) //h v
	{
		if (hxx > 3 || hyy > 3)
		{
			if (vxx > 3 || vyy > 3)
			{
				return 0;
			}
			else
			{
				if (vl == false || vr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my], oy[my] - c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] - c;
							return 1;
						}
						else
						{
							x[1] = ox[my];
							y[1] = oy[my] - c;
							return 1;
						}
					}
					else if (showBoard(ox[my], oy[my] + c) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my];
							y[0] = oy[my] + c;
							return 1;
						}
						else
						{
							x[1] = ox[my];
							y[1] = oy[my] + c;
							return 1;
						}
					}
				}
			}
		}
		else
		{
			if (vxx > 3 || vyy > 3)
			{
				if (hl == false || hr == false)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] - c;
							y[0] = oy[my];
							return 1;
						}
						else
						{
							x[1] = ox[my] - c;
							y[1] = oy[my];
							return 1;
						}
					}
					else if (showBoard(ox[my] + c, oy[my]) == 0)
					{
						if (num == 0)
						{
							x[0] = ox[my] + c;
							y[0] = oy[my];
							return 1;
						}
						else
						{
							x[1] = ox[my] + c;
							y[1] = oy[my];
							return 1;
						}
					}
				}
			}
			else
			{
				if ((hl == false || hr == false) && (vl == false || vr == false))
				{
					return 0;
				}
				if (hl == false || hr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my] - c, oy[my]) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] - c;
								y[0] = oy[my];
								return 1;
							}
							else
							{
								x[1] = ox[my] - c;
								y[1] = oy[my];
								return 1;
							}
						}
						else if (showBoard(ox[my] + c, oy[my]) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my] + c;
								y[0] = oy[my];
								return 1;
							}
							else
							{
								x[1] = ox[my] + c;
								y[1] = oy[my];
								return 1;
							}
						}
					}
				}
				if (vl == false || vr == false)
				{
					for (int c = 1; c < 3; c++)
					{
						if (showBoard(ox[my], oy[my] + c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my];
								y[0] = oy[my] + c;
								return 1;
							}
							else
							{
								x[1] = ox[my];
								y[1] = oy[my] + c;
								return 1;
							}
						}
						else if (showBoard(ox[my], oy[my] - c) == 0)
						{
							if (num == 0)
							{
								x[0] = ox[my];
								y[0] = oy[my] - c;
								return 1;
							}
							else
							{
								x[1] = ox[my];
								y[1] = oy[my] - c;
								return 1;
							}
						}
					}
				}
				if (num == 1)
				{
					return 0;
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my] - c, oy[my]) == 0)
					{
						x[0] = ox[my] - c;
						y[0] = oy[my];
						break;
					}
					else if (showBoard(ox[my] + c, oy[my]) == 0)
					{
						x[0] = ox[my] + c;
						y[0] = oy[my];
						break;
					}
				}
				for (int c = 1; c < 3; c++)
				{
					if (showBoard(ox[my], oy[my] + c) == 0)
					{
						x[1] = ox[my];
						y[1] = oy[my] + c;
						return 2;
					}
					else if (showBoard(ox[my], oy[my] - c) == 0)
					{
						x[1] = ox[my];
						y[1] = oy[my] - c;
						return 2;
					}
				}
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

int attack(int x[], int y[], int d, int m)
{
	int cx[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int cy[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	int c[2] = { -2, -2 };
	for (int i = 0; i < 8; i++)
	{
		if (showBoard(mx[m] + cx[i], my[m] + cy[i]) == 0)
		{
			if (c[0] == -2)
			{
				c[0] = i;
			}
			else
			{
				c[1] = i;
				break;
			}
		}
	}
	if (c[0] == -2)
	{
		return 0;
	}
	else
	{
		if (c[1] == -2)
		{
			if (d == 0)
			{
				x[0] = mx[m] + cx[c[0]];
				y[0] = my[m] + cy[c[0]];
				return 1;
			}
			else
			{
				if (x[0] == mx[m] + cx[c[0]] && y[0] == my[m] + cy[c[0]])
				{
					return 0;
				}
				x[1] = mx[m] + cx[c[0]];
				y[1] = my[m] + cy[c[0]];
				return 1;
			}
		}
		else
		{
			if (d == 0)
			{
				x[0] = mx[m] + cx[c[0]];
				y[0] = my[m] + cy[c[0]];
				x[1] = mx[m] + cx[c[1]];
				y[1] = my[m] + cy[c[1]];
				return 2;
			}
			else
			{
				if (x[0] == mx[m] + cx[c[0]] && y[0] == my[m] + cy[c[0]])
				{
					return 0;
				}
				x[1] = mx[m] + cx[c[0]];
				y[1] = my[m] + cy[c[0]];
				return 1;
			}
		}
	}
}

int allsearch(int x[], int y[], int num)
{
	//가로
	int ex[6] = { -1, -1, -1, -1, -1, -1 };
	int ey[6] = { -1, -1, -1, -1, -1, -1 };
	int empty = 0;
	bool e = false;
	int i = 0; int j = 0; int h = 0;
	for (h = 0; h < 19; h++)
	{
		for (i = 0; i < 14; i++)
		{
			for (j = i; j < i + 6; j++)
			{
				if (showBoard(j, h) == 2)
				{
					e = true;
					break;
				}
				else if (showBoard(j, h) == 0)
				{
					ex[empty] = j;
					ey[empty] = h;
					empty++;
				}
			}
			if (!e)
			{
				if (empty == 2)
				{
					if (num == 0)
					{
						x[0] = ex[0];
						y[0] = ey[0];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[1] && y[0] == ey[1])
						{
							break;
						}
						else
						{
							x[1] = ex[1];
							y[1] = ey[1];
							return 1;
						}
					}
				}
				else if (empty == 1)
				{
					if (showBoard(j + 1, h) == 1 || showBoard(j - 6, h) == 1)
					{
						i++;
					}
					else
					{
						if (num == 0)
						{
							x[0] = ex[0];
							y[0] = ey[0];
							return 1;
						}
						else
						{
							if (x[0] == ex[0] && y[0] == ey[0])
							{
								break;
							}
							else
							{
								x[1] = ex[0];
								y[1] = ey[0];
								return 1;
							}
						}
					}
				}
				else if (empty == 3)
				{
					if (num == 0)
					{
						x[0] = ex[2];
						y[0] = ey[2];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[2] && y[0] == ey[2])
						{
							break;
						}
						else
						{
							x[1] = ex[2];
							y[1] = ey[2];
							return 1;
						}
					}
				}
			}
			e = false;
			empty = 0;
		}
	}

	//세로
	for (int idx = 0; idx < 6; idx++)
	{
		ex[idx] = -1;
		ey[idx] = -1;
	}
	empty = 0;
	e = false;
	i = 0; j = 0; h = 0;
	for (h = 0; h < 19; h++)
	{
		for (i = 0; i < 14; i++)
		{
			for (j = i; j < i + 6; j++)
			{
				if (showBoard(h, j) == 2)
				{
					e = true;
					break;
				}
				else if (showBoard(h, j) == 0)
				{
					ex[empty] = h;
					ey[empty] = j;
					empty++;
				}
			}
			if (!e)
			{
				if (empty == 2)
				{
					if (num == 0)
					{
						x[0] = ex[0];
						y[0] = ey[0];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[1] && y[0] == ey[1])
						{
							break;
						}
						else
						{
							x[1] = ex[1];
							y[1] = ey[1];
							return 1;
						}
					}
				}
				else if (empty == 1)
				{
					if (showBoard(h, j + 1) == 1 || showBoard(h, j - 6) == 1)
					{
						i++;
					}
					else
					{
						if (num == 0)
						{
							x[0] = ex[0];
							y[0] = ey[0];
							return 1;
						}
						else
						{
							if (x[0] == ex[0] && y[0] == ey[0])
							{
								break;
							}
							else
							{
								x[1] = ex[0];
								y[1] = ey[0];
								return 1;
							}
						}
					}
				}
				else if (empty == 3)
				{
					if (num == 0)
					{
						x[0] = ex[2];
						y[0] = ey[2];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[2] && y[0] == ey[2])
						{
							break;
						}
						else
						{
							x[1] = ex[2];
							y[1] = ey[2];
							return 1;
						}
					}
				}
			}
			e = false;
			empty = 0;
		}
	}

	//ne -> sw
	for (int idx = 0; idx < 6; idx++)
	{
		ex[idx] = -1;
		ey[idx] = -1;
	}
	empty = 0;
	e = false;
	for (int h = 5; h <= 18; h++)
	{
		for (int i = 0; i <= 5 - h; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (showBoard(h - i - j, i + j) == 2)
				{
					e = true;
					break;
				}
				else if (showBoard(h - i - j, i + j) == 0)
				{
					ex[empty] = h - i - j;
					ey[empty] = i + j;
					empty++;
				}
			}
			if (!e)
			{
				if (empty == 2)
				{
					if (num == 0)
					{
						x[0] = ex[0];
						y[0] = ey[0];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[1] && y[0] == ey[1])
						{
							break;
						}
						else
						{
							x[1] = ex[1];
							y[1] = ey[1];
							return 1;
						}
					}
				}
				else if (empty == 1)
				{
					if (showBoard(h - i - j - 1, i + j + 1) == 1 || showBoard(h - i - j + 6, i + j - 6))
					{
						i++;
					}
					else
					{
						if (num == 0)
						{
							x[0] = ex[0];
							y[0] = ey[0];
							return 1;
						}
						else
						{
							if (x[0] == ex[0] && y[0] == ey[0])
							{
								break;
							}
							else
							{
								x[1] = ex[0];
								y[1] = ey[0];
								return 1;
							}
						}
					}
				}
				else if (empty == 3)
				{
					if (num == 0)
					{
						x[0] = ex[2];
						y[0] = ey[2];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[2] && y[0] == ey[2])
						{
							break;
						}
						else
						{
							x[1] = ex[2];
							y[1] = ey[2];
							return 1;
						}
					}
				}
			}
			e = false;
			empty = 0;
		}
	}
	for (int idx = 0; idx < 6; idx++)
	{
		ex[idx] = -1;
		ey[idx] = -1;
	}
	empty = 0;
	e = false;
	for (int h = 19; h <= 31; h++)
	{
		for (int i = h - 18; i <= 13; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (showBoard(h - i - j, i + j) == 2)
				{
					e = true;
					break;
				}
				else if (showBoard(h - i - j, i + j) == 0)
				{
					ex[empty] = h - i - j;
					ey[empty] = i + j;
					empty++;
				}
			}
			if (!e)
			{
				if (empty == 2)
				{
					if (num == 0)
					{
						x[0] = ex[0];
						y[0] = ey[0];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[1] && y[0] == ey[1])
						{
							break;
						}
						else
						{
							x[1] = ex[1];
							y[1] = ey[1];
							return 1;
						}
					}
				}
				else if (empty == 1)
				{
					if (showBoard(h - i - j - 1, i + j + 1) == 1 || showBoard(h - i - j + 6, i + j - 6))
					{
						i++;
					}
					else
					{
						if (num == 0)
						{
							x[0] = ex[0];
							y[0] = ey[0];
							return 1;
						}
						else
						{
							if (x[0] == ex[0] && y[0] == ey[0])
							{
								break;
							}
							else
							{
								x[1] = ex[0];
								y[1] = ey[0];
								return 1;
							}
						}
					}
				}
				else if (empty == 3)
				{
					if (num == 0)
					{
						x[0] = ex[2];
						y[0] = ey[2];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[2] && y[0] == ey[2])
						{
							break;
						}
						else
						{
							x[1] = ex[2];
							y[1] = ey[2];
							return 1;
						}
					}
				}
			}
			e = false;
			empty = 0;
		}
	}

	//nw -> se
	for (int idx = 0; idx < 6; idx++)
	{
		ex[idx] = -1;
		ey[idx] = -1;
	}
	empty = 0;
	e = false;
	for (int h = 0; h <= 13; h++)
	{
		for (int i = 0; i <= 13 - h; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (showBoard(h + i + j, i + j) == 2)
				{
					e = true;
					break;
				}
				else if (showBoard(h + i + j, i + j) == 0)
				{
					ex[empty] = h + i + j;
					ey[empty] = i + j;
					empty++;
				}
			}
			if (!e)
			{
				if (empty == 2)
				{
					if (num == 0)
					{
						x[0] = ex[0];
						y[0] = ey[0];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[1] && y[0] == ey[1])
						{
							break;
						}
						else
						{
							x[1] = ex[1];
							y[1] = ey[1];
							return 1;
						}
					}
				}
				else if (empty == 1)
				{
					if (showBoard(h + i + j + 1, i + j + 1) == 1 || showBoard(h + i + j - 6, i + j - 6) == 1)
					{
						i++;
					}
					else
					{
						if (num == 0)
						{
							x[0] = ex[0];
							y[0] = ey[0];
							return 1;
						}
						else
						{
							if (x[0] == ex[0] && y[0] == ey[0])
							{
								break;
							}
							else
							{
								x[1] = ex[0];
								y[1] = ey[0];
								return 1;
							}
						}
					}
				}
				else if (empty == 3)
				{
					if (num == 0)
					{
						x[0] = ex[2];
						y[0] = ey[2];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[2] && y[0] == ey[2])
						{
							break;
						}
						else
						{
							x[1] = ex[2];
							y[1] = ey[2];
							return 1;
						}
					}
				}
			}
			e = false;
			empty = 0;
		}
	}
	for (int idx = 0; idx < 6; idx++)
	{
		ex[idx] = -1;
		ey[idx] = -1;
	}
	empty = 0;
	e = false;
	for (int h = 1; h <= 13; h++)
	{
		for (int i = 0; i <= 13 - h; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (showBoard(i + j, h + i + j) == 2)
				{
					e = true;
					break;
				}
				else if (showBoard(i + j, h + i + j) == 0)
				{
					ex[empty] = i + j;
					ey[empty] = h + i + j;
					empty++;
				}
			}
			if (!e)
			{
				if (empty == 2)
				{
					if (num == 0)
					{
						x[0] = ex[0];
						y[0] = ey[0];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[1] && y[0] == ey[1])
						{
							break;
						}
						else
						{
							x[1] = ex[1];
							y[1] = ey[1];
							return 1;
						}
					}
				}
				else if (empty == 1)
				{
					if (showBoard(i + j + 1, h + i + j + 1) == 1 || showBoard(i + j - 6, h + i + j - 6) == 1)
					{
						i++;
					}
					else
					{
						if (num == 0)
						{
							x[0] = ex[0];
							y[0] = ey[0];
							return 1;
						}
						else
						{
							if (x[0] == ex[0] && y[0] == ey[0])
							{
								break;
							}
							else
							{
								x[1] = ex[0];
								y[1] = ey[0];
								return 1;
							}
						}
					}
				}
				else if (empty == 3)
				{
					if (num == 0)
					{
						x[0] = ex[2];
						y[0] = ey[2];
						x[1] = ex[1];
						y[1] = ey[1];
						return 2;
					}
					else
					{
						if (x[0] == ex[2] && y[0] == ey[2])
						{
							break;
						}
						else
						{
							x[1] = ex[2];
							y[1] = ey[2];
							return 1;
						}
					}
				}
			}
			e = false;
			empty = 0;
		}
	}

	return 0;
}