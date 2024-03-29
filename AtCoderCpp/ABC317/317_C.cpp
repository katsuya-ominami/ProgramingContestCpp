#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdio.h>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;
using ll = long long;
using ull = unsigned long long;

int di[] = { -1,0,1,0,-1,1,1,-1,0 }; // ↑ → ↓ ← 右上 右下 左下 左上  中心
int dj[] = { 0,1,0,-1,1,1,-1,-1,0 };

struct Edge {

	// メンバ変数
	int to;
	int cost;

	// コンストラクタ デフォルト引数をとる
	// : コロン以降はメンバ初期化子リスト
	Edge(int t = 0, int c = 0) : to(t), cost(c) {}

};

int solve(vector<vector<Edge>> g, int n) {

	int ans = 0;
	// ラムダ式
	// [キャプチャリスト](パラメータリスト) mutable 例外仕様 属性 -> 戻り値の型 { 関数の本体 }
	// [&] はたぶんmain関数内の変数を普通参照して使えるキャプチャ
	// ラムダ式で再帰関数を定義する場合は引数に自分自身をいれる。今回の場合auto fが該当
	auto f = [&](auto f, int v, vector<bool> visited, int dist) -> void {
		visited[v] = true;
		ans = max(ans, dist);
		for (auto e : g[v]) {
			if (visited[e.to]) continue;
			f(f, e.to, visited, dist + e.cost);
		}
		};

	rep(i, n) {
		// 全ての頂点を試す
		f(f, i, vector<bool>(n), 0);
	};

	return ans;
}

signed main() {

	int n, m;
	cin >> n >> m;
	vector<vector<Edge>> g(n);

	rep(i, m) {
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}

	int ans = 0;

	ans = solve(g, n);

	cout << ans << endl;

	return 0;

}

