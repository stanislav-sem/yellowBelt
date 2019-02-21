#include <iostream>
#include <vector>
using namespace std;
/*
2 14
1 2 3
30 40 50

1 100
1000 1000 1000
 */

int main() {
	int N = 0;
	int R = 0;
	cin >> N >> R;
	uint64_t result = 0;
	for (int i = 0; i < N; i++) {
		int64_t W = 0, H = 0, D = 0;
		cin >> W >> H >> D;
		int64_t M = W * H * D * R;
		result += M;
	}
	cout << result;
	return 0;
}
