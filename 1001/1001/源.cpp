#include <iostream>	
#include <list>
#include <string>
using namespace std;

/*解决方案类*/
class Solution {
public:
	/*解决方案驱动程序*/
	void run() {
		string s;
		int n;
		while (cin >> s >> n) {
			cout << exponentiation(s, n) << endl;
		}
	}
private:
	/*计算高精度幂，s为底数，n为指数*/
	string exponentiation(string s, int n) {
		/*将字符串类型的底数转存在链表中，并去掉小数点，小数点位置单独记录*/
		list<int> origin, res(1, 1); //origin为转换为链表之后存储底数的变量
		int dot_pos = 0, res_dot = 0; //dot_pos为原底数小数点位置， res_dot记录结果的小数点位置
		for (int i = s.size() - 1; i >= 0; --i) {
			if (s[i] == '.') dot_pos = s.size() - i - 1; //记录是否在原底数中有小数点的存在，记录逆序小数点位置
			else origin.push_back(s[i]-'0'); //转化char为int类型
		}
		/*使用快速幂运算求高精度幂*/
		while (n > 0) {
			if (n & 1) {
				multiple(res, origin);
				res_dot += dot_pos; //更新结果的小数点位置
			}
			multiple(origin, origin);
			if (dot_pos > 0) dot_pos <<= 1;
			n >>= 1;
		}
		/*格式化并返回String类型结果*/
		string str_res;
		int index = 0;
		if (dot_pos > 0) res_dot = res.size() - res_dot; //转化res_dot为正序位置
		for (auto r_it = res.rbegin(); r_it != res.rend(); ++r_it, ++index) {
			if (dot_pos > 0 && res_dot == index) str_res.push_back('.');
			str_res.push_back(*r_it + '0'); //重新转化为char类型
		}
		//去除多余的零(也可以在原始数据上去除，程序运行更快)
		if (dot_pos != 0) { //若有小数点才进行去除操作
			auto it = str_res.end() - 1;
			for (; it != str_res.begin(); --it) {
				if (*it != '0') {
					break;
				}
			}
			str_res.erase(it+1, str_res.end()); //去除末尾的零
			if (*(str_res.end()-1) == '.') str_res.erase(str_res.end()-1); //若最后一位是小数点，则去掉
			auto it2 = str_res.begin(); 
			for (; it2 != str_res.end(); ++it2) {
				if (*it2 != '0') {
					break;
				}
			}
			str_res.erase(str_res.begin(), it2);//去掉前导的零
		}
		else {
			auto it2 = str_res.begin();
			for (; it2 != str_res.end(); ++it2) {
				if (*it2 != '0') {
					break;
				}
			}
			str_res.erase(str_res.begin(), it2);//去掉前导的零
		}
		if (str_res.size() == 0) str_res.push_back('0'); //若最后结果为空，则置为0
		return str_res;
	}
	/*计算存储在两个链表中的两个数的乘积，结果通过Num1的引用返回*/
	void multiple(list<int>& num1, list<int> num2) { //模拟乘法竖式进行计算，规定num2为乘数，num1为被乘数
		list<int> temp, origin_num1(num1); //temp存储乘数与被乘数其中一位的临时结果，origin_num1为num1的拷贝，以防后续将num1清空导致原数据丢失
		int key_index = 0; //记录两位数相乘时被乘数的左移位数
		num1.erase(num1.begin(), num1.end());
		for (auto key : origin_num1) {
			temp.erase(temp.begin(), temp.end());
			for (int i = 0; i < key_index; ++i) temp.push_back(0);
			multiple_one(num2, key, temp);
			add(num1, temp);
			++key_index;
		}
	}
	/*计算一个一位整数与存储在链表L-H中的数的乘积，结果存储在result的引用返回*/
	void multiple_one(list<int>& num, int one, list<int>& result) { //模拟竖式计算多位乘以一位
		int carry = 0, temp = 0; //carry为进位， temp为相乘时存放结果的临时变量
		for (auto it = num.begin(); it != num.end(); ++it) {
			temp = *it * one + carry;
			result.push_back(temp % 10);
			carry = temp / 10;
		}
		if (carry != 0) result.push_back(carry); //若计算完成后进位值仍不是0，则将其加到最高位
	}
	/*计算存储在链表L-H中的两个数的和，结果存储在num1*/
	void add(list<int>& num1, list<int>& num2) { //模拟竖式计算两个数相加
		int carry = 0, temp = 0; //carry为进位， temp为相加时存放结果的临时变量
		auto it1 = num1.begin(), it2 = num2.begin();
		for (; it1 != num1.end(); ++it1) {
			if (it2 != num2.end()) {
				temp = *it1 + *it2 + carry;
				*it1 = temp % 10;
				carry = temp / 10;
				++it2;
			}
			else { //若num1的位数大于num2
				temp = *it1 + carry;
				*it1 = temp % 10;
				carry = temp / 10;
			}
		}
		while (it2 != num2.end()) { //若num1的位数小于num2
			temp = *it2 + carry;
			num1.push_back(temp % 10);
			carry = temp / 10;
			++it2;
		}
		if (carry != 0) num1.push_back(carry); //若计算完成后进位值仍不是0，则将其加到最高位
	}
};

int main() {
	Solution sol;
	sol.run();
}