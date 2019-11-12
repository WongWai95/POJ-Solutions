#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
	unordered_map<char, char> search_dict; //�洢�绰�����г��ֵ���ĸ�����ֹ���ֵ
	unordered_map<string, int> count_dict; //�洢����ת���ɱ�׼��ʽ��ġ��绰����-���ִ�������ֵ��
	priority_queue<string, vector<string>, greater<string>> dup_nums; //��̬�洢�����������εĵ绰����
	Solution() {
		/*��ʼ��search_dict*/
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
		/*��ȡ������Ϣ*/
		for (int i = 0; i < count; ++i) {
			cin >> symbol;
			trans_symbol(symbol);
		}
		/*��ʽ�����*/
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
		/*ȥ��ԭʼ�����е����ַ���-��,��ֵ��fmt_symbol*/
		string fmt_symbol;
		for (auto c : symbol) {
			if (c != '-') fmt_symbol.push_back(c);
		}
		/*ת��Ϊ��׼����*/
		for (string::iterator it = fmt_symbol.begin(); it != fmt_symbol.end(); ++it) {
			*it = search_dict[*it];
		}
		/*����count_dict�У������¶�Ӧ��value����valueֵ����1����ͬ�����浽dup_nums*/
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