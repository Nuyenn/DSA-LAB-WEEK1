#include<iostream>

using namespace std;

struct NODE {
	int key;
	NODE* p_left;
	NODE* p_right;
	int height;
};


//--------------------------------HÀM HỖ TRỢ--------------------------------//
int getHeight(NODE* p) {
	if (p == nullptr) {
		return -1;
	}
	else {
		return p->height;
	}
}


int getBalance(NODE* p) {
	if (p == nullptr) {
		return 0;
	}
	else {
		return getHeight(p->p_left) - getHeight(p->p_right);
	}
}

void updateHeight(NODE* p) {
	if (p) {
		p->height = 1 + max(getHeight(p->p_left), getHeight(p->p_right));
	}
}


NODE* rotateRight(NODE* y) {
	NODE* x = y->p_left;
	NODE* T2 = x->p_right;

	x->p_right = y;
	y->p_left = T2;

	updateHeight(y);
	updateHeight(x);

	return x;
}

NODE* rotateLeft(NODE* x) {
	NODE* y = x->p_right;
	NODE* T2 = y->p_left;

	y->p_left = x;
	x->p_right = T2;

	updateHeight(x);
	updateHeight(y);

	return y;
}

NODE* balance(NODE* p) {
	updateHeight(p);
	int balanceFactor = getBalance(p);

	if (balanceFactor > 1) {
		if (getBalance(p->p_left) < 0)
			p->p_left = rotateLeft(p->p_left);
		return rotateRight(p);
	}

	if (balanceFactor < -1) {
		if (getBalance(p->p_right) > 0)
			p->p_right = rotateRight(p->p_right);
		return rotateLeft(p);
	}

	return p;
}
//---------------------------------------------------------------------------------------//



// 1. Tạo node mới 
NODE* createNode(int data) {
	NODE* p = new NODE{ data, nullptr, nullptr, 0 };
	return p;
}


// 2. Thêm node
void Insert(NODE*& pRoot, int x) {
	if (!pRoot) {
		pRoot = createNode(x);
		return;
	}

	if (x < pRoot->key)
		Insert(pRoot->p_left, x);
	else if (x > pRoot->key)
		Insert(pRoot->p_right, x);
	else
		return;

	pRoot = balance(pRoot);
}

NODE* findMin(NODE* p) {
	while (p && p->p_left)
		p = p->p_left;
	return p;
}

// 3. Xóa node
void Remove(NODE*& pRoot, int x) {
	if (!pRoot) return;

	if (x < pRoot->key)
		Remove(pRoot->p_left, x);
	else if (x > pRoot->key)
		Remove(pRoot->p_right, x);
	else {
		if (!pRoot->p_left || !pRoot->p_right) {
			NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
			delete pRoot;
			pRoot = temp;
		}
		else {
			NODE* temp = findMin(pRoot->p_right);
			pRoot->key = temp->key;
			Remove(pRoot->p_right, temp->key);
		}
	}

	if (pRoot)
		pRoot = balance(pRoot);
}

// 4. kiểm tra cây AVL?
bool isAVL(NODE* pRoot) {
	if (!pRoot) return true;

	int balanceFactor = getBalance(pRoot);
	if (abs(balanceFactor) > 1)
		return false;

	return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}