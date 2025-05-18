#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

struct Company;
struct Node;
struct HashTable;

long long hashString(string& company_name);

void insert(HashTable* table, Company& company);

Company* search(HashTable* table, string& company_name);

HashTable* createHashTable(vector<Company>& list_company);

void deleteHashTable(HashTable* table);

vector<Company> readCompany(string& file_name);

#endif