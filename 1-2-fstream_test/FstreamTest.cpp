// By xchhe 2018.
#include "FstreamTest.h"

// Initialize static data
std::string FstreamTest::s[FstreamTest::NTESTS] = {"0",  \
        "11",  "222",  "3.1415",  "PI",  "Aircraft"};

void FstreamTest::fstream_write()
{
    std::ofstream output_file("fstream_test.txt");

    for(int i=0;i<NTESTS;i++)
    {
        output_file<<s[i]<<std::endl;
    }

    output_file.flush();
    output_file.close();
}


void FstreamTest::fstream_read()
{
    std::ifstream input_file("fstream_test.txt");
    std::string str;

    for(int i=0;i<NTESTS;i++)
    {
        std::getline(input_file, str);
        vec_str.push_back(str);
    }

    input_file.close();
}
