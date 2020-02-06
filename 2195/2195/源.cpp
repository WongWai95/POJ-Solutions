#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
	vector<vector<int>> 
		man,					// 记录题目输入的man的坐标
		house;					// 记录题目输入的house的坐标
	int size = 0;				// 记录二部图的单部分大小，即man和house的数量
	vector<vector<int>> map;	// 二维向量，map[i][j]表示第i个man到第j个house的花费
	vector<int> 
		man_ex,					// 一维向量，man_ex[i]表示在KM算法过程中的第i个man的期望值
		house_ex;				// 一维向量，house_ex[i]表示在KM算法过程中的第i个house的被期望值
	vector<bool> 
		man_vis,				// 记录在单个循环过程中第i个man是否被尝试匹配
		house_vis;				// 记录在单个循环过程中第i个house是否被尝试匹配
	vector<int> 
		match,					// 记录每个house被匹配到的man，没有匹配到为-1
		slack;					// 记录每个house被man选择至少还需要多少期望值
public:
	void run() {    // 驱动程序
		int rows, cols;
		while (true) {    //循环输入
			cin >> rows >> cols;
			if (rows == 0 && cols == 0) {    //检测到终止符，退出
				break;
			}
			
			man.resize(0, vector<int>(2, 0));
			house.resize(0, vector<int>(2, 0));
			char input;
			for (int r = 0; r < rows; ++r) {
				for (int c = 0; c < cols; ++c) {
					cin >> input;
					if (input == 'H') house.push_back(vector<int>({ r, c }));
					else if (input == 'm') man.push_back(vector<int>({ r, c }));
				}
			}

			cout << going_home(man, house) << endl;

		}
	}

	int going_home(vector<vector<int>>& man, vector<vector<int>>& house) {
		// 以下代码根据man和house数量重新分配vector空间大小
		size = man.size();
		match.clear(), match.resize(size, -1);				// 将匹配清除
		map.clear(), map.resize(size, vector<int>(size));	
		man_ex.clear(), man_ex.resize(size, INT_MAX);		// man的期望初始化为无穷大
		house_ex.clear(), house_ex.resize(size, 0);			// house的被期望值初始化为0
		// 初始化map；初始化man_ex为map中当前man对应的最小期望边，即这个man回去离得最近的那个house需要付的钱
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				map[i][j] = abs(man[i][0] - house[j][0]) + abs(man[i][1] - house[j][1]);
				man_ex[i] > map[i][j] ? man_ex[i] = map[i][j]:0;
			}
		}
		
		for (int man_id = 0; man_id < size; ++man_id) {
			slack.clear(), slack.resize(size, INT_MAX);
			while (true) {
				man_vis.clear(), man_vis.resize(size, false);		// 将所有man标记为未访问状态
				house_vis.clear(), house_vis.resize(size, false);	// 将所有house标记为未访问状态
				if (km(man_id)) break;	// 如果这个man在这次循环中找到house了，就进入下次循环
				// 以下几行代码的作用：因为找house失败，所以要找出这个人想要找到house，需要让自己回家花的钱至少提高多少dollar，记为d。
				int d = INT_MAX;
				for (int house_id = 0; house_id < size; ++house_id) {
					if (!house_vis[house_id]) d = min(slack[house_id], d);
				}
				
				for (int id = 0; id < size; ++id) {
					if (man_vis[id]) man_ex[id] += d;		// 将访问过的man的期望加d，即让自己回家的钱增加d
					if (house_vis[id]) house_ex[id] -= d;	// 将访问过的house的被期望值减d
					else slack[id] += d;					// 将没被访问过的house的slack加d
				}
			}
		}
		// 对回家的总花费做累加
		int res = 0;
		for (int i = 0; i < size; ++i)
			res += map[match[i]][i];

		return res;
	}

	bool km(int man_id) {
		man_vis[man_id] = true;    //标记当前man为已访问状态
		for (int house_id = 0; house_id < size; ++house_id) {
			if (house_vis[house_id]) continue;	// 每个house只遍历一次
			int gap = house_ex[house_id] + man_ex[man_id] - map[man_id][house_id];	// 计算man的期望和house的被期望值与真实花费之间的差值
			if (gap == 0) {	// 差值为0则进行迭代匹配
				house_vis[house_id] = true;
				if (match[house_id] == -1 || km(match[house_id])) {	// 若这个house还没有被选取，或者选这个house的man可以选择其它的house
					match[house_id] = man_id;
					return true;
				}
			}
			else {	// 否则更新slack的值
				slack[house_id] = min(slack[house_id], gap);
			}
		}
		return false;
	}
};

int main(void) {
	Solution sol;
	sol.run();
	return 0;
}