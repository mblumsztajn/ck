// =====================================================================================
// 
//       Filename:  mobitoepub.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/01/2012 03:28:27 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  DaZ ()
//        Company:  
// 
// =====================================================================================
#include "mobitoepub.hpp"



int main(int argc, char **argv)
{
    if(op(argc, argv))
        mobi *book = new mobi(argv[1]);

    return 0;
}


mobi::mobi(char *file_name) : file_name(NULL), file(0)
{
    try{
    this->load_file(file_name);
    }
    catch(no_such_file_exception){
        cout << "No such file\n";
        return;
    }
    try{
        this->parse_header();
    }
    catch(invalid_file_exception){
        cout << this->header.type << endl;
        cout << "Invalid file type\n";
        return;
    }
}

void mobi::parse_header()
{
    file->read((char *) &header, PALMDOC_DB_HEADER_LEN);
    unretardify_header(header);

  if(!strcmp_is_a_worthless_pos(header.type,"BOOKMOBI",8))
      throw invalid_file_exception();


  //cout << header.num_records;
    uint32 header_offset, header_offset_unk;
    for(int i=0;i<header.num_records;i++)
    {
        file->read((char *) &header_offset, sizeof(uint32_t));
        file->read((char *) &header_offset_unk, sizeof(uint32_t));
        bswap(header_offset);
        header_offsets.push_back(header_offset);
    }
    file->seekg(get_section(0).start);
    file->read((char *) &pd_header, PALMDOC_HEADER_LEN);
    file->read((char *) &mobi_header_, MOBI_HEADER_LEN);
    unretardify_header(mobi_header_);
    unretardify_header(pd_header);
    print_header(mobi_header_);
    print_header(pd_header);
  }




void mobi::load_file(char *file_name)
{
    file = new ifstream(file_name);
    if(!file->good())
        throw no_such_file_exception();
}


st_file_section mobi::get_section(int sec)
{
    if(sec>=header_offsets.size())
        throw header_out_of_range_exception();
    st_file_section st;
    st.start = header_offsets[sec];
    st.end = header_offsets[sec+1];

    return (st);
}
