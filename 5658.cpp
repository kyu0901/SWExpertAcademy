//43개 맞음

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> v[4];
vector<long long> ans;
int N , K;
long long res;

void To_Ten()
{
	int cnt = N / 4;
	int a, k;

	for (int i = 0; i < 4; i++) {
		k = 0;
		for (int j = 0; j < cnt; j++) {
			if (v[i][j] >= 'A')
				a = v[i][j] - 'A' + 10;
			else
				a = v[i][j] - '0';

			for (int k = j; k < cnt - 1; k++) {
				a *= 16;
			}
			k += a;
		}
		//cout << "값 : " << k << endl;
		//십진수를 집어넣기.
		ans.push_back(k);
	}
}

void Rot(int cnt)
{
	if (cnt == N / 4)
		return;

	To_Ten();

	char tmp;

	tmp = v[3][N / 4 - 1];

	//cout << " Rot Start " << endl;

	for (int i = 3; 0 <= i; i--) {
		for (int j = N / 4 - 1; 0 < j; j--) {
			v[i][j] = v[i][j - 1];
		}
		if(i>0)
			v[i][0] = v[i - 1][N / 4 - 1];
	}


	v[0][0] = tmp;

	/*
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			cout << v[i][j];
		}
		cout << endl;
	}
	*/
	
	Rot(cnt + 1);
}

int main()
{
	int T;
	char c;

	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		//초기화
		ans.clear();
		res = 0;
		for (int i = 0; i < 4; i++) {
			v[i].clear();
		}

		cin >> N >> K;
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < N / 4; j++) {

				cin >> c;
				v[i].push_back(c);

			}
		}

		Rot(0);

		sort(ans.begin(), ans.end(), greater<int>());

		int cnt = 1;

		for (int i = 0; i < ans.size()-1; i++) {

			if (cnt == K) {
				//cout << ans[i + 1] << endl;
				res = ans[i];
				break;
			}

			if (ans[i] != ans[i + 1]){
				//cout << ans[i] << endl;
				cnt++;
			}
			
		}

		if (res == 0) {
			res = ans[ans.size() - 1];
		}


		cout << "#" << tc << ' ' << res << endl;
	}

	return 0;
}