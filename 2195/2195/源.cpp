#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
private:
	vector<vector<int>> 
		man,					// ��¼��Ŀ�����man������
		house;					// ��¼��Ŀ�����house������
	int size = 0;				// ��¼����ͼ�ĵ����ִ�С����man��house������
	vector<vector<int>> map;	// ��ά������map[i][j]��ʾ��i��man����j��house�Ļ���
	vector<int> 
		man_ex,					// һά������man_ex[i]��ʾ��KM�㷨�����еĵ�i��man������ֵ
		house_ex;				// һά������house_ex[i]��ʾ��KM�㷨�����еĵ�i��house�ı�����ֵ
	vector<bool> 
		man_vis,				// ��¼�ڵ���ѭ�������е�i��man�Ƿ񱻳���ƥ��
		house_vis;				// ��¼�ڵ���ѭ�������е�i��house�Ƿ񱻳���ƥ��
	vector<int> 
		match,					// ��¼ÿ��house��ƥ�䵽��man��û��ƥ�䵽Ϊ-1
		slack;					// ��¼ÿ��house��manѡ�����ٻ���Ҫ��������ֵ
public:
	void run() {    // ��������
		int rows, cols;
		while (true) {    //ѭ������
			cin >> rows >> cols;
			if (rows == 0 && cols == 0) {    //��⵽��ֹ�����˳�
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
		// ���´������man��house�������·���vector�ռ��С
		size = man.size();
		match.clear(), match.resize(size, -1);				// ��ƥ�����
		map.clear(), map.resize(size, vector<int>(size));	
		man_ex.clear(), man_ex.resize(size, INT_MAX);		// man��������ʼ��Ϊ�����
		house_ex.clear(), house_ex.resize(size, 0);			// house�ı�����ֵ��ʼ��Ϊ0
		// ��ʼ��map����ʼ��man_exΪmap�е�ǰman��Ӧ����С�����ߣ������man��ȥ���������Ǹ�house��Ҫ����Ǯ
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				map[i][j] = abs(man[i][0] - house[j][0]) + abs(man[i][1] - house[j][1]);
				man_ex[i] > map[i][j] ? man_ex[i] = map[i][j]:0;
			}
		}
		
		for (int man_id = 0; man_id < size; ++man_id) {
			slack.clear(), slack.resize(size, INT_MAX);
			while (true) {
				man_vis.clear(), man_vis.resize(size, false);		// ������man���Ϊδ����״̬
				house_vis.clear(), house_vis.resize(size, false);	// ������house���Ϊδ����״̬
				if (km(man_id)) break;	// ������man�����ѭ�����ҵ�house�ˣ��ͽ����´�ѭ��
				// ���¼��д�������ã���Ϊ��houseʧ�ܣ�����Ҫ�ҳ��������Ҫ�ҵ�house����Ҫ���Լ��ؼһ���Ǯ������߶���dollar����Ϊd��
				int d = INT_MAX;
				for (int house_id = 0; house_id < size; ++house_id) {
					if (!house_vis[house_id]) d = min(slack[house_id], d);
				}
				
				for (int id = 0; id < size; ++id) {
					if (man_vis[id]) man_ex[id] += d;		// �����ʹ���man��������d�������Լ��ؼҵ�Ǯ����d
					if (house_vis[id]) house_ex[id] -= d;	// �����ʹ���house�ı�����ֵ��d
					else slack[id] += d;					// ��û�����ʹ���house��slack��d
				}
			}
		}
		// �Իؼҵ��ܻ������ۼ�
		int res = 0;
		for (int i = 0; i < size; ++i)
			res += map[match[i]][i];

		return res;
	}

	bool km(int man_id) {
		man_vis[man_id] = true;    //��ǵ�ǰmanΪ�ѷ���״̬
		for (int house_id = 0; house_id < size; ++house_id) {
			if (house_vis[house_id]) continue;	// ÿ��houseֻ����һ��
			int gap = house_ex[house_id] + man_ex[man_id] - map[man_id][house_id];	// ����man��������house�ı�����ֵ����ʵ����֮��Ĳ�ֵ
			if (gap == 0) {	// ��ֵΪ0����е���ƥ��
				house_vis[house_id] = true;
				if (match[house_id] == -1 || km(match[house_id])) {	// �����house��û�б�ѡȡ������ѡ���house��man����ѡ��������house
					match[house_id] = man_id;
					return true;
				}
			}
			else {	// �������slack��ֵ
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