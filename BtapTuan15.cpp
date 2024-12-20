#include<bits/stdc++.h>
using namespace std;
struct Node {
    string title;                
    int page;           
    vector<Node*> children;      
    
    Node(string t) {
		title = t;
		page = 0;
	} 
    Node(string t, int p) {
    	title = t;
    	page = p;
    }
};
int chaptersNum(Node* book) {
	if(book == nullptr) return -1; 
	int count = 0;
	for(Node* chap : book->children) {
		count++;
	}
	return count;
}
Node* longestChapter(Node* book) {
    if (book->children.empty()) return nullptr; 
    Node* res = book->children[0];
    for (Node* chap : book->children) {
        if (chap->page > res->page) {
            res = chap;
        }
    }
    return res;
}
void updatePage(Node* parent, int deleted) {
	parent->page -= deleted;
}
int deletedPage = 0;
bool deleteNode(Node* parent, string deleted) {
    for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
        if ((*it)->title == deleted) {
        	deletedPage = (*it)->page;
            delete *it; 
            parent->children.erase(it);
            updatePage(parent,deletedPage);
            return true;
        }
        if (deleteNode(*it, deleted)) {
        	updatePage(parent,deletedPage);
            return true;
        }
    }
    return false;
}
int main() {
    Node* book = new Node("Book");
    Node* chapter1 = new Node("Chapter 1", 14);
    Node* chapter2 = new Node("Chapter 2", 20);
    Node* section1 = new Node("Section 1.1", 6);
    Node* section2 = new Node("Section 1.2", 8);
    book->children.push_back(chapter1);
    book->children.push_back(chapter2);
    chapter1->children.push_back(section1);
    chapter1->children.push_back(section2);
    book->page = 34;
    cout << "Total chapters: " << chaptersNum(book) << endl;
    Node* longest = longestChapter(book);
    if (longest) {
        cout << "Longest chapter: " << longest->title << " with " << longest->page << " pages." << endl;
    }
    if (deleteNode(book, "Section 1.1") ) {
        cout << "Section 1.1 deleted." << endl;
        cout << "Chapters 1's pages after deleted section 1 :" <<chapter1->page<<endl;
        cout << "Book's pages after deleted section 1 :" <<book->page;
    }

    return 0;
}
