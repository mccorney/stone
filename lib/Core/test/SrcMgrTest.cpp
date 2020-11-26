#include "stone/Core/SrcMgr.h"
#include "stone/Core/FileSystem.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/Support/Process.h"
#include "gtest/gtest.h"


#include <cstddef>


using namespace stone; 


class FakeDiagClient : public DiagClient {

};


class SrcMgrTest : public ::testing::Test {
	protected:
	//FileMgr fileMgr;
	//SrcMgr srcMgr; 
	//FileSystemOptions fileSysOpts;
	//IntrusiveRefCntPtr<DiagIDs> diagIDs;
  //Diag diag;

protected:
	SrcMgrTest() {


	}

};

TEST_F(SrcMgrTest, GetColNumber) {

}
