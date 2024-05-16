#pragma once
using namespace std;
class TreeNode {
private:
	string word;
	TreeNode* left;
	TreeNode* right;
	linklist links;
	int links_count;
public:
	TreeNode()
	{
		word = "";
		left = right = nullptr;
		links_count = 0;
	}
	TreeNode(const string word, const string link)
	{
		this->word = word;
		left = right = nullptr;
		links.insert(link);
		links_count++;
	}
	void setword(const string word)
	{
		this->word = word;
	}
	void setleft(TreeNode* left)
	{
		this->left = left;
	}
	void setright(TreeNode* right)
	{
		this->right = right;
	}
	const string getword()
	{
		return this->word;
	}
	TreeNode* getleft()
	{
		return this->left;
	}
	TreeNode* getright()
	{
		return this->right;
	}
	void addlink(const string link)
	{
		if (links.insert(link))
		{
			links_count++;
		}
	}
	void setlinks(Node* head)
	{
		links.deletelinks();
		links_count = 0;
		Node* temp = head->getnext();
		while (temp != nullptr)
		{
			links.insert(temp->getdata());
			temp = temp->getnext();
			links_count++;
		}
	}
	linklist getlinks()
	{
		return this->links;
	}
	void showlinks()
	{
		links.print();
	}
	int totallinks()
	{
		return this->links_count;
	}
	Node* getheadoflinklist()
	{
		return links.gethead();
	}
	bool isLeaf()
	{
		if (left == nullptr && right == nullptr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

};