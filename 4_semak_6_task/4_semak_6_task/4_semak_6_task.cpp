// 4_semak_6_task.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <vector>
#include <iostream>

using namespace std;

class DictionaryTree
{
private:
	struct TreeElem
	{
		vector<char> info = vector<char>();
		TreeElem* left;
		TreeElem* right;
		int count;
		TreeElem():left(nullptr), right(nullptr), count(0){}
		TreeElem(vector<char> word)
		{
			info = word;
			count = 1;
			left = nullptr;
			right = nullptr;
		}
	};

	TreeElem* root;

	int searchOfWord(TreeElem *root, vector<char> word)
	{
		if (!root){ return 0; }
		if (root->info == word){
			return root->count;
		}
		if (root->info < word){
			return searchOfWord(root->left, word);
		}
		else{
			return searchOfWord(root->right, word);
		}
	}

	void add(TreeElem*root, vector<char> word)
	{
		if (root->info == word){
			root->count++;
			return;
		}
		if (root->info < word){
			if (root->right == nullptr){
				root->right = new TreeElem(word);
				return;
			}
			add(root->right, word);
		}
		else{
			if (root->left == nullptr){
				root->left = new TreeElem(word);
				return;
			}
			add(root->left, word);
		}
	}

	void remove(TreeElem *& root, vector<char> word)
	{
		if (root->info == word){
			root->count--;
			return;
		}
		if (root->info > word) {
			if (root->left->info == word) {
				if (root->left->count == 1){
					delete root->left;
					root->left = nullptr;
					return;
				}
				else{
					root->left->count--;
					return;
				}
			}
			remove(root->left, word);
		}
		else {
			if (root->right->info == word) {
				if (root->right->count == 1){
					delete root->right;
					root->right = nullptr;
					return;
				}
				else{
					root->right->count--;
					return;
				}
			}
			remove(root->right, word);
		}
	}

	int countOfWords(TreeElem* root)
	{
		if (!root){ return 0; }
		return root->count + countOfWords(root->left) + countOfWords(root->right);
	}

	void write(TreeElem* root)
	{
		if (!root){ return; }
		write(root->left);
		cout << " '";
		for (int i = 0; i < root->info.size(); i++){
			cout << root->info[i];
		}
		cout << "' ";
		cout << "(" << root->count << ")";
		write(root->right);
	}

	void deleteAll(TreeElem * root)
	{
		if (!root){ return; }
		deleteAll(root->left);
		deleteAll(root->right);
		delete root;
	}

	TreeElem * copy(TreeElem* root)
	{
		if (!root){ return nullptr; }
		TreeElem* t = new TreeElem(root->info);
		t->left = copy(root->left);
		t->right = copy(root->right);
		t->count = root->count;
		return t;
	}
public:
	DictionaryTree()
	{
		root = new TreeElem();
	}

	DictionaryTree(vector<char> word)
	{
		root = new TreeElem(word);
	}

	~DictionaryTree()
	{
		deleteAll(root);
	}

	DictionaryTree& operator= (DictionaryTree const & dictionary)
	{
		cout << "AssignOper" << endl;
		if (this == &dictionary) { return *this; }
		this->root = copy(dictionary.root);
		return *this;
	}

	int searchOfWord(vector<char> word)
	{
		return searchOfWord(root, word);
	}

	void add(vector<char> word)
	{
		add(root, word);
	}

	void remove(vector<char> word)
	{
		remove(root, word);
	}

	int countOfWords()
	{
		return countOfWords(root);
	}

	void write()
	{
		write(root);
		cout << endl;
	}
};

int main()
{
	vector<char> v[7];
	v[0].push_back('t');
	v[0].push_back('a');
	v[0].push_back('k');
	v[0].push_back('e');
	v[1].push_back('m');
	v[1].push_back('y');
	v[2].push_back('p');
	v[2].push_back('r');
	v[2].push_back('o');
	v[2].push_back('g');
	v[2].push_back('r');
	v[2].push_back('a');
	v[2].push_back('m');
	v[3].push_back('a');
	v[4].push_back('n');
	v[4].push_back('u');
	v[4].push_back('m');
	v[4].push_back('b');
	v[4].push_back('e');
	v[4].push_back('r');
	v[5].push_back('s');
	v[5].push_back('i');
	v[5].push_back('x');
	v[6].push_back('p');
	v[6].push_back('l');
	v[6].push_back('e');
	v[6].push_back('a');
	v[6].push_back('s');
	v[6].push_back('e');
	cout << "Create Dictionary with word 'program'" << endl;
	DictionaryTree* tree = new DictionaryTree(v[2]);
	tree->write();
	cout << endl;
	tree->add(v[0]); 
	tree->add(v[1]); 
	tree->add(v[3]); 
	tree->add(v[4]); 
	tree->add(v[5]); 
	tree->add(v[6]);
	cout << "Dictionary after add words: 'my', 'a', 'please', 'six', 'take', 'number' " << endl;
	tree->write();
	cout << endl;
	cout << "Find word 'program'. Amount = " << tree->searchOfWord(v[2]) << endl;
	cout << endl;
	vector <char> v1 = vector<char>();
	v1.push_back('m');
	cout << "Find word 'm'. Amount = " << tree->searchOfWord(v1) << endl;
	cout << endl;
	cout << "Delete word 'a' from Dictionary" << endl;
	tree->remove(v[3]);
	tree->write();
	cout << endl;
	cout << "Delete word 'please' from Dictionary" << endl;
	tree->remove(v[6]);
	tree->write();
	cout << endl;
	cout << "Delete word 'number' from Dictionary" << endl;
	tree->remove(v[4]);
	tree->write();
	cout << endl;
	cout << "Delete word 'six' from Dictionary" << endl;
	tree->remove(v[5]);
	tree->write();
	cout << endl;
	cout << "Count of words in Dictionary = " << tree->countOfWords() << endl;
	cout << endl;
	cout << "Add to Dictionary word 'program'" << endl;
	tree->add(v[2]);
	tree->write();
	cout << endl;

	return 0;
}

