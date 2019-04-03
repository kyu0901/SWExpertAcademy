#include <iostream>

using namespace std;

int Map[13][20];
int D, W, K, res;

bool Correct()
{
	bool chk = true;

	for (int i = 0; i < W; i++) {
		for (int p = 0; p <= D - K; p++) {
			for (int q = p; q < p + K - 1; q++) {

				//cout << "현재 보는 곳 : " << q <<", " << i << endl;
				if (Map[q][i] != Map[q + 1][i]) {
					chk = false;
					break;
				}
			}
			if (chk)
				break;
		}
		if (chk == false)
			break;
	}

	/*
	if (chk)
		cout << "가능하다" << endl;
		*/
	

	return chk;
}

void dfs(int x, int cnt)
{
	if (res < cnt)
		return;

	if (x == D) {

		//cout << "-------------------" << endl;

		if (Correct() && cnt < res)
			res = cnt;
		
		/*
		cout << res << endl;
		
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				cout << Map[i][j];
			}
			cout << endl;
		}
		*/
		return;
	}

	// i값이 0이면 그대로 간다. i값이 1이면 0로 i값이 2이면 1으로
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			dfs(x + 1, cnt);
		}
		else if ( i== 1) {
			int tmp[20];
			for (int j = 0; j < W; j++) {
				tmp[j] = Map[x][j];
				Map[x][j] = 0;
			}

			dfs(x + 1, cnt + 1);
			
			for (int j = 0; j < W; j++) {
				Map[x][j] = tmp[j];
			}
		}
		else {
			int tmp[20];
			for (int j = 0; j < W; j++) {
				tmp[j] = Map[x][j];
				Map[x][j] = 1;
			}
			
			dfs(x + 1, cnt + 1);

			for (int j = 0; j < W; j++) {
				Map[x][j] = tmp[j];
			}
		}
	}
}
int main()
{

	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		cin >> D >> W >> K;

		res = 15;

		for (int i = 0; i < D; i++) {
			for (int j = 0; j < W; j++) {
				cin >> Map[i][j];
			}
		}

		dfs(0, 0);
		cout << "#" << tc << ' ' << res << endl;
	}
	return 0;
}