#include <iostream>
#include <vector>

using namespace std;

int dir[4][2] = { {1,1},{-1,1}, {-1,-1}, {1,-1} };
int map[20][20];
bool visit[101];
int N, res;

bool range(int x, int y)
{
	if (0 <= x && x < N && 0 <= y && y < N && visit[map[x][y]] == false)
		return true;
	return false;
}

void dfs(int x, int y, int rd, int ru, int stat)
{
	//cout << " 현재 좌표 : " << x << " , " << y << endl;
	if (stat == 1) {
		int dir_x = x + dir[0][0];
		int dir_y = y + dir[0][1];

		if (range(dir_x, dir_y)) {
			visit[map[dir_x][dir_y]] = true;
			dfs(dir_x, dir_y, rd + 1, ru, 1);
			visit[map[dir_x][dir_y]] = false;
		}
		
		if (rd == 0)
			return;
		else {
			dfs(x, y, rd, ru, 2);
		}
	}
	else if (stat == 2) {
		int dir_x = x + dir[1][0];
		int dir_y = y + dir[1][1];

		if (range(dir_x, dir_y)) {
			visit[map[dir_x][dir_y]] = true;
			dfs(dir_x, dir_y, rd, ru + 1, 2);
			visit[map[dir_x][dir_y]] = false;
		}
		
		if (ru == 0)
			return;
		else {
			dfs(x, y, rd, ru, 3);
		}
	}
	else if (stat == 3) {
		int dir_x = x + dir[2][0];
		int dir_y = y + dir[2][1];

		if (rd == 0) {
			dfs(x, y, rd, ru, 4);
		}
		else if (range(dir_x, dir_y)) {
			visit[map[dir_x][dir_y]] = true;
			dfs(dir_x, dir_y, rd-1, ru, 3);
			visit[map[dir_x][dir_y]] = false;
		}
		else {
			return;
		}
	}
	else if (stat == 4) {
		int dir_x = x + dir[3][0];
		int dir_y = y + dir[3][1];

		if (ru == 1) {
			int cnt = 0;
			for (int i = 0; i < 101; i++) {
				if (visit[i] == true)
					cnt++;
			}
			if (res < cnt){
				res = cnt;
				//cout << "res값 갱신 : " << res << endl;
			}
			return;
		}
		else if (range(dir_x, dir_y)) {
			visit[map[dir_x][dir_y]] = true;
			dfs(dir_x, dir_y, rd, ru-1, 3);
			visit[map[dir_x][dir_y]] = false;
		}
		else {
			return;
		}
	}
}

int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		cin >> N;
		res = -1;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> map[i][j];
			}
		}

		for (int i = 1; i < N - 1; i++) {
			for (int j = 0; j < N - 2; j++) {
				visit[map[i][j]] = true;
				dfs(i, j, 0, 0, 1);
				visit[map[i][j]] = false;
			}
		}

		cout << "#" << tc << ' ' << res << endl;
	}
	return 0 ;
}