#include <stdio.h>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

int nfiled[51][51];
int arrx[52][52];
int arry[52][52];
int castle_room[52];
int x, y;

typedef struct pos{
	int nx, ny;
};


int total_castle, castle_size, max_castle_size;


int dirx[] = { 1, 0, -1, 0 }; // 동 북 서 남
int diry[] = { 0, -1, 0, 1 };


void bfs(){

	queue <pos> bfsq;
	pos cur = { 0, 0 };
	pos next = { 0, 0 };
	int nvisit[51][51] = { 0, 0, };
	int max_count = 0;
	int count = 0;
	int castle_num = 1;
	
	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++){
			if (!nvisit[i][j])
			{
				bfsq.push({ j, i });
				nvisit[i][j] = castle_num;
				count = 1;

				while (!bfsq.empty())
				{
					cur = bfsq.front();
					bfsq.pop();

					for (int k = 0; k < 4; k++)
					{
						next.nx = cur.nx + dirx[k];
						next.ny = cur.ny + diry[k];

						if (next.nx < 0 || next.nx >= x || next.ny < 0 || next.ny >= y) continue;

						if (k == 0){
							if (arry[cur.ny][cur.nx + 1]) continue;
						}
						else if (k == 1){
							if (arrx[cur.ny][cur.nx]) continue;
						}
						else if (k == 2){
							if (arry[cur.ny][cur.nx]) continue;
						}
						else if (k == 3){
							if (arrx[cur.ny + 1][cur.nx]) continue;
						}

						if (nvisit[next.ny][next.nx] == 0){

							nvisit[next.ny][next.nx] = castle_num;
							bfsq.push(next);
							count++;

						}
					}
				}
				castle_room[castle_num] = count;
				castle_num++;

				if (max_count < count)
					max_count = count;


			}
		}
	}


	int pre_num = 0;
	int cur_num = 0;

	vector <pair<int, int> > tem_vec;


	for (int i = 0; i < y; i++){
		pre_num = 0;
		for (int j = 0; j < x; j++){
			cur_num = nvisit[i][j];
			if (cur_num != pre_num && pre_num != 0)
			{
				tem_vec.push_back(make_pair(pre_num, cur_num));
			}
			pre_num = cur_num;
		}
	}

	for (int i = 0; i < x; i++){
		pre_num = 0;
		for (int j = 0; j < y; j++){
			cur_num = nvisit[j][i];
			if (cur_num != pre_num && pre_num != 0)
			{
				tem_vec.push_back(make_pair(pre_num, cur_num));
			}
			pre_num = cur_num;
		}
	}

	int max_room = 0;
	int room = 0;

	for (int i = 0; i < tem_vec.size(); i++)
	{
		room = castle_room[tem_vec[i].first] + castle_room[tem_vec[i].second];
		if (max_room < room)
			max_room = room;

	}

	total_castle = castle_num - 1;
	castle_size = max_count;
	max_castle_size = max_room;

}



int main()
{
	scanf("%d %d", &x, &y);

	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++){
			scanf("%d", &nfiled[i][j]);


			switch (nfiled[i][j])
			{
			//0개
			case 0:	
				break;
			//1개
			case 1:		arry[i][j] = 1;	break;
			case 2:		arrx[i][j] = 1;	break;
			case 4:		arry[i][j + 1] = 1;	break;
			case 8:		arrx[i + 1][j] = 1;	break;
			//2개
			case 3:		arry[i][j] = 1;		arrx[i][j] = 1;	break;
			case 5:		arry[i][j] = 1;		arry[i][j + 1] = 1; break;
			case 9:		arry[i][j] = 1;		arrx[i + 1][j] = 1; break;
			case 6:		arrx[i][j] = 1;		arry[i][j + 1] = 1;	break;
			case 10:	arrx[i][j] = 1;		arrx[i + 1][j] = 1; break;
			case 12:	arry[i][j + 1] = 1;		arrx[i + 1][j] = 1; break;
			//3개
			case 7:		arry[i][j] = 1; arrx[i][j] = 1; arry[i][j + 1] = 1; break;
			case 11:	arry[i][j] = 1; arrx[i][j] = 1; arrx[i + 1][j] = 1;	break;
			case 13:	arry[i][j] = 1; arry[i][j + 1] = 1; arrx[i + 1][j] = 1;	break;
			case 14:	arrx[i][j] = 1; arry[i][j + 1] = 1; arrx[i + 1][j] = 1; break;
			//4개
			case 15:	arry[i][j] = 1; arrx[i][j] = 1; arry[i][j + 1] = 1; arrx[i + 1][j] = 1; break;
			}
		}
	}

	bfs();

	printf("%d\n%d\n%d\n", total_castle, castle_size, max_castle_size);

	

	return 0;
}