//
// Created by 16979 on 2022/7/5.
//

#include "binaryTree.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/* ================================== Node =================================== */
void deleteNode (Node * root) {
    if (root->leftSubtree()!=nullptr) {
        deleteNode(root->leftSubtree());
    }
    if (root->rightSubtree()!=nullptr){
        deleteNode(root->rightSubtree());
    }
    delete root;
}

Node::Node(const std::string &str, int num, Node *left, Node *right) {
    this->num=num;
    this->str=str;
    this->left=left;
    this->right=right;
}

Node* Node::leftSubtree() const{
    return this->left;
}

void Node::setleft(Node *n) {
    if(this->leftSubtree()!=nullptr){
        deleteNode(this->leftSubtree());
    }
    left = n;
}

Node* Node::rightSubtree() const{
    return this->right;
}

void Node::setright(Node *n) {
    if(this->rightSubtree()!=nullptr){
        deleteNode(this->rightSubtree());
    }
    right = n;
}

string Node::getstr() const {
    return this->str;
}

int Node::getnum() const {
    return this->num;
}

void Node::incnum() {
    (this->num)++;
}

Node *Node::mergeNodes(Node *leftNode, Node *rightNode) {
      Node* node =new Node(leftNode->str + rightNode->str, leftNode->num + rightNode->num, leftNode, rightNode);
      return node;
}

/* =============================== Binary Tree =============================== */

BinaryTree::BinaryTree(Node *rootNode){
    root=rootNode;
}

void helperDestructor(Node* root){
    if (root->leftSubtree()!=nullptr) {
        helperDestructor(root->leftSubtree());
    }
    if (root->rightSubtree()!=nullptr){
        helperDestructor(root->rightSubtree());
    }
    delete root;
}

BinaryTree::~BinaryTree() {
    helperDestructor(this->root);
}

string find_helper(Node*root,const string &s){
    if(root==nullptr){
        return"-1";
    }
    else if(root->getstr()==s){
        return "";
    }
    else{
        string left=find_helper(root->leftSubtree(),s);
        if(left!="-1"){
            return "0"+left;
        }
        string right = find_helper(root->rightSubtree(),s);
        if(right!="-1"){
            return "1"+right;
        }
    }
    return "-1";
}

string BinaryTree::findPath(const string &s) const{
    return find_helper(root,s);
}

int getHight(Node* root){
    if (root == nullptr){
        return 0;
    }
    int leftHigh = getHight(root->leftSubtree());
    int rightHigh = getHight(root->rightSubtree());
    int maxHigh = leftHigh >= rightHigh ? leftHigh + 1 : rightHigh + 1;
    return maxHigh;
}

int BinaryTree::depth() const {
    return getHight(root);
}

void helperPreorder(Node* root,vector<int>& res){
    if (root == nullptr){
        return;
    }
    //将节点的值存到数组中
    res.push_back(root->getnum());
    //前序遍历左子树
    helperPreorder(root->leftSubtree(), res);
    //前序遍历右子树
    helperPreorder(root->rightSubtree(), res);
}

void BinaryTree::preorder_num() const {
    if(root == nullptr){
        return;
    }
    else{
        vector<int> res;
        helperPreorder(root, res);
        int i;
        for(i=0;i<res.size();i++){
            cout<<res[i]<<" ";
        }
    }
}

void helperInorder(Node* root, vector<string>& res)
{
    //如果节点为空，则直接返回
    if (root == nullptr){
        return;
    }
    //中序遍历左子树
    helperInorder(root->leftSubtree(), res);
    //将节点的值存到数组中
    res.push_back(root->getstr());
    //中序遍历右子树
    helperInorder(root->rightSubtree(), res);
}

void helperInorder2(Node* root, vector<int>& res)
{
    //如果节点为空，则直接返回
    if (root == nullptr){
        return;
    }
    //中序遍历左子树
    helperInorder2(root->leftSubtree(), res);
    //将节点的值存到数组中
    res.push_back(root->getnum());
    //中序遍历右子树
    helperInorder2(root->rightSubtree(), res);
}

int BinaryTree::sum() const {
    if(root == nullptr){
        return 0;
    }
    else{
        vector<int> res;
        int sum=0;
        helperInorder2(root, res);
        int i;
        for(i=0;i<res.size();i++){
            sum=sum+res[i];
        }
        return sum;
    }
}

void BinaryTree::inorder_str() const {
    if(root == nullptr){
        return;
    }
    else{
        vector<string> res;
        helperInorder(root, res);
        int i;
        for(i=0;i<res.size();i++){
            cout<<res[i]<<" ";
        }
    }
}

void helperPostorder(Node* root, vector<int>& res)
{
    //如果节点为空，则直接返回
    if (root == nullptr){
        return;
    }
    //后序遍历左子树
    helperPostorder(root->leftSubtree(), res);
    //后序遍历右子树
    helperPostorder(root->rightSubtree(), res);
    //将节点的值存到数组中
    res.push_back(root->getnum());
}

void BinaryTree::postorder_num() const {
    if(root == nullptr){
        return;
    }
    else{
        vector<int> res;
        helperPostorder(root, res);
        int i;
        for(i=0;i<res.size();i++){
            cout<<res[i]<<" ";
        }
    }
}

int helperSum(Node* root){
    if(root==nullptr){
        return 0;
    }
    int left = helperSum(root->leftSubtree());
    int right = helperSum(root->rightSubtree());
    if(left>=right){
        return right+root->getnum();
    }
    else {
        return left+root->getnum();
    }
}

bool BinaryTree::allPathSumGreater(int sum) const {
    int min=helperSum(root);
    if(min>sum){
        return true;
    }
    else{
        return false;
    }
}

bool helperCovered(Node* rootCovered, Node* tree) {
    if(rootCovered==nullptr) {
        return true;
    }
    else if(tree==nullptr) {
        return false;
    }
    else if(rootCovered->getnum()!=tree->getnum()) {
        return false;
    }
    else{
        return helperCovered(rootCovered->leftSubtree(),tree->leftSubtree())&&helperCovered(rootCovered->rightSubtree(),tree->rightSubtree());
    }
}

bool BinaryTree::covered_by(const BinaryTree &tree) const {
    return helperCovered(this->root,tree.root);
}

void contain_helper(Node* rootContained, Node* root,vector<int>& res){
    if(helperCovered(rootContained,root)){
        res.push_back(1);
    }
    if(root== nullptr){
        return ;
    }
    contain_helper(rootContained,root->leftSubtree(),res);
    contain_helper(rootContained,root->rightSubtree(),res);
}

bool BinaryTree::contained_by(const BinaryTree &tree) const {
    int judge=0;
    vector<int> res;
    contain_helper(this->root,tree.root,res);
    if(!res.empty()){
        judge=1;
    }
    if(judge==1){
        return true;
    }
    else{
        return false;
    }
}

void copy_help(Node* initial, Node* copy) {
    if (copy==nullptr) {
        return;
    }
    if (initial->leftSubtree()!=nullptr){
        Node* left=new Node(initial->leftSubtree()->getstr(), initial->leftSubtree()->getnum(), nullptr, nullptr);
        copy->setleft(left);
    }
    if (initial->rightSubtree()!=nullptr) {
        Node* right=new Node(initial->rightSubtree()->getstr(), initial->rightSubtree()->getnum(), nullptr, nullptr);
        copy->setright(right);
    }
    copy_help(initial->leftSubtree(), copy->leftSubtree());
    copy_help(initial->rightSubtree(), copy->rightSubtree());
}

BinaryTree BinaryTree::copy() const {
    Node* copy = new Node(root->getstr(), root->getnum(), nullptr, nullptr);
    copy_help(root, copy);
    return {copy};
}
