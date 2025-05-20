#include <iostream>
#include<climits>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
};

NODE* createNode(int data) {
	return new NODE{ data,nullptr,nullptr };
}

// Tìm node có giá trị x
NODE* search(NODE* &pRoot, int x) {
	if (!pRoot || pRoot->key == x) {
		return pRoot;
	}
	if (x < pRoot->key) {
		return search(pRoot->p_left, x);
	}
	else {
		return search(pRoot->p_right, x);
	}
}

// Thêm node 
void Insert(NODE* &pRoot, int x) {
	if (!pRoot) {
		pRoot = createNode(x);
		return;
	}
	if (x < pRoot->key) {
		Insert(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Insert(pRoot->p_right, x);
	}
}

// Xóa node
NODE* findMin(NODE* p) {
	while (p->p_left) {
		p = p->p_left;
	}
	return p;
}

void Remove(NODE*& pRoot, int x) {
	if (!pRoot) {
		return;
	}

	if (x < pRoot->key) {
		Remove(pRoot->p_left, x);
	}
	else if (x > pRoot->key) {
		Remove(pRoot->p_right, x);
	}
	else {
		if (!pRoot->p_left) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_right;
			delete temp;
		}
		else if (!pRoot->p_right) {
			NODE* temp = pRoot;
			pRoot = pRoot->p_left;
			delete temp;
		}
		else {
			NODE* temp = findMin(pRoot->p_right);
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}
	}
}

// Tạo BST từ bảng
NODE* createtree(int a[], int n) {
	NODE* root = nullptr;
	for (int i = 0; i < n; i++) {
		Insert(root, a[i]);
	}
	return root;
}

// Xóa toàn bộ cây
void removeTree(NODE*& pRoot) {
	if (!pRoot) {
		return;
	}

	removeTree(pRoot->p_left);
	removeTree(pRoot->p_right);
	delete pRoot;
	pRoot = nullptr;
}

// Tính chiều cao của BST
int Height(NODE* pRoot) {
	if (!pRoot) {
		return -1;
	}

	int leftHeight = Height(pRoot->p_left);
	int rightHeight = Height(pRoot->p_right);
	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}

// Đếm số node có key bé hơn 
int countLess(NODE* pRoot, int x) {
	if (!pRoot) {
		return 0;
	}

	if (pRoot->key >= x) {
		return countLess(pRoot->p_left, x);
	}
	return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
}

// Đếm số node có key lớn hơn 
int countGreater(NODE* pRoot, int x) {
	if (!pRoot) {
		return 0;
	}

	if (pRoot->key <= x) {
		return countGreater(pRoot->p_right, x);
	}
	return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
}


// Hàm kiểm tra cây có phải BST?
bool isBSTUtil(NODE* pRoot, int minVal, int maxVal) {
	if (!pRoot) return true;
	if (pRoot->key <= minVal || pRoot->key >= maxVal)
		return false;
	return isBSTUtil(pRoot->p_left, minVal, pRoot->key) &&
		isBSTUtil(pRoot->p_right, pRoot->key, maxVal);
}

bool isBST(NODE* pRoot) {
	return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

// Kiểm tra full BST 
bool isFullBST(NODE* pRoot) {
	if (!pRoot) {
		return true;
	}
	if (!pRoot->p_right && !pRoot->p_left) {
		return true;
	}
	if (pRoot->p_left && pRoot->p_right) {
		return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
	}
	return false;
}
