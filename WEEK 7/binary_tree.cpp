#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};



// Hàm tạo node mới 
NODE* createNode(int data) {
	NODE* p = new NODE{ data, nullptr, nullptr };
	return p;
}

//Hàm duyệt NLR pre-order
vector<int> NLR(NODE* pRoot) {
	vector<int> res;
	if (pRoot) {
		res.push_back(pRoot->key);
		vector<int> left = NLR(pRoot->p_left);
		vector <int> right = NLR(pRoot->p_right);
		res.insert(res.end(), left.begin(), left.end());
		res.insert(res.end(), right.begin(), right.end());
	}
	return res;
}

// Hàm duyệt LNR in-order
vector<int> LNR(NODE* pRoot) {
	vector<int> res;
	if (pRoot) {
		vector<int> left = LNR(pRoot->p_left);
		res.insert(res.end(), left.begin(), left.end());
		res.push_back(pRoot->key);
		vector<int> right = LNR(pRoot->p_right);
		res.insert(res.end(), right.begin(), right.end());
	}
	return res;
}

// Hàm duyệt LRN post-order
vector<int> LRN(NODE* pRoot) {
	vector<int> res;
	if (pRoot) {
		vector<int> left = LRN(pRoot->p_left);
		vector<int> right = LRN(pRoot->p_right);
		res.insert(res.end(), left.begin(), left.end());
		res.insert(res.end(), right.begin(), right.end());
		res.push_back(pRoot->key);
	}
	return res;
}


// Hàm duyệt theo tầng Level-order
vector<vector<int>> levelOrder(NODE* pRoot) {
	vector<vector<int>> res;
	if (!pRoot) {
		return res;
	}

	queue<NODE*> q;
	q.push(pRoot);

	while (!q.empty()) {
		int size = q.size();
		vector<int> level;
		for (int i = 0; i < size; i++) {
			NODE* node = q.front(); q.pop();
			level.push_back(node->key);
			if (node->p_left) q.push(node->p_left);
			if (node->p_right) q.push(node->p_right);
		}
		res.push_back(level);
	}
	return res;

}

// Hàm đếm số node
int countNode(NODE* pRoot) {
	if (!pRoot) {
		return 0;
	}

	return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// Hàm tính tổng các giá trị node 
int sumNode(NODE* pRoot) {
	if (!pRoot) {
		return 0;
	}
	return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

// Hàm tính chiều cao của node cụ thể

int getHeight(NODE* p) {
	if (!p) {
		return -1;
	}
	int leftHeight = getHeight(p->p_left);
	int rightHeight = getHeight(p->p_right);
	return 1 + max(leftHeight, rightHeight);
}


int heightNode(NODE* pRoot, int value) {
	if (!pRoot) {
		return -1;
	}

	if (pRoot->key == value) {
		return getHeight(pRoot);
	}

	int left = heightNode(pRoot->p_left, value);
	if (left != -1) {
		return left;
	}
	return heightNode(pRoot->p_right, value);
}

// Hàm tính level của node
int level(NODE* pRoot, NODE* p) {
	if (!pRoot) {
		return -1;
	}
	if (pRoot == p) {
		return 0;
	}

	int left = level(pRoot->p_left, p);
	if (left != -1) {
		return left + 1;
	}

	int right = level(pRoot->p_right, p);
	if (right != -1) {
		return right + 1;
	}
	return -1;
}

// Hàm đếm số node lá 
int countLeaf(NODE* pRoot) {
	if (!pRoot) {
		return 0;
	}
	if (!pRoot->p_left && !pRoot->p_right) {
		return 1;
	}
	return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}