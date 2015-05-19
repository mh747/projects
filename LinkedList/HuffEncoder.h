#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class HuffTree;

template<class T>
class LinkedList;

class HuffEncoder
{
    public:
        struct CharFreq
        {
            unsigned char c;
            int freq;

            bool operator<(const CharFreq &cf) const
            {
                return freq < cf.freq;
            }
            bool operator<=(const CharFreq &cf) const
            {
                return freq <= cf.freq;
            }
            bool operator>(const CharFreq &cf) const
            {
                return freq > cf.freq;
            }
            bool operator>=(const CharFreq &cf) const
            {
                return freq>= cf.freq;
            }
            bool operator==(const CharFreq &cf) const
            {
                return freq == cf.freq;
            }
        };

        HuffEncoder();
        ~HuffEncoder();
        void set_infile(string filename);
        void set_outfile(string filename);
        bool encode(string iFilename, string oFilename);
        bool decode(string iFilename, string oFilename);
        void decode();
        vector<CharFreq> frequencies;
        vector<string> huff_strings;
        LinkedList<HuffTree> *tree_list;

    private:
        void output_bit(char bit);
        HuffTree *combine_list_trees();
        string bit_buffer;
        ifstream infile;
        ofstream outfile;


};
