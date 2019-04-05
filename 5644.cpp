#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<pair<int, int> > Map[10][10];
//초단위 좌표
vector<pair<int, int> >v[2];
int dir[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
int M, A, res;

void init()
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			Map[i][j].clear();
		}
	}
	for (int i = 0; i < 2; i++) {
		v[i].clear();
	}
	res = 0;
}

bool range(int x, int y)
{
	if (0 <= x && x < 10 && 0 <= y && y < 10)
		return true;
	return false;
}

void check()
{
	cout << "-----------------------" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (Map[i][j].size() == 0)
				cout << "0";
			else if (Map[i][j].size() == 2)
				if (Map[i][j][0].first > Map[i][j][1].first)
					cout << Map[i][j][1].second+1;
				else
					cout << Map[i][j][0].second+1;
			else
				cout << Map[i][j][0].second + 1;
		}
		cout << endl;
	}
}

void bfs(int x, int y, int C, int P, int num)
{
	queue<pair<int, int > > q;
	bool visit[10][10];

	for(int i=0; i<10; i++)
		for (int j = 0; j < 10; j++) 
			visit[i][j] = false;
		
	visit[x][y] = true;
	q.push(make_pair(x, y));

	int depth = 0;
	int size = 0;
	while (!q.empty()) {

		if (depth > C)
			break;

		size = q.size();

		while (size--) {
			int dx = q.front().first;
			int dy = q.front().second;

			if (Map[dx][dy].size() == 2) {
				if (Map[dx][dy][0].first > Map[dx][dy][1].first){
					if(Map[dx][dy][1].first < P){
						Map[dx][dy][1].first = P;
						Map[dx][dy][1].second = num;
					}
				}
				else {
					if(Map[dx][dy][0].first < P){
						Map[dx][dy][0].first = P;
						Map[dx][dy][0].second = num;
					}
				}
			}else{
				Map[dx][dy].push_back(make_pair(P, num));
			}

			for (int i = 0; i < 4; i++) {
				int dir_x = dx + dir[i][0];
				int dir_y = dy + dir[i][1];

				if (range(dir_x, dir_y) && visit[dir_x][dir_y] == false) {
					visit[dir_x][dir_y] = true;
					q.push(make_pair(dir_x, dir_y));
				}
			}

			q.pop();
		}

		depth++;
	}
}

void Solution()
{
	int t = 0;
	int x1, y1, x2, y2, type1, type2, type3, type4;
	int size1, size2;

	for (int i = 0; i < M+1; i++) {
		//배터리의 영역이 아닐 경우
		type1 = type2 = type3 = type4 = 10;
		x1 = v[0][i].first;
		y1 = v[0][i].second;
		if (Map[x1][y1].size() > 0)
			type1 = Map[x1][y1][0].second;

		x2 = v[1][i].first;
		y2 = v[1][i].second;
		if (Map[x2][y2].size() > 0)
			type2 = Map[x2][y2][0].second;

		size1 = Map[x1][y1].size();
		size2 = Map[x2][y2].size();

		if (size1 > 1)
			type3 = Map[x1][y1][1].second;

		if (size2 > 1)
			type4 = Map[x2][y2][1].second;

		//범위 내에 같이 있을 경우.
		if (((type1 == type2) && type1 != 10) || ((type1 == type4) && type1 != 10) || ((type3 == type2) && type3 != 10) || (type3 == type4) && type3 != 10) {
			if (size1 == 1 && size2 == 1) {
				res += Map[x1][y1][0].first;
			}
			else if (size1 == 1 && size2 == 2) {
				if (type1 == type2)
					res += Map[x1][y1][0].first + Map[x2][y2][1].first;
				if (type1 == type4)
					res += Map[x1][y1][0].first + Map[x2][y2][0].first;
			}
			else if (size1 == 2 && size2 == 1) {
				if (type1 == type2)
					res += Map[x1][y1][1].first + Map[x2][y2][0].first;
				if (type3 == type2)
					res += Map[x1][y1][0].first + Map[x2][y2][0].first;
			}
			else if(size1 == 2 && size2 == 2){
				int m1 = max(Map[x1][y1][0].first, Map[x1][y1][1].first);
				int l1 = min(Map[x1][y1][0].first, Map[x1][y1][1].first);
				int m2 = max(Map[x2][y2][0].first, Map[x2][y2][1].first);
				int l2 = min(Map[x2][y2][0].first, Map[x2][y2][1].first);

				if (m1 != m2)
					res += m1 + m2;
				else {
					if (l1 > l2)
						res += m1 + l1;
					else
						res += m1 + l2;
				}
			}
		}
		else {
			
			if (size1 == 1) {
				res += Map[x1][y1][0].first;
			}
			else if (size1 == 2) {
				res += max(Map[x1][y1][0].first, Map[x1][y1][1].first);
			}

			if (size2 == 1) {
				res += Map[x2][y2][0].first;
			}
			else if (size2 == 2) {
				res += max(Map[x2][y2][0].first, Map[x2][y2][1].first);
			}
		}

		//cout << "현재 좌표들 : " << x1 << ", " << y1 << " ,  " << x2 << " , " << y2 << endl;
		//cout << "현재 카운트 : " << i + 1 << " 값 : " << res << endl;
	}
}
int main()
{
	int T, x, y, a, C, P;

	cin >> T;

	for (int tc = 1; tc <= T; tc++) {

		cin >> M >> A;
		
		init();

		//사람의 좌표 표시
		for (int i = 0; i < 2; i++) {
			if (i == 0) {
				x = y = 0;
			}
			else {
				x = y = 9;
			}

			v[i].push_back(make_pair(x, y));

			for (int j = 0; j < M; j++) {

				cin >> a;

				if (a == 1) {
					x += -1;
				}
				else if (a == 2) {
					y += 1;
				}
				else if (a == 3) {
					x += 1;
				}
				else if (a == 4) {
					y += -1;
				}

				v[i].push_back(make_pair(x, y));
			}


		}

		//Battery Map
		for (int i = 0; i < A; i++) {
			
			cin >> y >> x >> C >> P;
			bfs(x - 1, y - 1, C, P, i);
		}

		//check();

		Solution();

		cout << "#" << tc << ' ' << res << endl;
	}
	
	return 0;
}