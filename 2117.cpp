#include <iostream>
#include <queue>

using namespace std;

int dir[4][2] = { {1,0}, {0,1},{-1,0},{0,-1} };
int Map[20][20];
int memo[22];
int N, M, res;

bool range(int x, int y)
{
	if (0 <= x && x < N && 0 <= y && y < N)
		return true;
	return false;
}

void InitMemo()
{
	for (int i = 1; i <= 21; i++) {
		memo[i] = i * i + (i - 1)*(i - 1);
	}
}

void bfs(int x, int y)
{

	bool visit[20][20] = {};
	visit[x][y] = true;
	queue<pair<int, int> > q;
	q.push(make_pair(x, y));

	int q_size;
	int depth = 1;
	int cnt = 0;
	if (Map[x][y] == 1)
		cnt += 1;

	while (!q.empty())
	{
		
		q_size = q.size();

		if (cnt * M >= memo[depth])
			res = max(res, cnt);

		if (depth == N + 1)
			return;

		while (q_size--)
		{
			int d_x = q.front().first;
			int d_y = q.front().second;

			q.pop();

			for (int i = 0; i < 4; i++) {
				int dir_x = d_x + dir[i][0];
				int dir_y = d_y + dir[i][1];

				if (range(dir_x, dir_y) && visit[dir_x][dir_y] == false) {
					visit[dir_x][dir_y] = true;
					if (Map[dir_x][dir_y] == 1)
						cnt++;
					q.push(make_pair(dir_x, dir_y));
				}
			}
		}

		depth += 1;
	}
}
int main()
{
	int T;
	cin >> T;

	InitMemo();

	for (int tc = 1; tc <= T; tc++) {

		res = 0;

		cin >> N >> M;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> Map[i][j];
			}
		}

		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				bfs(i, j);
			}
		}

		cout << "#" << tc << ' ' << res << endl;
	}
	return 0;
}