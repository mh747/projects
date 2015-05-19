#include<iostream>
#include<fstream>
#include<string>
#include<bitset>
#include "HuffEncoder.h"
#include "HuffTree.cpp"
using namespace std;

HuffEncoder::HuffEncoder()
{
    tree_list = new LinkedList<HuffTree>;
    for(int i=0; i<=255; i++) {

        //Setting all char freq's to 0
        CharFreq cf;
        cf.c = (unsigned char)i;
        cf.freq = 0;
        frequencies.push_back(cf);

        //Setting all huff_strings to ''
        huff_strings.push_back("");
    }

    bit_buffer = "";
}

HuffEncoder::~HuffEncoder()
{
    if(infile.is_open())
        infile.close();
    if(outfile.is_open())
        outfile.close();
    delete tree_list;
}

void HuffEncoder::set_infile(string filename)
{
    infile.open(filename.c_str(),ios::in);

    if(!infile) {
        cout << "File '" << filename << "' could not be opened for reading.\n";
    }
}

void HuffEncoder::set_outfile(string filename)
{
    if(ifstream(filename.c_str())) {
        cout << "File already exists.\n";
    } else {
        outfile.open(filename.c_str(),ios::out|ios::binary);
    }

    if(!outfile) {
        cout << "File '" << filename << "' could not be opened for output.\n";
    }
}

bool HuffEncoder::decode(string iFilename, string oFilename)
{
    set_infile(iFilename);
    set_outfile(oFilename);
    bool success = 1;

    if(infile.is_open() && outfile.is_open()) {

        //cout << "Decompressing file '" << iFilename << "' to '"
             //<< oFilename << "'...\n\n";
        int freq;

        //Reading in file header to populate frequencies
        for(int i=0; i<=255; i++) {
            infile >> freq;
            frequencies[i].c = (unsigned char)i;
            frequencies[i].freq = freq;
        }
        infile.get();   //catching newline after header
        infile.get();

        //Sort frequencies vector
        sort(frequencies.begin(),frequencies.end());

        /*Creating single-node HuffTrees for each 
          char present in the file. Inserting HuffTrees
          into tree_list, keeping them sorted.*/
        for(int i=0; i<=255; i++) {
            if(frequencies[i].freq > 0) {
                HuffTree *newTree = new HuffTree;
                newTree->insert(frequencies[i].c,frequencies[i].freq);
                tree_list->push_back(*newTree);
            }
        }

        HuffTree *combined = combine_list_trees();

        if(combined != NULL) {
            /*Now that tree is created, read file bit by bit.*/
            char ch;
            unsigned char letter;

            while(infile) {
                infile.get(ch);
                letter = ch;
                unsigned long ul = (unsigned long)letter;
                bitset<8> bs(ul);
                bit_buffer = bit_buffer + bs.to_string();
            } 

            //cout << "string of bits:\n" << bit_buffer;

            int totalChars = combined->get_freq();
            //cout << "Total chars: " << totalChars << "\n";
            size_t startPos = 0;
            while(totalChars > 0) {
                char decodedChar = '\0';
                size_t slen = 0;
                while(decodedChar == '\0') {
                    slen++;
                    decodedChar = combined->get_huff_char(bit_buffer.substr(startPos,slen));
                }
                //cout << decodedChar;
                outfile << decodedChar;
                startPos+=slen;
                totalChars--;
            } 
        } else {
            success = 0;
        }

        infile.close();
        outfile.close();
    } else {
        success = 0;
        if(!infile.is_open())
            cout << "'" << iFilename << "' is not opened.'\n";
        if(!outfile.is_open())
            cout << "'" << oFilename << "' is not opened.'\n"; 
    }

    return success;
}
        
bool HuffEncoder::encode(string iFilename, string oFilename)
{
    set_infile(iFilename);
    set_outfile(oFilename);
    bool success = 1;
    
    if(infile.is_open() && outfile.is_open()){

        //cout << "Compressing file '" << iFilename << "' to '"
             //<< oFilename << "'...\n\n";
        char ch;
        unsigned char letter;

        //Reading in file, char by char
        //counting frequency of each char
        while(infile)
        {
            infile.get(ch);
            letter = ch;
            //cout << letter;
            frequencies[(int)letter].freq++;
        }

        //First, printing a header of frequencies at top of outfile
        for(int i=0; i<frequencies.size(); i++)
            outfile << frequencies[i].freq << " ";
        outfile << "\n";

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


        //We have an ordered list of trees, now combine them
        HuffTree *combined = combine_list_trees();


        //Continue only if combined tree is not empty
        if(combined != NULL) {
        
            /*Now that the tree is complete, find the Huffman
              string for each char in the file and store them
              in huff_strings vector.*/
            for(int i=0; i<=255; i++) {
                if(frequencies[i].freq > 0) {
                    huff_strings[(int)frequencies[i].c] = 
                                 combined->get_huff_string(frequencies[i].c);
                }
            }

            //Starting from beginning of file to do the translation.
            infile.clear();
            infile.seekg(0,ios::beg);
    
            while(infile)
            {
                infile.get(ch);
                letter = ch;
                string bits = huff_strings[(int)letter];
 
                for(int i=0; i<bits.size(); i++) {
                    output_bit(bits[i]);
                }
            }

        } else {
            cout <<  "Combined tree is NULL. Not continuing.\n";
            success = 0;
            exit(1);
        }

        infile.close();
        outfile.close();
    } else {
        success = 0;
        if(!infile.is_open())
            cout << "Input file could not be opened.\n";
        if(!outfile.is_open())
            cout << "Output file could not be opened.\n";
    }

    return success;
}

void HuffEncoder::output_bit(char bit)
{
    if(bit == '0' || bit == '1') {
        bit_buffer += bit;

        if(bit_buffer.size() == 8) {
            bitset<8> bs(bit_buffer);
            unsigned long ul = bs.to_ulong();
            unsigned char c = (unsigned char)ul;
            outfile.put(c);
            //cout << c;
            bit_buffer = "";
        }
    } else if(bit == '2') {  //signals eof
        while(bit_buffer.size() > 8)
            bit_buffer = bit_buffer + '0';
        bitset<8> bs(bit_buffer);
        unsigned long ul = bs.to_ulong();
        unsigned char c = (unsigned char)ul;
        outfile.put(c);
        bit_buffer = "";
    }
}

HuffTree *HuffEncoder::combine_list_trees()
{
    HuffTree *final = NULL;
    if(tree_list->size > 1) {
        while(tree_list->size > 1) {
            HuffTree *temp = new HuffTree(tree_list->pop_front());
            HuffTree *t1 = new HuffTree(tree_list->pop_front());
            HuffTree *combined = new HuffTree(*temp,*t1);
       //     combined->alternate_output();
            LinkedList<HuffTree>::list_iterator li = tree_list->begin();
            int i =0;
            while(li != tree_list->end() && li.val().get_freq()<combined->get_freq()) {
                i++;
                li++;         
            }
            //cout << "inserting tree before " << i << "th element.\n";
            tree_list->insert(*combined,li);
            final = combined; 
            //cout << "Remaining trees in list: " << tree_list->size << "\n";
            LinkedList<HuffTree>::list_iterator li2 = tree_list->begin();
            for(li2=tree_list->begin(); li2!=tree_list->end(); li2++) {
      //          li2.val().alternate_output();
            }
        }
    }
    return final;
}

/*int main()
{
    HuffEncoder he;
    bool encoded = he.encode("infile.txt","outfile");
    cout << "Encode() passed?: " << encoded << "\n\n";

    HuffEncoder he2;
    bool decoded = he2.decode("outfile","decoded");
    cout << "Decode() passed?: " << decoded << "\n\n";

}*/


