#pragma once
using namespace std;
class BST {
private:
	TreeNode* root;
	int compare(const string word1, const string word2)
	{
		int cmp;
		int i, j;
		for (i = 0, j = 0; word1[i] != '\0' && word2[j] != '\0'; i++, j++)
		{
			if (word1[i] > word2[j])
			{
				cmp = 1;
				break;
			}
			else if (word1[i] < word2[j])
			{
				cmp = -1;
				break;
			}
			else
			{
				cmp = 0;
			}
		}
		if (cmp == 0)
		{
			if (word1[i] == '\0' && word2[j] != '\0')
			{
				cmp = -1;
			}
			else if (word2[j] == '\0' && word1[i] != '\0')
			{
				cmp = 1;
			}
		}
		return cmp;
	}
	void free_tree(TreeNode* root)
	{
		if (root != nullptr)
		{
			free_tree(root->getleft());
			free_tree(root->getright());
			//cout << root->getword() << " deleted" << endl;
			delete root;
		}
	}
	TreeNode* insert(TreeNode* root, const string word)
	{
		string link;
		cout << "Enter link : ";
		cin.ignore();
		getline(cin, link);
		if (root == nullptr)
		{
			TreeNode* newNode = new TreeNode(word, link);
			root = newNode;
			return root;
		}
		else
		{
			int c = compare(word, root->getword());
			if (c == -1)
			{
				root->setleft(insert(root->getleft(), word));
			}
			else if (c == 1)
			{
				root->setright(insert(root->getright(), word));
			}
			else
			{
				root->addlink(link);
				return root;
			}
			return root;
		}
	}
	TreeNode* deleteword(TreeNode* root, const string word)
	{

		TreeNode* t;
		int cmp = compare(word, root->getword());

		if (cmp == -1)
		{
			t = deleteword(root->getleft(), word);
			root->setleft(t);
		}
		else if (cmp == 1)
		{
			t = deleteword(root->getright(), word);
			root->setright(t);
		}
		else if (root->getleft() != NULL && root->getright() != NULL)
		{
			TreeNode* minNode;
			minNode = findmin(root->getright());
			root->setword(minNode->getword());
			root->setlinks(minNode->getheadoflinklist());
			t = deleteword(root->getright(), (minNode->getword()));
			root->setright(t);
		}
		else
		{
			TreeNode* deleteNode = root;
			if (root->getleft() == NULL)
				root = root->getright();
			else if (root->getright() == NULL)
				root = root->getleft();
			else
				root = NULL;

			delete deleteNode;

		}
		return root;
	}
	TreeNode* findmin(TreeNode* root)
	{
		if (root != nullptr)
		{
			if (root->getleft() == nullptr)
			{
				return root;
			}
			return findmin(root->getleft());
		}
	}
public:
	BST()
	{
		this->root = nullptr;
	}
	bool createBST(const string filename)
	{
		fstream inout;
		inout.open(filename, ios::in);
		if (!inout.is_open())
		{
			return false;
		}
		else
		{
			string line, link, emptyline, word = "";
			char id[3];
			while (!inout.eof())
			{
				inout >> id;
				getline(inout, link);
				getline(inout, line);
				getline(inout, emptyline);
				for (int i = 0; line[i] != '\0'; i++)
				{
					if (line[i] != ' ')
					{
						word += line[i];
					}
					if (line[i] == ' ' || line[i + 1] == '\0')
					{
						if (this->root == nullptr)
						{
							root = new TreeNode(word, link);
						}
						else
						{
							TreeNode* p, * q;
							p = q = root;
							bool exists = false;
							while (p != nullptr)
							{
								q = p;
								int c = compare(word, p->getword());
								if (c == -1)
								{
									p = p->getleft();
								}
								else if (c == 1)
								{
									p = p->getright();
								}
								else
								{
									p->addlink(link);
									exists = true;
									break;
								}
							}
							if (!exists)
							{
								TreeNode* newNode = new TreeNode(word, link);
								int c = compare(word, q->getword());
								if (c == -1)
								{
									q->setleft(newNode);
								}
								else if (c == 1)
								{
									q->setright(newNode);
								}
							}
						}
						word = "";
					}
				}
			}
			inout.close();
			return true;
		}
	}
	void insert(const string word)
	{
		root = insert(this->root, word);
	}
	void search(const string word)
	{
		TreeNode* p = this->root;
		bool find = false;
		while (p != nullptr && !find)
		{
			int c = compare(word, p->getword());
			if (c == -1)
			{
				p = p->getleft();
			}
			else if (c == 1)
			{
				p = p->getright();
			}
			else
			{
				find = true;
				break;
			}
		}
		if (find)
		{
			cout << p->totallinks() << " result(s) found" << endl;
			p->showlinks();
		}
		else
		{
			cout << "Opps...no results found!!!" << endl;
		}
	}
	/*void deleteword(const string word)
	{
		if (this->root != nullptr)
		{
			TreeNode* curr = this->root;
			TreeNode* prev = nullptr;
			while (curr != nullptr)
			{
				int c = compare(word, curr->getword());
				if (c == -1)
				{
					prev = curr;
					curr = curr->getleft();
				}
				else if (c == 1)
				{
					prev = curr;
					curr = curr->getright();
				}
				else
				{
					break;
				}
			}
			if (prev == nullptr && word == curr->getword())
			{
				if (curr->isLeaf())
				{
					delete curr;
				}
			}
			else
			{
				if (curr->isLeaf())
				{
					delete curr;
				}
				else if (curr->getleft() != nullptr && curr->getright() != nullptr)
				{
					TreeNode* minNode = findmin(curr->getright());
					curr->setword(minNode->getword());
					curr->setlinks(minNode->getheadoflinklist());
					deleteword(minNode->getword());
				}
				else
				{
					TreeNode* nodetobedeleted = curr;
					int c = compare(curr->getword(), prev->getword());
					if (c == -1)
					{
						if (curr->getleft() == nullptr)
						{
							prev->setleft(curr->getright());
						}
						else
						{
							prev->setleft(curr->getleft());
						}
					}
					else if (c == 1)
					{
						if (curr->getleft() == nullptr)
						{
							prev->setright(curr->getright());
						}
						else
						{
							prev->setright(curr->getleft());
						}
					}
					delete nodetobedeleted;
				}
			}
		}
	}*/
	void deleteword(const string word)
	{
		root = deleteword(this->root, word);
	}


	~BST()
	{
		free_tree(this->root);
		this->root = nullptr;
	}
};