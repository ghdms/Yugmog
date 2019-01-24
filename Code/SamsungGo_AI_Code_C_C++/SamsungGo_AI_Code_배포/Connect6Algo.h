// Samsung Go Tournament Form C Connect6Algo Header (g++-4.8.3)

// <--------------- 이 Code를 수정하면  작동하지 않을 수 있습니다 ------------------>

#pragma once
extern int width, height;
extern int terminateAI;
extern int blockx[10];
extern int blocky[10];
extern int block_num;
extern int ox[2];
extern int oy[2];
extern int mx[2];
extern int my[2];
extern unsigned s_time;

extern FILE *fp;


extern int isFree(int x, int y);
extern int showBoard(int x, int y);
extern void init();
extern void restart();
extern void mymove(int x[], int y[], int cnt = 2);
extern void opmove(int x[], int y[], int cnt = 2);
extern void block(int, int);
extern int setLine(char *fmt, ...);
extern void domymove(int x[], int y[], int cnt = 2);
extern void writeLog(char *log);

void myturn(int cnt = 2);
void example_random(int x[], int y[], int cnt);
void first(int x[], int y[]);
int attack(int x[], int y[], int d, int m);
int defense(int x[], int y[], int num, int my);
int defense_v(int x[], int y[], int num, int my);
int defense_nw(int x[], int y[], int num, int my);
int defense_ne(int x[], int y[], int num, int my);
int defended(bool lc, bool rc, int x[], int y[], int lempty, int rempty, int i, int j, int mode, int num, int ex, int ey, int opnum, int my);
int next_de(int x[], int y[], int mode, int num, int my);
int last_defense(int x[], int y[]);
int each(int x[], int y[], int my, int num);
void check(bool & left, bool & right, int & l, int & r, int lx[], int ly[], int rx[], int ry[], int my, int i, int j);

int allsearch(int x[], int y[], int num);

char info[];