#include <bits/stdc++.h>

std::vector<int> get_scc_idx(const std::vector<std::vector<int>> &adj) {
	const int n = adj.size();
	int cur_dfn = -1;
	std::vector<int> dfn(n, -1), low(n, -1);
	std::stack<int> stack;
	std::vector<bool> in_stack(n, false);
	int cur_scc = -1;
	std::vector<int> scc_idx(n, -1);

	const auto tarjan = [&](const int cur, const auto &self) -> void {
		dfn[cur] = low[cur] = ++cur_dfn;
		stack.push(cur);
		in_stack[cur] = true;

		for (const int to : adj[cur]) {
			if (!~dfn[to]) {
				self(to, self);
				low[cur] = std::min(low[cur], low[to]);
			} else if (in_stack[to])
				low[cur] = std::min(low[cur], dfn[to]);
		}

		if (dfn[cur] != low[cur]) return;

		++cur_scc;
		for (int node = -1; node != cur;) {
			node = stack.top();
			stack.pop();
			in_stack[node] = false;
			scc_idx[node] = cur_scc;
		}
	};

	for (int u = 0; u < n; ++u)
		if (!~dfn[u]) tarjan(u, tarjan);

	return scc_idx;
}

std::vector<std::vector<int>> get_dag(const std::vector<std::vector<int>> &adj,
									  const std::vector<int> &scc_idx) {
	const int n = adj.size();
	std::vector<std::vector<int>> dag(
		*std::max_element(scc_idx.begin(), scc_idx.end()) + 1);
	for (int u = 0; u < n; ++u)
		for (const int v : adj[u])
			if (scc_idx[u] != scc_idx[v]) dag[scc_idx[u]].push_back(scc_idx[v]);
	return dag;
}

std::vector<std::vector<int>> get_dag(
	const std::vector<std::vector<int>> &adj) {
	return get_dag(adj, get_scc_idx(adj));
}

void solve() {
    int n, m, q;
    std::cin >> n >> m >> q;


}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        solve();
    }

    return 0;
}