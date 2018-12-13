/*
Link to question:
https://docs.google.com/document/d/1auenQM6UlIGc9MClezndUslPOpxbJ9GVI1_czjU5p3E/edit

For this code:

Compile: 
g++ -std=c++11 -o flower_gap flower_gap.cc

Run:
./flower_gap

Input:
(The example in the question:)
schedule = {3, 2, 5, 1, 9, 7, 10, 8, 6, 4};
k = 1 to 10.

Output:
For k = 2, result = true
For k = 3, result = true
For k = 4, result = true
For k = 5, result = true
For k = 6, result = true
For k = 7, result = false
For k = 8, result = false
For k = 9, result = false
For k = 10, result = true

*/

#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
	// 1 <= k <= n
	bool has_gap(vector<int>& schedule, int k) {
		int n = schedule.size();
		if(n <= 0) return false;

		// Convert schedule to positions:
		vector<int> positions(n, -1);

		for(int i = 0; i < n; ++i) {
			int sch = schedule[i];
			positions[sch - 1] = i;
		}

		vector<int**> map(n, NULL); 
		vector<int> values(n, 0);
		vector<int*> values_pointers(n, 0);
		unordered_set<int> set;

		// Traverse the positions reversely:
		for(auto pos = positions.rbegin(); pos != positions.rend(); ++pos) {
			int p = *pos;

			if(map[p - 1] && map[p + 1]) {
				int val_p_minus_1 = **map[p - 1];
				int val_p_plus_1 = **map[p + 1];
				int new_p_minus_plus_1 = val_p_minus_1 + val_p_plus_1 + 1;
				**map[p - 1] = new_p_minus_plus_1;
				//map[p + 1] = map[p - 1];
				*map[p + 1] = *map[p - 1];
				map[p] = map[p - 1];
				set.insert(new_p_minus_plus_1);

			} else if(map[p - 1]) {
				int new_p_minus_1 = ++(**map[p - 1]);
				map[p] = map[p - 1];
				set.insert(new_p_minus_1);

			} else if(map[p + 1]) {
				int new_p_plus_1 = ++(**map[p + 1]);
				map[p] = map[p + 1];
				set.insert(new_p_plus_1);
			} else {
				values[p] = 1;
				values_pointers[p] = &values[p];
				map[p] = &values_pointers[p];
				set.insert(1);
			}
			
			if(set.find(k) != set.end()) return true;
		}

		return false;
	}
};

int main() {
	Solution sol;
	vector<int> schedule = {3, 2, 5, 1, 9, 7, 10, 8, 6, 4};

	for(int k = 1; k <= 10; ++k) {
		string res_to_str = sol.has_gap(schedule, k) ? "true" : "false";
		cout << "For k = " << k << ", result = " << res_to_str << endl;
	}

}









