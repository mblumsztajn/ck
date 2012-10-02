// =====================================================================================
// 
//       Filename:  mobitoepub.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/01/2012 03:28:46 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  DaZ ()
//        Company:  
// 
// =====================================================================================
#define HEADERS_LEN 78
#include <fstream>
#include <iostream>
#include <cstring>
//#include <stdint.h>
//#include <cstdio>
//#include <string>
using namespace std;



typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

#pragma pack(push)
#pragma pack(1)

struct headers
{
    char name[32];
    uint16 flags;
    uint16 version;
    uint32 c_time;
    uint32 m_time;
    uint32 b_time;
    uint32 mod_num;
    uint32 app_info;
    uint32 sort_info;
    char type[4];
    char creator[4];
    uint32 u_id_seed;
    uint32 next_record_list;
    uint16 num_records;
};

struct rec_headers{
    uint32   offset;
    uint8    deleted   : 1;
    uint8    dirty     : 1;
    uint8    busy      : 1;
    uint8    secret    : 1;
    uint8    category  : 4;
    char     uniqueID[3];
};

struct image_data {
    char *      data;
    size_t      len;
    char *	type;
};
#pragma pack(pop)
static_assert((sizeof(headers)==HEADERS_LEN),"lolnie");


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


class mobi{
    headers header;
    rec_headers *rec_header;

    void parse_header();
    bool load_file();
public:
    void print_header();
    unsigned int get_locale();
    void load_file(char *file_name);
    mobi(char *file_name);

protected:
        char *file_name;
        ifstream *file;
};

class no_such_file_exception :public exception{
public:

};


inline uint16 bswap(const uint16 &x)
{
 uint16 x_ = __builtin_bswap32(x << 16);
 return x_;

}
inline uint32 bswap(const uint32 &x)
{
 uint32 x_ = __builtin_bswap32(x);
 return x_;

}
