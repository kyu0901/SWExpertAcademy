#include <iostream>
#include <queue>

using namespace std;

int Map[50][50];
bool visit[50][50];
int dir[4][2] = { {1,0}, {0,1}, {-1,0} , {0,-1} };
int N, M, R, C, L, res;

void init()
{
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			visit[i][j] = false;
			Map[i][j] = 0;
		}
	}
}

bool range(int x, int y)
{
	if (0 <= x && x < N && 0 <= y && y < M && visit[x][y] == false){
		//visit[x][y] = true;
		return true;
	}
	return false;
}

void bfs()
{
	queue<pair<int, int> >q;
	res++;

	q.push(make_pair(R, C));
	int cnt = 0;
	int q_size;
	while (!q.empty()) {
		
		cnt++;
		q_size = q.size();
		if (cnt == L)
			break;


		while (q_size--) {

			int x = q.front().first;
			int y = q.front().second;
			visit[x][y] = true;

			//cout << "ÁÂÇ¥ : " << x << ", " << y << endl;

			q.pop();

			for (int i = 0; i < 4; i++) {
				int dir_x = x + dir[i][0];
				int dir_y = y + dir[i][1];

				if (range(dir_x, dir_y) == false)
					continue;

				if (i == 0) {
					if ((Map[x][y] == 1 || Map[x][y] == 2 || Map[x][y] == 5 || Map[x][y] == 6) && 
						(Map[dir_x][dir_y] == 1 || Map[dir_x][dir_y] == 2 || Map[dir_x][dir_y] == 4 || Map[dir_x][dir_y] == 7)){
						visit[dir_x][dir_y] = true;
						q.push(make_pair(dir_x, dir_y));
						res++;
					}
				}
				else if (i == 1) {
					if ((Map[x][y] == 1 || Map[x][y] == 3 || Map[x][y] == 4 || Map[x][y] == 5) && 
						(Map[dir_x][dir_y] == 1 || Map[dir_x][dir_y] == 3 || Map[dir_x][dir_y] == 6 || Map[dir_x][dir_y] == 7)){
						visit[dir_x][dir_y] = true;
						q.push(make_pair(dir_x, dir_y));
						res++;
					}
				}
				else if (i == 2) {
					if ((Map[x][y] == 1 || Map[x][y] == 2 || Map[x][y] == 4 || Map[x][y] == 7) && 
						(Map[dir_x][dir_y] == 1 || Map[dir_x][dir_y] == 2 || Map[dir_x][dir_y] == 5 || Map[dir_x][dir_y] == 6)){
						visit[dir_x][dir_y] = true;
						q.push(make_pair(dir_x, dir_y));
						res++;
					}
				}
				else if (i == 3) {
					if ((Map[x][y] == 1 || Map[x][y] == 3 || Map[x][y] == 6 || Map[x][y] == 7) &&
						(Map[dir_x][dir_y] == 1 || Map[dir_x][dir_y] == 3 || Map[dir_x][dir_y] == 4 || Map[dir_x][dir_y] == 5)){
						visit[dir_x][dir_y] = true;
						q.push(make_pair(dir_x, dir_y));
						res++;
					}
				}
			}

		}
	}

}

int main()
{

	int T;

	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		res = 0;
		init();

		cin >> N >> M >> R >> C >> L;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				cin >> Map[i][j];
			}
		}

		bfs();

		cout << "#" << tc << ' ' << res << endl;
	}
	return 0;
}