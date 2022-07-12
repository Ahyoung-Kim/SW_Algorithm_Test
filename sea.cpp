#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

int T, N;
int map[101][101];
bool visit[101][101] = { false, };

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

void dfs(int x, int y, int h) {

	for (int i = 0; i < 4; i++) {
		int tx = dx[i] + x;
		int ty = dy[i] + y;

		if (tx < 0 || tx >= N || ty < 0 || ty >= N)
			continue;
		if (visit[ty][tx] || map[ty][tx] <= h)
			continue;

		visit[ty][tx] = true;
		dfs(tx, ty, h);
	}
}

int dfs_search(int h) {
	int num = 0;

	memset(visit, false, sizeof(visit));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!visit[i][j] && map[i][j] > h) {
				dfs(j, i, h);
				num++;
			}
		}
	}

	return num;
}

int main(void) {

	int maxH = 0;
	int ans = 0;
	cin >> T;

	for (int i = 1; i <= T; i++) {
		cin >> N;
		maxH = 0;
		ans = 0;

		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				cin >> map[j][k];
				maxH = max(maxH, map[j][k]);
			}
		}

		for (int h = 0; h < maxH; h++) {
			int temp = dfs_search(h);
			ans = max(temp, ans);
		}

		cout << '#' << i << " " << ans << endl;

	}



	return 0;
}