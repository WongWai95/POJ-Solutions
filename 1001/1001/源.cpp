#include <iostream>	
#include <list>
#include <string>
using namespace std;

/*���������*/
class Solution {
public:
	/*���������������*/
	void run() {
		string s;
		int n;
		while (cin >> s >> n) {
			cout << exponentiation(s, n) << endl;
		}
	}
private:
	/*����߾����ݣ�sΪ������nΪָ��*/
	string exponentiation(string s, int n) {
		/*���ַ������͵ĵ���ת���������У���ȥ��С���㣬С����λ�õ�����¼*/
		list<int> origin, res(1, 1); //originΪת��Ϊ����֮��洢�����ı���
		int dot_pos = 0, res_dot = 0; //dot_posΪԭ����С����λ�ã� res_dot��¼�����С����λ��
		for (int i = s.size() - 1; i >= 0; --i) {
			if (s[i] == '.') dot_pos = s.size() - i - 1; //��¼�Ƿ���ԭ��������С����Ĵ��ڣ���¼����С����λ��
			else origin.push_back(s[i]-'0'); //ת��charΪint����
		}
		/*ʹ�ÿ�����������߾�����*/
		while (n > 0) {
			if (n & 1) {
				multiple(res, origin);
				res_dot += dot_pos; //���½����С����λ��
			}
			multiple(origin, origin);
			if (dot_pos > 0) dot_pos <<= 1;
			n >>= 1;
		}
		/*��ʽ��������String���ͽ��*/
		string str_res;
		int index = 0;
		if (dot_pos > 0) res_dot = res.size() - res_dot; //ת��res_dotΪ����λ��
		for (auto r_it = res.rbegin(); r_it != res.rend(); ++r_it, ++index) {
			if (dot_pos > 0 && res_dot == index) str_res.push_back('.');
			str_res.push_back(*r_it + '0'); //����ת��Ϊchar����
		}
		//ȥ���������(Ҳ������ԭʼ������ȥ�����������и���)
		if (dot_pos != 0) { //����С����Ž���ȥ������
			auto it = str_res.end() - 1;
			for (; it != str_res.begin(); --it) {
				if (*it != '0') {
					break;
				}
			}
			str_res.erase(it+1, str_res.end()); //ȥ��ĩβ����
			if (*(str_res.end()-1) == '.') str_res.erase(str_res.end()-1); //�����һλ��С���㣬��ȥ��
			auto it2 = str_res.begin(); 
			for (; it2 != str_res.end(); ++it2) {
				if (*it2 != '0') {
					break;
				}
			}
			str_res.erase(str_res.begin(), it2);//ȥ��ǰ������
		}
		else {
			auto it2 = str_res.begin();
			for (; it2 != str_res.end(); ++it2) {
				if (*it2 != '0') {
					break;
				}
			}
			str_res.erase(str_res.begin(), it2);//ȥ��ǰ������
		}
		if (str_res.size() == 0) str_res.push_back('0'); //�������Ϊ�գ�����Ϊ0
		return str_res;
	}
	/*����洢�����������е��������ĳ˻������ͨ��Num1�����÷���*/
	void multiple(list<int>& num1, list<int> num2) { //ģ��˷���ʽ���м��㣬�涨num2Ϊ������num1Ϊ������
		list<int> temp, origin_num1(num1); //temp�洢�����뱻��������һλ����ʱ�����origin_num1Ϊnum1�Ŀ������Է�������num1��յ���ԭ���ݶ�ʧ
		int key_index = 0; //��¼��λ�����ʱ������������λ��
		num1.erase(num1.begin(), num1.end());
		for (auto key : origin_num1) {
			temp.erase(temp.begin(), temp.end());
			for (int i = 0; i < key_index; ++i) temp.push_back(0);
			multiple_one(num2, key, temp);
			add(num1, temp);
			++key_index;
		}
	}
	/*����һ��һλ������洢������L-H�е����ĳ˻�������洢��result�����÷���*/
	void multiple_one(list<int>& num, int one, list<int>& result) { //ģ����ʽ�����λ����һλ
		int carry = 0, temp = 0; //carryΪ��λ�� tempΪ���ʱ��Ž������ʱ����
		for (auto it = num.begin(); it != num.end(); ++it) {
			temp = *it * one + carry;
			result.push_back(temp % 10);
			carry = temp / 10;
		}
		if (carry != 0) result.push_back(carry); //��������ɺ��λֵ�Բ���0������ӵ����λ
	}
	/*����洢������L-H�е��������ĺͣ�����洢��num1*/
	void add(list<int>& num1, list<int>& num2) { //ģ����ʽ�������������
		int carry = 0, temp = 0; //carryΪ��λ�� tempΪ���ʱ��Ž������ʱ����
		auto it1 = num1.begin(), it2 = num2.begin();
		for (; it1 != num1.end(); ++it1) {
			if (it2 != num2.end()) {
				temp = *it1 + *it2 + carry;
				*it1 = temp % 10;
				carry = temp / 10;
				++it2;
			}
			else { //��num1��λ������num2
				temp = *it1 + carry;
				*it1 = temp % 10;
				carry = temp / 10;
			}
		}
		while (it2 != num2.end()) { //��num1��λ��С��num2
			temp = *it2 + carry;
			num1.push_back(temp % 10);
			carry = temp / 10;
			++it2;
		}
		if (carry != 0) num1.push_back(carry); //��������ɺ��λֵ�Բ���0������ӵ����λ
	}
};

int main() {
	Solution sol;
	sol.run();
}