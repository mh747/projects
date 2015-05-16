#include<iostream>
#include "LinkedList.cpp"
#include "HuffTree.h"
#include "TreeNode.cpp"
using namespace std;

HuffTree::HuffTree()
{
    root = NULL;
}

HuffTree::HuffTree(const HuffTree &other)
{
    //Copy root first
    if(other.root != NULL) {
        TreeNode *newRoot = new TreeNode;
        newRoot->set_char(other.root->get_char());
        newRoot->set_freq(other.root->get_freq());
        root = newRoot; 
        copy_tree(root,other.root);
    } else {
        root = NULL;
    }
}

HuffTree::HuffTree(HuffTree &ht1, HuffTree &ht2)
{
    //Constructor for combining two trees
    
    //Creating root (which will be null char and combined freq)
    TreeNode *newRoot = new TreeNode;
    newRoot->set_char('\0');
    newRoot->set_freq(ht1.get_freq()+ ht2.get_freq());
    if(ht1.get_freq() < ht2.get_freq()) {
        newRoot->set_left(ht1.root);
        newRoot->set_right(ht2.root);
    } else {
        newRoot->set_left(ht2.root);
        newRoot->set_right(ht1.root);
    }
    root = newRoot;
}

void HuffTree::copy_tree(TreeNode *node, TreeNode *otherNode)
{
    if(otherNode->get_left() != NULL) {
        TreeNode *newNode = new TreeNode;
        newNode->set_char(otherNode->get_left()->get_char());
        newNode->set_freq(otherNode->get_left()->get_freq());
        node->set_left(newNode);
        copy_tree(newNode,otherNode->get_left());
    }
    if(otherNode->get_right() != NULL) {
        TreeNode *newNode = new TreeNode;
        newNode->set_char(otherNode->get_right()->get_char());
        newNode->set_freq(otherNode->get_right()->get_freq());
        node->set_right(newNode);
        copy_tree(newNode,otherNode->get_right());
    }

}
        

HuffTree::~HuffTree()
{
    destroy_tree(root);
}

void HuffTree::destroy_tree(TreeNode *node)
{
    if(node != NULL) {
        if(node->get_left() != NULL) {
            destroy_tree(node->get_left());
        }
        if(node->get_right() != NULL) {
            destroy_tree(node->get_right());
        }
        delete node;
    }
}

void HuffTree::insert(char c, int frequency)
{
    if(root != NULL) {
        insert(c,frequency,root);
    } else {
        TreeNode *newNode = new TreeNode;
        newNode->set_char(c);
        newNode->set_freq(frequency);
        root = newNode;
    }
}

void HuffTree::insert(char c, int frequency, TreeNode *node)
{
    if(node->get_freq() > frequency) {
        if(node->get_left() != NULL) {
            insert(c,frequency,node->get_left());
        } else {
            TreeNode *newNode = new TreeNode;
            newNode->set_char(c);
            newNode->set_freq(frequency);
            node->set_left(newNode);
            root->set_freq(frequency + root->get_freq());
        }
    } else if(node->get_freq() <= frequency) {
        if(node->get_right() != NULL) {
            insert(c,frequency,node->get_right());
        } else {
            TreeNode *newNode = new TreeNode;
            newNode->set_char(c);
            newNode->set_freq(frequency);
            node->set_right(newNode);
            root->set_freq(frequency + root->get_freq());
        }
    }
}

int HuffTree::get_freq() const
{
    return root->get_freq();
}

void HuffTree::alternate_output()
{
    int level = 0;
    cout << "-------------------------------------------------------\n"
         << "-----DUMPING TREE--------------------------------------\n"
         << "-------------------------------------------------------\n\n";
    alternate_output(root,level);
    cout << "-------------------------------------------------------\n\n";
}

void HuffTree::alternate_output(TreeNode *node, int level)
{
    if(node != NULL) {
        alternate_output(node->get_right(), (level+1)); 
        for(int i=0; i<(level-1); i++)
            cout << "            ";
        if(level > 0)
            cout << "    --------";
        if(node->get_char() == '\0')
            cout << "\\0";
        else 
            cout << " " << node->get_char();
        cout << "," << node->get_freq() << "\n";
        alternate_output(node->get_left(), (level+1));
    }
} 
        
void HuffTree::output_tree() const
{
    cout << "-------------------------------------------------------\n"
         << "-----DUMPING TREE--------------------------------------\n"
         << "-------------------------------------------------------\n\n";
    output_tree(root);
    cout << "-------------------------------------------------------\n\n";
}

void HuffTree::output_tree(TreeNode *node) const
{
    if(node != NULL) {
        cout << "left child\n";
        output_tree(node->get_left());
        cout << "Node";
        if(node == root)
            cout << "\tROOT NODE";
        cout << "\n\tChar: " << node->get_char() << "\n\tFreq: " << node->get_freq()
             << "\n\n";
        cout << "right child\n";
        output_tree(node->get_right());
    }
}

void HuffTree::operator=(const HuffTree &ht)
{
    //Copy root first
    if(ht.root != NULL) {
        TreeNode *newRoot = new TreeNode;
        newRoot->set_char(ht.root->get_char());
        newRoot->set_freq(ht.root->get_freq());
        root = newRoot;
        copy_tree(root,ht.root);
    } else {
        root = NULL;
    } 
}

bool HuffTree::operator>(const HuffTree &ht)
{
    return get_freq()>ht.get_freq();
}

bool HuffTree::operator>=(const HuffTree &ht)
{
    return get_freq()>=ht.get_freq();
}

bool HuffTree::operator<(const HuffTree &ht)
{
    return get_freq()<ht.get_freq();
}

bool HuffTree::operator<=(const HuffTree &ht)
{
    return get_freq()<=ht.get_freq();
}

int main()
{
    HuffTree *ht = new HuffTree;
    ht->insert('g',5);
    ht->insert('a',3);
    ht->insert('b',8);

    HuffTree *ht2 = new HuffTree;
    ht2->insert('h',7);

    HuffTree *ht3 = new HuffTree;
    ht3->insert('j',1);

    LinkedList<HuffTree> htlist;

    htlist.push_back(*ht);
    htlist.push_back(*ht2);
    htlist.push_back(*ht3);

    LinkedList<HuffTree>::list_iterator li;
    for(li=htlist.begin(); li!=htlist.end(); li++)
        li.val().output_tree();

    cout << "Sorting list of trees...\n\n";
    htlist.sort_list();
    for(li=htlist.begin(); li!=htlist.end(); li++)
        li.val().output_tree();


    cout << "Starting new test:\n\n\n";

    HuffTree *ht4 = new HuffTree;
    ht4->insert('i',4);

    ht4->output_tree();

    HuffTree *ht5 = new HuffTree;
    ht5->insert('j',5);

    ht5->output_tree();

    HuffTree *newTree = new HuffTree(*ht4,*ht5);

    newTree->alternate_output();
    return 0;
}
