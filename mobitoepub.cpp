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


mobi::mobi(char *file_name) : rec_header(NULL), file_name(NULL), file(0)
{
    try{
    load_file(file_name);
    }
    catch(no_such_file_exception){
        cout << "No such file\n";
        return;
    }
    try{
        parse_header();
    }
    catch(invalid_file_exception){
        cout << "Invalid header\n";
        return;
    }
}

void mobi::parse_header()
{
    file->read((char *) &header, HEADERS_LEN);


    ofstream output_file("num_records", ios::binary);
    output_file.write((char*)&header.num_records,sizeof(header.num_records));
  if(strcmp("BOOKMOBI",header.type)!=0)
      throw invalid_file_exception();
    //cout . write (header.type,78);
    //

  cout << "name             " << header.name                           <<endl;
  cout << "flags            " << header.flags                          <<endl;
  cout << "version          " << bswap(header.version)                 <<endl;
  cout << "c_time           " << bswap(header.c_time)                  <<endl;
  cout << "m_time           " << bswap(header.m_time)                  <<endl;
  cout << "b_time           " << bswap(header.b_time)                  <<endl;
  cout << "mod_num          " << bswap(header.mod_num)                 <<endl;
  cout << "app_info         " << bswap(header.app_info)                <<endl;
  cout << "sort_info        " << bswap(header.sort_info)               <<endl;
  cout << "type             "; cout.write(header.type,4)               <<endl;

  cout << "creator          " << header.creator                        <<endl;
  cout << "u_id_seed        " << bswap(header.u_id_seed)               <<endl;
  cout << "next_record_list " << hex << bswap(header.next_record_list) <<endl;
  cout << "num_records      " << bswap(header.num_records)             <<endl;



}




void mobi::load_file(char *file_name)
{
    //try {
    file = new ifstream(file_name);
    if(!file->good())
        throw no_such_file_exception();
    //}
    //catch(no_such_file_exception){
        //cout << "No such file\n";
    //}

}
