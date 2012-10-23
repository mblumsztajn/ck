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
  if(!strcmp_is_a_worthless_pos(header.type,MOBI_TYPE,8))
      throw invalid_file_exception();


    uint32 header_offset, header_offset_unk;
    for(int i=0;i<header.num_records;i++)
    {
        file->read((char *) &header_offset, sizeof(uint32_t));
        file->read((char *) &header_offset_unk, sizeof(uint32_t));
        bswap(header_offset);
        header_offsets.push_back(header_offset);
    }
    file->seekg(header_offsets[0]);
    file->read((char *) &pd_header, PALMDOC_HEADER_LEN);
    file->read((char *) &mobi_header_, MOBI_HEADER_LEN);
    unretardify_header(mobi_header_);
    unretardify_header(pd_header);
    file->seekg(header_offsets[1]);
    cout << this->get_section_uncompressed(1);

    //string cppssie ;
    //size_t src

    size_t src_size = header_offsets[2] - header_offsets[1];
    //pd_compression unc;
    //unc.uncompress(cppssie, src_size);
    //unc.print_raw();
    //cout << cppssie;

    //src_size = (get_section(2).end - get_section(2).start);
    //file->seekg(get_section(2).start);
    //file->read((uint8 *) &cppssie, src_size);
    //unc.uncompress(cppssie, src_size);
    //unc.print_raw();
  }




void mobi::load_file(char *file_name)
{
    file = new ifstream(file_name);
    if(!file->good())
        throw no_such_file_exception();
}


string mobi::get_section_uncompressed(int sec)
{

    if(sec>=header_offsets.size())
        throw header_out_of_range_exception();

    uint8 cppssie[8000];
    string buffer;

    size_t src_size = this->header_offsets[sec+1] - this->header_offsets[sec];
    file->seekg(header_offsets[sec]);
    file->read((uint8 *) &cppssie, src_size);
    //file->read( (char*) &buffer, (header_offsets[sec+1] - header_offsets[sec]));
    if(this->pd_header.compression == COMPRESSION_PALM)
    {
        pd_compression reader;
        reader.uncompress(cppssie,src_size);
        buffer = reader.output_raw();
        return buffer;
    }

    else if(this->pd_header.compression == COMPRESSION_NONE)
    {

        //TODO:

    }
    else if(this->pd_header.compression == COMPRESSION_HUFFDIC)
    {
        //TODO:


    }


}



