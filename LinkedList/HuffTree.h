#include<iostream>

class TreeNode;

class HuffTree
{
    public:
        HuffTree();
        HuffTree(const HuffTree &other);
        HuffTree(HuffTree &ht1, HuffTree &ht2);
        ~HuffTree();
        void insert(char c, int frequency);
        int get_freq() const;
        void output_tree() const;
        void alternate_output();

        void operator=(const HuffTree &ht);
        bool operator>(const HuffTree &ht);
        bool operator>=(const HuffTree &ht);
        bool operator<(const HuffTree &ht);
        bool operator<=(const HuffTree &ht);

    private:
        void destroy_tree(TreeNode *node);
        void insert(char c, int frequency, TreeNode *node);
        void output_tree(TreeNode *node) const;
        void alternate_output(TreeNode *node, int level);
        void copy_tree(TreeNode *node, TreeNode *otherNode);

        TreeNode *root;
};
