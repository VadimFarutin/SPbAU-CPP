#ifndef _AUTOTEST_H_
#define _AUTOTEST_H_

#include <cstddef>

#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__);

class Test {
public:
  static void check(bool expr, const char *func, const char *filename, std::size_t lineNum);
  static void showFinalResult();
  virtual void runAllTests() = 0;

protected:
  static int failedNum;
  static int totalNum;
};

#endif