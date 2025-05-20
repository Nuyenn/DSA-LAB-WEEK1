#include "HashTable.h"



struct Company {
	string name;
	string profit_tax;
	string address;
};

struct Node {
	Company data;
	Node* next;
};

struct HashTable {
	vector<Node*> buckets;
	int size;
	HashTable(int sz = 2000) {
		size = sz;
		buckets = vector<Node*>(sz, nullptr);
	}
};


long long hashString(string& company_name) {
	const int p = 31;
	const int m = 2000;
	string s = company_name;

	// Lấy 20 kí tự cuối 
	if (s.length() > 20) {
		s = s.substr(s.length() - 20);
	}

	long long hash = 0;
	long long power = 1;

	for (int i = 0; i < s.length(); i++) {
		hash = (hash + (s[i] * power) % m) % m;
		power = (power * p) % m;
	}

	return hash;
}

//thêm cty vào hash
void insert(HashTable* table, Company& company) {
	int index = hashString(company.name);
	Node* newNode = new Node{ company, table->buckets[index] };
	table->buckets[index] = newNode;
}

//tìm cty theo tên
Company* search(HashTable* table, string& company_name) {
	int index = hashString(company_name);
	Node* node = table->buckets[index];

	while (node) {
		if (node->data.name == company_name) {
			return &node->data;
		}
		node = node->next;
	}
	return nullptr;
}

HashTable* createHashTable(vector<Company>& list_company) {
	HashTable* table = new HashTable();
	for (int i = 0; i < list_company.size(); i++) {
		insert(table, list_company[i]);
	}
	return table;
}

void deleteHashTable(HashTable* table) {
	for (int i = 0; i < table->buckets.size(); i++) {
		Node* cur = table->buckets[i];
		while (cur) {
			Node* temp = cur;
			cur = cur->next;
			delete temp;
		}
	}
	delete table;
}

//đọc danh sách cty từ file input
vector<Company> readCompany(string& file_name) {
	vector<Company> companies;
	ifstream fin(file_name);
	string line;

	getline(fin, line);		//bỏ dòng đầu 

	while (getline(fin, line)) {
		stringstream ss(line);
		string name, tax, address;

		getline(ss, name, '|');
		getline(ss, tax, '|');
		getline(ss, address);

		Company c;
		c.name = name;
		c.profit_tax = tax;
		c.address = address;

		companies.push_back(c);
	}
	return companies;
}


int main(int argc, char* argv[]) {
	if (argc != 4) {
		return 1;
	}

	string mst_file = argv[1];
	string input_file = argv[2];
	string output_file = argv[3];

	vector<Company> companies = readCompany(mst_file);

	HashTable* table = createHashTable(companies);

	ifstream fin(input_file);
	ofstream fout(output_file);

	string name;

	while (getline(fin, name)) {
		Company* result = search(table, name);
		if (result) {
			fout << result->name << "|" << result->profit_tax << "|" << result->address << endl;
		}
		else {
			fout << name << "NOT FOUND" << endl;
		}
	}

	deleteHashTable(table);

	return 0;
}