#include<iostream>
#include "TreeNode.h"
using namespace std;

TreeNode::TreeNode()
{
    ch = '\0';
    freq = 0;

    left = NULL;
    right = NULL;
}

TreeNode::TreeNode(const TreeNode &other)
{
    ch = other.ch;
    freq = other.freq;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode()
{
}

char TreeNode::get_char()
{
    return ch;
}

void TreeNode::set_char(char c)
{
    ch = c;
}

int TreeNode::get_freq()
{
    return freq;
}

void TreeNode::set_freq(int frequency)
{
    freq = frequency;
}

TreeNode *TreeNode::get_left()
{
    return left;
}

void TreeNode::set_left(TreeNode *tn)
{
    left = tn;
}

TreeNode *TreeNode::get_right()
{
    return right;
}

void TreeNode::set_right(TreeNode *tn)
{
    right = tn;
}

/*int main()
{
    TreeNode tn;

    cout << "tn initialized. char is " << tn.get_char() << " and freq is "
         << tn.get_freq() << "\n\n";

    tn.set_char('g');
    tn.set_freq(6);

    TreeNode tn2;
    tn2.set_char('a');
    tn2.set_freq(3);

    tn.set_left(&tn2);

    cout << "tn char: " << tn.get_char() << " freq: " << tn.get_freq() <<
         "\ntn2 char: " << tn.get_left()->get_char() << " freq: " << 
         tn.get_left()->get_freq() << "\n\n";

    return 0;

}*/
