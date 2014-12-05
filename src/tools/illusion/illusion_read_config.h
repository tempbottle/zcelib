// illusion_doc.h :  CillusionDoc 类的接口
//


#pragma once




class Illusion_Read_Config
{
public:

    struct TABLE_CONFIG
    {
        ///表格名称
        CString table_name_;

        ///表格数据从第几行读取
        unsigned int read_data_start_ = 3;

        ///表格对应的protobuf的message名称
        CString  protobuf_message_;

        ///表格的第几行描述字段对应的protobuf
        unsigned int protobuf_cfg_line_ = 2;

        ///表格存放的数据库（SQLite）文件名称
        CString sqlite3_db_name_;

        ///表格对应的table id
        unsigned int table_id_ = 0;
        ///表格索引的字段1的列号
        unsigned int index1_column_ = 0;
        ///表格索引的字段2的列号
        unsigned int index2_column_ = 0;


        ///Protobuf item定义的数据
        std::vector<std::string>  proto_tag_;

    };

    ///枚举值的对应关系表
    typedef std::map <CString, CString >  MAP_CSTRING_TO_CSTRING;

    ///
    typedef std::map <CString, TABLE_CONFIG> MAP_TABLE_TO_CONFIG;

    ///
    struct EXCEL_FILE_DATA
    {
        MAP_CSTRING_TO_CSTRING  file_enum_;

        MAP_TABLE_TO_CONFIG  file_table_cfg_;
    };

    typedef std::map <CString, EXCEL_FILE_DATA> MAP_FNAME_TO_CFGDATA;


    enum CVT_CODING
    {
        CVT_UTF8,
        CVT_UTF16,
        CVT_MBCS,
    };


protected: // 仅从序列化创建
    Illusion_Read_Config();
protected:
    virtual ~Illusion_Read_Config();


public:

    ///
    static Illusion_Read_Config *instance();

    ///
    static void clean_instance();



public:
    //
    BOOL initialize();
    //
    void finalize();


    //处理EXCEL文件
    int read_excelconfig(const CString &open_file);

    //清理所有的读取数据
    void clear();

protected:

    //读枚举值
    int read_enum_data(EXCEL_FILE_DATA &file_cfg_data);

    //读取表格配置
    int read_table_config(EXCEL_FILE_DATA &file_cfg_data);

    //读取表格数据
    int read_table_data(TABLE_CONFIG &table_cfg);


    //
    int convert_to_utf8(CString &src, std::string &dst);
    //
    int convert_to_utf16(CString &src, std::string &dst);
    //
    int convert_to_mbcs(CString &src, std::string &dst);

protected:
    //
    static const size_t CONVERT_BUFFER_LEN = 64 * 1024;

protected:

    //单子实例
    static Illusion_Read_Config  *instance_;

protected:

    ///Excel的处理对象,EXCEL的处理类
    Illusion_ExcelFile illusion_excel_file_;

    ///文件对应的配置数据，用于我的查询
    MAP_FNAME_TO_CFGDATA   file_cfg_map_;

    ///
    CVT_CODING cur_cvt_coding_ = CVT_UTF8;

    ///
    wchar_t *cvt_utf16_buf_ = NULL;

    ///
    char *cvt_utf8_buf_ = NULL;

    ///
    char *cvt_mbcs_buf_ = NULL;

};


