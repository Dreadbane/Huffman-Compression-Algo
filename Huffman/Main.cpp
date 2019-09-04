#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <bits/stdc++.h> 

using namespace std;

class Node{
public:
	char ch;
	int freq;
	Node* left;
	Node* right;
	Node(char ch,int freq){
		this->freq=freq;
		this->ch=ch;
		left=NULL;
		right=NULL;
	}

	Node(){
		ch=' ';freq=0;
	}
};

class Node_Compare{
public:
	bool operator()(Node a,Node b){
		return a.freq<b.freq;
	}
};

//Use this function only to view to view if the map is created properly or not;
//don't include in actual code
void print_map(unordered_map<char,int> m){
	unordered_map<char,int>:: iterator itr;
	for(itr=m.begin();itr!=m.end();itr++)
		cout<<itr->first<<" "<<itr->second<<endl;
}

void create_Nodes(unordered_map<char,int> m,Node* arr){
	int l=m.size();

	int i=0;
	unordered_map<char,int>:: iterator itr;
	for(itr=m.begin();itr!=m.end();itr++){
		arr[i].ch=itr->first;arr[i++].freq=itr->second;
	}

	//return arr;
}

void create_map(std::unordered_map<char,int> &map){
	string file_path="";	
	cout<<"Enter path of file: ";
	getline(cin,file_path);

	ifstream ob;
	ob.open(file_path);
	//Execute if the file opened successfully
	if(!ob){
		cout<<"File couldn't be opened!"<<endl;
		return ;
	}

	//If file opened 
	while(!ob.eof()) {
	    /* code */
	    char c=ob.get();

	    //if character is not present in map, insert it
	    if(map.find(c)==map.end())
	    	map[c]=0;

	    //If character is already present then increment it's count by 1
	    map[c]++;
	}

	ob.close();

}

void create_pq(std::priority_queue<Node,vector<Node>,Node_Compare> &pq,Node* arr,int l){
	for(int i=0;i<l;i++)
		pq.push(arr[i]);
}

void create_Huff_codes(struct Node *node,unordered_map<char,string> &huffman_codes,string h){

	if(node->right==NULL && node->left==NULL){
		huffman_codes[node->ch]=h;
		node->huff_code=h;
		cout<<"Huf!"<<endl;
		return;
	}

	if(node->left!=NULL){
		create_Huff_codes(node->left,huffman_codes,"0"+h);
	}

	if(node->right!=NULL){
		create_Huff_codes(node->right,huffman_codes,"1"+h);	
	}
}

Node create_tree(priority_queue<Node,vector<Node>,Node_Compare> &pq){
	while(pq.size()!=1) {
	    /* code */
	    Node par;
	    Node left_child=pq.top();pq.pop();

	    Node right_child=pq.top();pq.pop();

	    par.freq=(left_child.freq)+(right_child.freq);

	    par.left=&left_child;par.right=&right_child;
	    //cout<<&par<<" "<<par.left<<par.right<<endl;
	    //cout<<par.left->ch<<" "<<par.right->ch<<endl;
	    pq.push(par);
	}

	Node* res=pq.top();
	return res;
}

int main(int argc, char const *argv[])
{
	unordered_map<char,int> map;
	create_map(map);
	//print_map(*map);

	Node arr[map.size()];
	create_Nodes(map,arr);

	for(Node n : arr)
		cout<<n.ch<<" "<<n.freq<<endl;

	int l=map.size();
	priority_queue<Node,vector<Node>,Node_Compare> pq;
	create_pq(pq,arr,l);
	Node* root=create_tree(pq);
	
	return 0;
}
