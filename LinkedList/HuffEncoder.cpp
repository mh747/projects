#include<iostream>
#include<fstream>
#include<string>
#include "HuffEncoder.h"
#include "HuffTree.cpp"
using namespace std;

HuffEncoder::HuffEncoder()
{
    tree_list = new LinkedList<HuffTree>;
    for(int i=0; i<=255; i++) {

        //Setting all char freq's to 0
        CharFreq cf;
        cf.c = (char)i;
        cf.freq = 0;
        frequencies.push_back(cf);

        //Setting all huff_strings to ''
        huff_strings.push_back("");
    }
}

HuffEncoder::~HuffEncoder()
{
    if(infile.is_open())
        infile.close();
    if(outfile.is_open())
        outfile.close();
}

void HuffEncoder::set_infile(string filename)
{
    infile.open(filename.c_str(),ios::in);
}

void HuffEncoder::encode()
{
    if(infile.is_open()){
        char letter;

        //Reading in file, char by char
        //counting frequency of each char
        while(infile)
        {
            infile.get(letter);
            cout << letter;
            frequencies[(int)letter].freq++;
        }

        //Sort vector of (char,freq) structs
        sort(frequencies.begin(),frequencies.end());

        /*Creating single-node HuffTrees for each 
          char present in the file. Inserting 
          HuffTrees into tree_list, keeping them
          sorted.*/
        for(int i=0; i<=255; i++) {
            if(frequencies[i].freq > 0) {
                HuffTree *newTree = new HuffTree;
                newTree->insert(frequencies[i].c,frequencies[i].freq);
                tree_list->push_back(*newTree);
            }
        }

        //Test purposes. Outputting each singleton tree before combining begins
        for(LinkedList<HuffTree>::list_iterator li=tree_list->begin(); li!=tree_list->end(); li++)
            li.val().alternate_output();


        //We have an ordered list of trees, now combine them
	HuffTree *combined = new HuffTree(tree_list->pop_front()); 
        while(!tree_list->empty()) {
            HuffTree *temp = combined;
            HuffTree *t1 = new HuffTree(tree_list->pop_front());
            combined = new HuffTree(*temp,*t1);
            combined->alternate_output();
        }

        
        /*Now that the tree is complete, find the Huffman
          string for each char in the file and store them
          in huff_strings vector.*/
        for(int i=0; i<=255; i++) {
            if(frequencies[i].freq > 0) {
                huff_strings[(int)frequencies[i].c] = 
                             combined->get_huff_string(frequencies[i].c);
            }
        }

        //Test purposes. Outputting each huff_strings element
        for(int i=0; i<=255; i++) {
            cout << "Char: " << (char)i << "\tHuff String Exists?: ";
            if(huff_strings[i] == "")
                cout << "N\n";
            else 
                cout << "Y\tHuff String: " << huff_strings[i] << "\n";
        }

        //Starting from beginning of file to do the translation.
        infile.clear();
        infile.seekg(0,ios::beg);
        string bits = "";

        while(infile)
        {
            infile.get(letter);
            cout << "Letter: " << letter << "\nHuff: " << huff_strings[(int)letter] << "\n\n";
            bits = bits + huff_strings[(int)letter]; 
        }

        cout << "Final encoded return sequence:\n" << bits << "\n\nTest completed.";
        
    }
}

int main()
{
    HuffEncoder he;
    he.set_infile("infile.txt");
    he.encode();


/*    LinkedList<HuffTree>::list_iterator li = he.tree_list->begin();
    for(li=he.tree_list->begin(); li!=he.tree_list->end(); li++) {
        cout << "List item:\n";
        li.val().alternate_output();
    }
     
    for(li=he.tree_list->begin(); li!=he.tree_list->end(); li++) {
        cout << "List Item:\n";
        li.val().alternate_output();
    }*/
}


