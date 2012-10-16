#pragma once
#define PALMDOC_DB_HEADER_LEN 78
#define PALMDOC_HEADER_LEN 16
#define MOBI_HEADER_LEN 232


typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

inline void bswap(uint16 &x){x = __builtin_bswap32(x << 16);}
inline void bswap(uint32 &x){x = __builtin_bswap32(x);}
inline void bswap(uint64 &x){x = __builtin_bswap64(x);}

#pragma pack(push)
#pragma pack(1)

struct palmdoc_db_header
{
    char   name[32];
    uint16 flags;
    uint16 version;
    uint32 c_time;
    uint32 m_time;
    uint32 b_time;
    uint32 mod_num;
    uint32 app_info;
    uint32 sort_info;
    char   type[8];
    //char creator[4];
    uint32 u_id_seed;
    uint32 next_record_list;
    uint16 num_records;
};

struct palmdoc_header
{
    uint16 compression;
    uint16 garbage;
    uint32 text_length;
    uint16 record_count;
    uint16 record_size;
    uint32 current_pos;
};


struct mobi_header
{
  //palmdoc_header s_palmdoc_header;
  char   id[4];
  uint32 header_len;
  uint32 mobi_type;
  uint32 text_encoding;
  uint32 u_id;
  uint32 file_version;
  uint32 ortographic_index;            //0xFFFFFFFF
  uint32 inflection_index;             //0xFFFFFFFF
  uint32 index_names;
  uint32 index_keys;
  uint32 extra_index0;
  uint32 extra_index1;
  uint32 extra_index2;
  uint32 extra_index3;
  uint32 extra_index4;
  uint32 extra_index5;
  uint32 first_nonbook_index;
  uint32 full_name_offset;
  uint32 full_name_length;
  uint32 locale;
  uint32 input_language;
  uint32 output_language;
  uint32 min_version;
  uint32 first_image_index;
  uint32 huffman_record_offset;
  uint32 huffman_record_count;
  uint32 huffman_table_offset;
  uint32 huffman_table_length;
  uint32 exth_flags;                   //TODO: bitfield
  char   garbage[32];                  //0x000000000000000000000000.
  uint32 drm_offset;
  uint32 drm_count;
  uint32 drm_size;
  uint32 drm_flags;
  char   garbage2[12];
  uint16 first_content_record_number;
  uint16 last_content_record_number;
  uint32 unknown;                      //0x00000001
  uint32 fcis_record_number;
  uint32 fcis_record_count;            //0x00000001
  uint32 flis_record_number;
  uint32 flis_record_count;            //0x00000001
  uint64 unk0;                         //0x0000000000000000
  uint32 unk1;                         //0xFFFFFFFF
  uint32 unk2;                         //0x00000000
  uint32 unk3;                         //0xFFFFFFFF
  uint32 unk4;                         //0xFFFFFFFF
  uint32 extra_record_data_flags;      //tldr http://wiki.mobileread.com/wiki/MOBI#MOBI_Header
  uint32 indx_record_offset;           //(If not 0xFFFFFFFF)The record number of
                                       //the first INDX record created from an ncx file.
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
    char  *data;
    size_t len;
    char  *type;
};
#pragma pack(pop)
static_assert((sizeof(palmdoc_db_header)==PALMDOC_DB_HEADER_LEN),"palmdoc_db_header");
static_assert((sizeof(palmdoc_header)==PALMDOC_HEADER_LEN),"palmdoc_header");
static_assert((sizeof(mobi_header)==MOBI_HEADER_LEN),"mobi_header");


void unretardify_header(palmdoc_db_header &x)
{
    bswap(x.flags);
    bswap(x.version);
    bswap(x.c_time);
    bswap(x.m_time);
    bswap(x.b_time);
    bswap(x.mod_num);
    bswap(x.app_info);
    bswap(x.sort_info);
    bswap(x.u_id_seed);
    bswap(x.next_record_list);
    bswap(x.num_records);

}
void unretardify_header(palmdoc_header &x)
{
    bswap(x.compression);
    bswap(x.garbage);
    bswap(x.text_length);
    bswap(x.record_count);
    bswap(x.record_size);
    bswap(x.current_pos);

}
void unretardify_header(mobi_header &x)
{
    bswap(x.header_len);
    bswap(x.mobi_type);
    bswap(x.text_encoding);
    bswap(x.u_id);
    bswap(x.file_version);
    bswap(x.ortographic_index);
    bswap(x.inflection_index);
    bswap(x.index_names);
    bswap(x.index_keys);
    bswap(x.extra_index0);
    bswap(x.extra_index1);
    bswap(x.extra_index2);
    bswap(x.extra_index3);
    bswap(x.extra_index4);
    bswap(x.extra_index5);
    bswap(x.first_nonbook_index);
    bswap(x.full_name_offset);
    bswap(x.full_name_length);
    bswap(x.locale);
    bswap(x.input_language);
    bswap(x.output_language);
    bswap(x.min_version);
    bswap(x.first_image_index);
    bswap(x.huffman_record_offset);
    bswap(x.huffman_record_count);
    bswap(x.huffman_table_offset);
    bswap(x.huffman_table_length);
    bswap(x.exth_flags);
    bswap(x.drm_offset);
    bswap(x.drm_count);
    bswap(x.drm_size);
    bswap(x.drm_flags);
    bswap(x.first_content_record_number);
    bswap(x.last_content_record_number);
    bswap(x.unknown);
    bswap(x.fcis_record_number);
    bswap(x.fcis_record_count);
    bswap(x.flis_record_number);
    bswap(x.flis_record_count);
    bswap(x.unk0);
    bswap(x.unk1);
    bswap(x.unk2);
    bswap(x.unk3);
    bswap(x.unk4);
    bswap(x.extra_record_data_flags);
    bswap(x.indx_record_offset);
}


void print_header(const mobi_header &x)
{

    cout<< "id:                         "   << x.id << endl;
    cout<< "header_len:                 "   << x.header_len << endl;
    cout<< "mobi_type:                  "   << x.mobi_type << endl;
    cout<< "text_encoding:              "   << x.text_encoding << endl;
    cout<< "u_id:                       "   << x.u_id << endl;
    cout<< "file_version:               "   << x.file_version << endl;
    cout<< "ortographic_index:          "   << x.ortographic_index << endl;
    cout<< "inflection_index:           "   << x.inflection_index << endl;
    cout<< "index_names:                "   << x.index_names << endl;
    cout<< "index_keys:                 "   << x.index_keys << endl;
    cout<< "extra_index0:               "   << x.extra_index0 << endl;
    cout<< "extra_index1:               "   << x.extra_index1 << endl;
    cout<< "extra_index2:               "   << x.extra_index2 << endl;
    cout<< "extra_index3:               "   << x.extra_index3 << endl;
    cout<< "extra_index4:               "   << x.extra_index4 << endl;
    cout<< "extra_index5:               "   << x.extra_index5 << endl;
    cout<< "first_nonbook_index:        "   << x.first_nonbook_index << endl;
    cout<< "full_name_offset:           "   << x.full_name_offset << endl;
    cout<< "full_name_length:           "   << x.full_name_length << endl;
    cout<< "locale:                     "   << x.locale << endl;
    cout<< "input_language:             "   << x.input_language << endl;
    cout<< "output_language:            "   << x.output_language << endl;
    cout<< "min_version:                "   << x.min_version << endl;
    cout<< "first_image_index:          "   << x.first_image_index << endl;
    cout<< "huffman_record_offset:      "   << x.huffman_record_offset << endl;
    cout<< "huffman_record_count:       "   << x.huffman_record_count << endl;
    cout<< "huffman_table_offset:       "   << x.huffman_table_offset << endl;
    cout<< "huffman_table_length:       "   << x.huffman_table_length << endl;
    cout<< "exth_flags:                 "   << x.exth_flags << endl;
    cout<< "garbage:                    "   << x.garbage << endl;
    cout<< "drm_offset:                 "   << x.drm_offset << endl;
    cout<< "drm_count:                  "   << x.drm_count << endl;
    cout<< "drm_size:                   "   << x.drm_size << endl;
    cout<< "drm_flags:                  "   << x.drm_flags << endl;
    cout<< "garbage2:                   "   << x.garbage2 << endl;
    cout<< "first_content_record_number:"   << x.first_content_record_number << endl;
    cout<< "last_content_record_number: "   << x.last_content_record_number << endl;
    cout<< "unknown:                    "   << x.unknown << endl;
    cout<< "fcis_record_number:         "   << x.fcis_record_number << endl;
    cout<< "fcis_record_count:          "   << x.fcis_record_count << endl;
    cout<< "flis_record_number:         "   << x.flis_record_number << endl;
    cout<< "flis_record_count:          "   << x.flis_record_count << endl;
    cout<< "unk0:                       "   << x.unk0 << endl;
    cout<< "unk1:                       "   << x.unk1 << endl;
    cout<< "unk2:                       "   << x.unk2 << endl;
    cout<< "unk3:                       "   << x.unk3 << endl;
    cout<< "unk4:                       "   << x.unk4 << endl;
    cout<< "extra_record_data_flags:    "   << x.extra_record_data_flags << endl;
    cout<< "indx_record_offset:         "   << x.indx_record_offset << endl;
}
void print_header(const palmdoc_db_header &x)
{

    cout << "name[32]:                  " <<   x.name;
    cout << "flags:                     " <<   x.flags;
    cout << "version:                   " <<   x.version;
    cout << "c_time:                    " <<   x.c_time;
    cout << "m_time:                    " <<   x.m_time;
    cout << "b_time:                    " <<   x.b_time;
    cout << "mod_num:                   " <<   x.mod_num;
    cout << "app_info:                  " <<   x.app_info;
    cout << "sort_info:                 " <<   x.sort_info;
    cout << "type[8]:                   " <<   x.type;
    cout << "u_id_seed:                 " <<   x.u_id_seed;
    cout << "next_record_list:          " <<   x.next_record_list;
    cout << "num_records:               " <<   x.num_records;

}
void print_header(const palmdoc_header &x)
{
    cout << "palmdoc_header             " << "\n\n";

    cout << "compression:                "  << x.compression << endl;
    cout << "garbage:                    "  << x.garbage << endl;
    cout << "text_length:                "  << x.text_length << endl;
    cout << "record_count:               "  << x.record_count << endl;
    cout << "record_size:                "  << x.record_size << endl;
    cout << "current_pos:                "  << x.current_pos << endl;

}
