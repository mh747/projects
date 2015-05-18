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
            cout << "      ";
        if(level > 0)
            cout << "    --";
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

string HuffTree::get_huff_string(char c)
{
    string huff_string = "";
    string s = "";
    if(root != NULL) {
        get_huff_string(root,c,huff_string,s);
    }
    return s;
}

void HuffTree::get_huff_string(TreeNode *node, char c, string huff_string, string &s)
{
    if(node != NULL) {
        if(node->get_left() == NULL && node->get_right() == NULL && node->get_char()==c) {            s = huff_string;
        } else {
            get_huff_string(node->get_left(),c,huff_string+'0',s);
            get_huff_string(node->get_right(),c,huff_string+'1',s);
        }
     }
}

char HuffTree::get_huff_char(string huff_string)
{
    char c = '\0';
    TreeNode *pos = root;

    for(int i=0; i<huff_string.size(); i++) {
        if(huff_string[i] == '0') {
            pos = pos->get_left();
        } else if(huff_string[i] == '1') {
            pos = pos->get_right();
        }

    }
    if(pos != NULL && pos->get_left() == NULL && pos->get_right() == NULL) {
        c = pos->get_char();
    }

    return c;
}    

/*int main()
{
/*
    HuffTree *ht = new HuffTree;
    ht->insert('g',5);
    ht->insert('a',3);
    ht->insert('b',8);

    HuffTree *ht2 = new HuffTree;
    ht2->insert('h',7);

    HuffTree *ht3 = new HuffTree;
    ht3->insert('k',1);

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
    HuffTree *newTree2 = new HuffTree(*newTree,*ht3);

    newTree->alternate_output();
    newTree2->alternate_output();

    string s = newTree2->get_huff_string('j');
    cout << "j = " << s << "\n\n";
    cout << "i = " << newTree2->get_huff_string('i') << "\n";
    cout << "k = " << newTree2->get_huff_string('k') << "\n";

    cout << "11 = " << newTree2->get_huff_char("11") << "\n";
    cout << "10 = " << newTree2->get_huff_char("10") << "\n";
    cout << "0 = " << newTree2->get_huff_char("0") << "\n";

    cout << "\n\n\nNew Test__________________________\n\n";

    HuffTree *ht = new HuffTree;
    ht->insert('a',4);
    HuffTree *ht2 = new HuffTree;
    ht2->insert('b',3);
    HuffTree *ht3 = new HuffTree;
    ht3->insert('c',7);
    HuffTree *ht4 = new HuffTree;
    ht4->insert('d',3);
    HuffTree *ht5 = new HuffTree;
    ht5->insert('e',11);

    LinkedList<HuffTree> *ll = new LinkedList<HuffTree>;
    ll->push_back(*ht);
    ll->push_back(*ht2);
    ll->push_back(*ht3);
    ll->push_back(*ht4);
    ll->push_back(*ht5);

    for(LinkedList<HuffTree>::list_iterator li=ll->begin(); li!=ll->end(); li++) {
        //outputting trees
        li.val().alternate_output();
    }

    cout << "\nSorting list of trees...\n\n";

    ll->sort_list();
    
    for(LinkedList<HuffTree>::list_iterator li=ll->begin(); li!=ll->end(); li++) {
        li.val().alternate_output();
    }

    //Combining the trees in the list
    /*while(ll->size > 1) {
        cout << "Size: " << ll->size << "\n";
        HuffTree t1 = ll->pop_front();
        HuffTree t2 = ll->pop_front();

        HuffTree *newTree = new HuffTree(t1,t2);
        ll->push_front(*newTree);
    }

    LinkedList<HuffTree>::list_iterator li = ll->begin();
    HuffTree t1 = li.val();
    li++;
    HuffTree t2 = li.val(); 
    li++;
    HuffTree *newTree = new HuffTree(t1,t2);
    cout << "Before for loop:\nnewTree:\n";
    newTree->alternate_output();
    cout << "\n";
    for(li = li; li!=ll->end(); li++) {
        HuffTree *temp = new HuffTree(li.val());
        //HuffTree temp2 = *newTree;
        cout << "combining tree\n";
        temp->alternate_output();
        newTree = new HuffTree(*newTree,*temp);
        cout << "new newTree:\n";
        newTree->alternate_output();
    }    

    while(ll->size>0)
        ll->pop_front();

    cout << "\nSize of list: " << ll->size << "\n\n";

    newTree->alternate_output();

    cout << "\n\nCHARACTER MAPPINGS:\n\n";
    cout << "\ta = " << newTree->get_huff_string('a') << "\n";
    cout << "\tb = " << newTree->get_huff_string('b') << "\n";
    cout << "\tc = " << newTree->get_huff_string('c') << "\n";
    cout << "\td = " << newTree->get_huff_string('d') << "\n";
    cout << "\te = " << newTree->get_huff_string('e') << "\n";
     
    
    return 0;
}*/
