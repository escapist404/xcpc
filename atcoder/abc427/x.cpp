#include <bits/stdc++.h>

int main() {
	std::string s;
	std::cin >> s;
	int n = s.size();

	std::vector<long long> ans;
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n - 1; ++j) {
			for (int k = j + 1; k < n - 1; ++k) {
				long long a = std::stoll(s.substr(0, i + 1));
				long long b = std::stoll(s.substr(i + 1, j - i));
				long long c = std::stoll(s.substr(j + 1, k - j));
				long long d = std::stoll(s.substr(k + 1, n - 1 - k));
				ans.push_back(a + b + c + d);
			}
		}
	}

	std::sort(ans.begin(), ans.end(), std::greater<long long>());

	for (auto i : ans) {
		std::cout << i << " ";
	}
	std::cout << "\n";

	return 0;
}
