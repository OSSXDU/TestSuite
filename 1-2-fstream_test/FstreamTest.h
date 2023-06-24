// By xchhe 2018.
#ifndef FSTREAMTEST_H
#define FSTREAMTEST_H
#include "Test.h"
#include "Suite.h"
#include "FstreamTest.h"
#include <vector>
#include <fstream>


class FstreamTest : public TestSuite::Test {
  enum {NTESTS = 6};
  static std::string s[NTESTS];
  std::vector <string> vec_str;
public:
  void test_fstream() {
    test_(vec_str[0] == "0");
    test_(vec_str[1] == "11");
    test_(vec_str[2] == "222");
    test_(vec_str[3] == "3.1415");
    test_(vec_str[4] == "PI");
    test_(vec_str[5] == "Aircraft");
  }

  void fstream_write();

  void fstream_read();

  void run() {
    fstream_write();

    fstream_read();

    test_fstream();
  }
};
#endif
