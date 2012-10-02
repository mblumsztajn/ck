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
    load_file(file_name);
    parse_header();
}

void mobi::parse_header()
{
    file->read((char *) &header, HEADERS_LEN);


    cout << "name               " << header.name                <<endl;
    cout << "flags              " << header.flags               <<endl;
    cout << "version            " << header.version             <<endl;
    cout << "c_time             " << header.c_time              <<endl;
    cout << "m_time             " << header.m_time              <<endl;
    cout << "b_time             " << header.b_time              <<endl;
    cout << "mod_num            " << header.mod_num             <<endl;
    cout << "app_info           " << header.app_info            <<endl;
    cout << "sort_info          " << header.sort_info           <<endl;
    cout << "type               " << header.type                <<endl;
    cout . write (header . type, 4)<< endl;;

    cout << "creator            " << header.creator             <<endl;
    cout << "u_id_seed          " << header.u_id_seed           <<endl;
    cout << "next_record_list   " << header.next_record_list    <<endl;
    cout << "num_records        " << header.num_records         <<endl;


}




void mobi::load_file(char *file_name)
{
    try {
    file = new ifstream(file_name);
    if(!file->good())
        throw no_such_file_exception();
    }
    catch(no_such_file_exception){
        cout << "No such file\n";
    }


}
