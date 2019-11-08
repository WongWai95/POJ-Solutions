// 1000.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

class Solution {
public:
	void run() {
		int num1, num2;
		cin >> num1 >> num2;
		cout << this->add(num1, num2);
	}
	int add(int a, int b) {
		return a + b;
	}
};

int main(void) {
	Solution sol;
	sol.run();
}