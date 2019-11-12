#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
	unordered_map<char, char> search_dict; //存储电话号码中出现的字母与数字关联值
	unordered_map<string, int> count_dict; //存储所有转换成标准格式后的“电话号码-出现次数”键值对
	priority_queue<string, vector<string>, greater<string>> dup_nums; //动态存储出现至少两次的电话号码
	Solution() {
		/*初始化search_dict*/
		search_dict['0'] = '0';
		search_dict['1'] = '1';
		search_dict['A'] = search_dict['B'] = search_dict['C'] = search_dict['2'] = '2';
		search_dict['D'] = search_dict['E'] = search_dict['F'] = search_dict['3'] = '3';
		search_dict['G'] = search_dict['H'] = search_dict['I'] = search_dict['4'] = '4';
		search_dict['J'] = search_dict['K'] = search_dict['L'] = search_dict['5'] = '5';
		search_dict['M'] = search_dict['N'] = search_dict['O'] = search_dict['6'] = '6';
		search_dict['P'] = search_dict['R'] = search_dict['S'] = search_dict['7'] = '7';
		search_dict['T'] = search_dict['U'] = search_dict['V'] = search_dict['8'] = '8';
		search_dict['W'] = search_dict['X'] = search_dict['Y'] = search_dict['9'] = '9';
	}
	void run() {
		int count;
		string symbol;
		cin >> count;
		/*读取输入信息*/
		for (int i = 0; i < count; ++i) {
			cin >> symbol;
			trans_symbol(symbol);
		}
		/*格式化输出*/
		if (dup_nums.size() == 0) {
			cout << "No duplicates." << endl;
		}
		else {
			while (dup_nums.size() != 0) {
				string number = dup_nums.top();
				dup_nums.pop();
				int dup_count = count_dict[number];
				number.insert(number.begin() + 3, '-');
				cout << number << ' ' << dup_count << endl;;
			}
		}
	}
	void trans_symbol(string symbol) {
		/*去除原始数据中的连字符“-”,赋值给fmt_symbol*/
		string fmt_symbol;
		for (auto c : symbol) {
			if (c != '-') fmt_symbol.push_back(c);
		}
		/*转化为标准号码*/
		for (string::iterator it = fmt_symbol.begin(); it != fmt_symbol.end(); ++it) {
			*it = search_dict[*it];
		}
		/*存入count_dict中，并更新对应的value，若value值大于1，则同步保存到dup_nums*/
		auto key = count_dict.find(fmt_symbol);
		if (key == count_dict.end()) {
			count_dict[fmt_symbol] = 1;
		}
		else if (key->second == 1) {
			key->second += 1;
			dup_nums.push(key->first);
		}
		else {
			key->second += 1;
		}
	}
};

int main(void) {
	Solution sol;
	sol.run();
}