#include <bits/stdc++.h>
using namespace std;
int N, Q, ans[10];
int nc, sz;
map<pair<int, int>, vector<pair<int, int> > > graph;
int p[10], r[10];
int *t[20], v[20];
int n[20];
int setv(int* a, int b, int toAdd)
{
	t[sz] = a;
	v[sz] = *a;
	*a = b;
	n[sz] = toAdd;
	++sz;
	return b;
}
void rollback(int x)
{
	for (; sz > x;) {
		--sz;
		*t[sz] = v[sz];
		nc += n[sz];
	}
}
int find(int n)
{
	return p[n] ? find(p[n]) : n;
}
bool merge(int a, int b)
{
	a = find(a), b = find(b);
	if (a == b)
		return 0;
	nc--;
	if (r[b] > r[a])
		std::swap(a, b);
	setv(r + b, r[a] + r[b], 0);
	return setv(p + b, a, 1), 1;
}
void solve(int start, int end)
{
	int tmp = sz;
	for (auto it = graph.begin();
		it != graph.end(); ++it) {
		int u = it->first.first;
		int v = it->first.second;
		for (auto it2 = it->second.begin();
			it2 != it->second.end(); ++it2) {
			int w = it2->first, c = it2->second;
			if (w <= start && c >= end) {
				merge(u, v);
				break;
			}
		}
	}
	if (start == end) {
		ans[start] = nc;
		return;
	}
	int mid = (start + end) >> 1;
	solve(start, mid);
	solve(mid + 1, end);
	rollback(tmp);
}

void componentAtInstant(vector<int> queries[])
{
	nc = N;
	for (int i = 0; i < Q; i++) {
		int t = queries[i][0];
		int u = queries[i][1], v = queries[i][2];
		if (u > v)
			swap(u, v);
		if (t == 1) {
			graph[{ u, v }].push_back({ i, Q });
		}
		else {
			graph[{ u, v }].back().second = i - 1;
		}
	}
	solve(0, Q);
}


int main()
{
	N = 3, Q = 4;
	vector<int> queries[] = { { 1, 1, 2 }, { 1, 2, 3 }, { 2, 1, 2 }, { 2, 2, 3 } };
	componentAtInstant(queries);
	for (int i = 0; i < Q; i++)
		cout << ans[i] << " ";
	return 0;
}
