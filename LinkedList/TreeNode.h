class TreeNode
{
    public:
        TreeNode();
        ~TreeNode();
        TreeNode(const TreeNode &other);
        
        char get_char();
        void set_char(char c);

        int get_freq();
        void set_freq(int frequency);

        TreeNode *get_left();
        void set_left(TreeNode *tn);

        TreeNode *get_right();
        void set_right(TreeNode *tn);

    private:
        char ch;
        int freq;

        TreeNode *left;
        TreeNode *right;

};
