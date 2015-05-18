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
            char c;
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
        void encode();
        void decode();
        vector<CharFreq> frequencies;
        vector<string> huff_strings;
        LinkedList<HuffTree> *tree_list;

    private:
        ifstream infile;
        ofstream outfile;


};
