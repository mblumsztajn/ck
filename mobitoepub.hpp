#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include "mobiexceptions.hpp"
#include "mobiheaders.hpp"

#define DEBUG true
#define PALMDOC_DB_HEADER_LEN 78
#define PALMDOC_HEADER_LEN 16
#define MOBI_HEADER_LEN 232
using namespace std;


struct st_file_section
{
    uint32 start;
    uint32 end;
};

bool  op(int &argc, char **argv)
{
    char msg[] = "usage: \n\
        mobitoepub file.mobi [file.epub]\n";

    if(argc<2||argc>3)
    {
        cout << msg;
        return 0;
    }

    if(strcmp(argv[1],"-h")==0)
    {
        cout << msg;
        return 0;
    }
    return 1;
}


//
class mobi{
    palmdoc_db_header header;
    palmdoc_header    pd_header;
    mobi_header       mobi_header_;
    vector<uint32>    header_offsets;


    void parse_header();
    bool load_file();
    st_file_section get_section(int sec);
public:
    unsigned int get_locale();
    void load_file(char *file_name);
    mobi(char *file_name);

protected:
        char *file_name;
        ifstream *file;
};



bool strcmp_is_a_worthless_pos(char x[], char y[], int len)
{
    for(int i=0;i<len;i++)
    {
        if(x[i] != y[i])
        return false;
    }
    return true;


}
