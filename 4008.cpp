#include <iostream>

using namespace std;


int Card[12];
//+ - * / ¼ø
int Cal[4];
int N, res, r_Max, r_Min;

void init()
{
	for (int i = 0; i < 4; i++) {
		Cal[i] = 0;
	}
	for (int i = 0; i < 12; i++) {
		Card[i] = 0;
	}

	r_Max = -100000000;
	r_Min = 100000000;
}

void dfs(int cnt, int value)
{
	if (cnt == N - 1) {

		if (value < r_Min)
			r_Min = value;
		
		if (value > r_Max)
			r_Max = value;

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (Cal[i] > 0) {
			Cal[i] -= 1;
			if(i == 0)
				dfs(cnt + 1, value + Card[cnt + 1]);
			else if(i==1)
				dfs(cnt + 1, value - Card[cnt + 1]);
			else if(i==2)
				dfs(cnt + 1, value * Card[cnt + 1]);
			else
				dfs(cnt + 1, value / Card[cnt + 1]);
			
			Cal[i] += 1;
		}
	}

}

int main()
{

	int T, C_type;
	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		init();

		cin >> N;
		
		for (int i = 0; i < 4; i++) {
			cin >> C_type;
			Cal[i] += C_type;
		}

		for (int i = 0; i < N; i++) {
			cin >> C_type;
			Card[i] = C_type;
		}

		dfs(0, Card[0]);

		cout << "#" << tc << ' ' << r_Max - r_Min << endl;

	}

	return 0;
}