#include <iostream>

using namespace std;

int Money[4];
int visit[12];
int res;

void dfs(int month, int total)
{
	if (12 <= month) {
		if (res > total)
			res = total;
		return;
	}

	if (res < total)
		return;

	for (int i = 0; i < 4; i++) {

		if (i == 0) {
			dfs(month + 1, total + visit[month] * Money[0]);
		}
		else if (i == 1) {
			dfs(month + 1, total + Money[1]);
		}
		else if (i == 2) {
			dfs(month + 3, total + Money[2]);
		}
		else {
			dfs(month + 12, total + Money[3]);
		}

	}

}

int main()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {
		
		res = 999999999;

		for (int i = 0; i < 4; i++) {
			cin >> Money[i];
		}

		for (int i = 0; i < 12; i++) {
			cin >> visit[i];
		}

		dfs(0, 0);

		cout << "#" << tc << ' ' << res << endl;
	}

	return 0;
}