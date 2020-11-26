#include "stone/Core/SrcMgr.h"
#include "stone/Core/SrcID.h"
#include "stone/Core/Diag.h"
#include "stone/Core/FileSystemOptions.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Support/Process.h"
#include "gtest/gtest.h"


#include <cstddef>


using namespace stone; 
namespace {
class FakeDiagClient : public DiagClient {

};

class SrcMgrTest : public ::testing::Test {
	protected:
	FileMgr fileMgr;
	SrcMgr srcMgr; 
	FileSystemOptions fileSysOpts;
	IntrusiveRefCntPtr<DiagIDs> diagIDs;
  Diag dg;

protected:
	SrcMgrTest():
			
			fileMgr(fileSysOpts),
      diagIDs(new DiagIDs()),
      dg(diagIDs, new DiagOptions, new FakeDiagClient()),
			srcMgr(dg, fileMgr){
 
    //TargetOpts->Triple = "x86_64-apple-darwin11.1.0";
    //Target = TargetInfo::CreateTargetInfo(Diags, TargetOpts);
  }

};

TEST_F(SrcMgrTest, GetColNumber) {

	const char *source =
    "int x;\n"
    "int y;";


	auto memBuffer = llvm::MemoryBuffer::getMemBuffer(source);
  SrcID mainSrcID = srcMgr.createSrcID(std::move(memBuffer));
  srcMgr.setMainSrcID(mainSrcID);

  bool invalid = false; 

	//GetColNumber()
  EXPECT_EQ(1U, srcMgr.getColumnNumber(mainSrcID, 0, &invalid));
  EXPECT_TRUE(!invalid);
}

}
