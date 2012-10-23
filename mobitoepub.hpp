#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "mobiexceptions.hpp"
#include "mobiheaders.hpp"

#define DEBUG true
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
    string get_section_uncompressed(int sec);
    st_file_section get_section_offsets(int sec);
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




class hd_compression
{

};


class  pd_compression
{
    string destination;

    public:
    bool uncompress(uint8 *src, size_t srcLen, uint8 *dst, size_t dstLen);
    bool uncompress(uint8 *src, size_t srcLen);
    string output_raw();

};
string pd_compression::output_raw()
{
    return destination;
}
bool pd_compression::uncompress(uint8 *src, size_t srcLen)
{
    if(!this->destination.empty())
        this->destination.clear();

    uint8 *srcEnd = src + srcLen;
    while (src < srcEnd) 
    {

        unsigned c = *src++;

        if ((c >= 1) && (c <= 8)) 
        {
            //if (dstLeft < c)
                //return false;
            while (c > 0) 
            {
                this->destination += *src++;
                --c;
            }
        } 
        else if (c < 128) 
        {
            this->destination += c;
        } 
        else if (c >= 192) 
        {
            this->destination  += ' ';
            this->destination  += c ^ 0x80;
        } 
        else 
        {
            if (src < srcEnd) 
            {
                c = (c << 8) | *src++;
                size_t back = (c >> 3) & 0x07ff;
                size_t n = (c & 7) + 3;
                //char *dstBack = &this->destination - back;
                string::iterator dst_back;
                dst_back = this->destination.end() - back;
                while (n > 0) 
                {
                    this->destination += *dst_back++;
                    --n;
                }
            }
        }
    }
    return true;
}

bool pd_compression::uncompress(uint8 *src, size_t srcLen, uint8 *dst, size_t dstLen)
{
    uint8 *srcEnd = src + srcLen;
    uint8 *dstEnd = dst + dstLen;
    uint8 *dstOrig = dst;
    size_t dstLeft;
    while (src < srcEnd) {
        dstLeft = dstEnd - dst;
        if (0 == dstLeft)
            return false;

        unsigned c = *src++;

        if ((c >= 1) && (c <= 8)) {
            if (dstLeft < c)
                return false;
            while (c > 0) {
                *dst++ = *src++;
                --c;
            }
        } else if (c < 128) {
            *dst++ = c;
        } else if (c >= 192) {
            if (dstLeft < 2)
                return false;
            *dst++ = ' ';
            *dst++ = c ^ 0x80;
        } else {
            if (src < srcEnd) {
                c = (c << 8) | *src++;
                size_t back = (c >> 3) & 0x07ff;
                size_t n = (c & 7) + 3;
                uint8 *dstBack = dst - back;
                while (n > 0) {
                    *dst++ = *dstBack++;
                    --n;
                }
            }
        }
    }

    if (dst < dstEnd)
        *dst = 0;

    return true;
}
