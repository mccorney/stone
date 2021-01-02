#include "stone/Core/SrcMgr.h"
#include "stone/Core/DiagnosticOptions.h"
#include "stone/Core/Diagnostics.h"
#include "stone/Core/FileMgr.h"
#include "stone/Core/FileSystemOptions.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Support/Process.h"
#include "gtest/gtest.h"

#include <cstddef>

using namespace stone;

class SrcMgrTest : public ::testing::Test {
protected:
  DiagnosticOptions diagOpts;
  FileSystemOptions fmOpts;
  FileMgr fm;
  DiagnosticEngine de;
  SrcMgr sm;

protected:
  SrcMgrTest() : de(diagOpts, nullptr, false), fm(fmOpts), sm(de, fm) {}
};

TEST_F(SrcMgrTest, GetColNumber) {

  const char *Source = "int x;\n"
                       "int y;";

  auto memBuffer = llvm::MemoryBuffer::getMemBuffer(Source);

  auto MainFileID = sm.CreateFileID(std::move(memBuffer));
  sm.SetMainFileID(MainFileID);

  bool Invalid;

  Invalid = false;
  EXPECT_EQ(1U, sm.GetColNumber(MainFileID, 0, &Invalid));
  EXPECT_TRUE(!Invalid);

  Invalid = false;
  EXPECT_EQ(5U, sm.GetColNumber(MainFileID, 4, &Invalid));
  EXPECT_TRUE(!Invalid);

  Invalid = false;
  EXPECT_EQ(1U, sm.GetColNumber(MainFileID, 7, &Invalid));
  EXPECT_TRUE(!Invalid);

  Invalid = false;
  EXPECT_EQ(5U, sm.GetColNumber(MainFileID, 11, &Invalid));
  EXPECT_TRUE(!Invalid);

  Invalid = false;
  EXPECT_EQ(7U, sm.GetColNumber(MainFileID, strlen(Source), &Invalid));
  EXPECT_TRUE(!Invalid);

  Invalid = false;
  sm.GetColNumber(MainFileID, strlen(Source) + 1, &Invalid);
  EXPECT_TRUE(Invalid);

  // Test invalid files
  Invalid = false;
  sm.GetColNumber(FileID(), 0, &Invalid);
  EXPECT_TRUE(Invalid);

  Invalid = false;
  sm.GetColNumber(FileID(), 1, &Invalid);
  EXPECT_TRUE(Invalid);

  // Test with no invalid flag.
  EXPECT_EQ(1U, sm.GetColNumber(MainFileID, 0, nullptr));
}
