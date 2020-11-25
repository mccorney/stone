#ifndef STONE_CORE_DIAG_H
#define STONE_CORE_DIAG_H

#include "stone/Core/LLVM.h"

#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "llvm/ADT/StringRef.h"
#include <vector>
namespace stone{

	class DiagClient; 


	enum class DiagLevel {
      // NOTE: 0 means "uncomputed".
      Ignored = 1, ///< Do not present this diagnostic, ignore it.
      Remark = 2,  ///< Present this diagnostic as a remark.
      Warning = 3, ///< Present this diagnostic as a warning.
      Error = 4,   ///< Present this diagnostic as an error.
      Fatal = 5    ///< Present this diagnostic as a fatal error.
    };

	class DiagOptions : public RefCountedBase<DiagOptions> {
	};
	
	class DiagIDs : public RefCountedBase<DiagIDs>{
	};
	class Fix final {
	};
	class Diag : public RefCountedBase<Diag> {
	public:
 
		explicit Diag(IntrusiveRefCntPtr<DiagIDs> diagIDs,
                             IntrusiveRefCntPtr<DiagOptions> diagOpts,
                             DiagClient *diagClient = nullptr,
                             bool shouldOwnClient = true);

  Diag(const Diag &) = delete;
  Diag &operator=(const Diag &) = delete;
  //~DiagnosticsEngine();

	public:
		void Write(); 
		void Warn();
		void Note();
		void Error();
		bool IsInFlight();


	};
	class DiagClient {
		protected:
			unsigned int ID = 0;
		public:
			DiagClient();
		public:
			virtual unsigned int GetID()  = 0;
		public:
	};
}
#endif

