#include<iostream>
#include<stack>
#include<vector>
#include<string>
using namespace std;

/*
Compile in Linux or Mac:
g++ -std=c++11 -o validate_parentheses validate_parentheses.cc

Run:
./validate_parentheses

Output:
 -> 
( -> 
) -> 
() -> ()
)( -> 
())( -> ()
)())))))( -> ()
(() -> ()
a(b) -> a(b)
()a(b))() -> ()a(b)()
((a)()a(ab)(((a() -> (a)()a(ab)a()

*/

class Solution {
public:
	string validate(string s) {
		if(s.size() == 0) return s;
		stack<char> stack;
		string res = "";

		for(unsigned i = 0; i < s.size(); ++i) {
			char c = s[i];
			if(c != ')') {
				stack.push(c);
			} else if(!stack.empty()) {
				string append_str = "";
				int num_left = 0;

				while(!stack.empty()) {
					char stack_top = stack.top();
					if(stack_top == '(') ++num_left;
					if(num_left >= 2) break;
					append_str = stack_top + append_str;
					stack.pop();
				}
				res += append_str;
				res += c;
			}
		}

		return res;
	}
};

int main() {
	Solution sol;
	
	vector<string> test_strings = {
		"",
		"(",
		")",
		"()",
		")(",
		"())(", 
		")())))))(",
		"(()",
		"a(b)",
		"()a(b))()",
		"((a)()a(ab)(((a()"
	};
	
	for(unsigned i = 0; i < test_strings.size(); ++i) {
		cout << test_strings[i] << " -> " << sol.validate(test_strings[i]) << endl;
	}
}

