#ifndef STONE_CORE_DIAG_H
#define STONE_CORE_DIAG_H

namespace stone{

	enum class DiagLevel {
      // NOTE: 0 means "uncomputed".
      Ignored = 1, ///< Do not present this diagnostic, ignore it.
      Remark = 2,  ///< Present this diagnostic as a remark.
      Warning = 3, ///< Present this diagnostic as a warning.
      Error = 4,   ///< Present this diagnostic as an error.
      Fatal = 5    ///< Present this diagnostic as a fatal error.
    };

	struct DiagOptions {

	};

	class Fix final {
	};
	class Diag final {
	public:
		//Diag() = delete;
		Diag(const Diag&) = delete;
		Diag(Diag &&) = delete;
		Diag &operator=(const Diag&) = delete;
		Diag &operator=(Diag&&) = delete;
	public:
		void Write(); 
		void Warn();
		void Note();
		void Error();

	};
	class DiagClient {
		protected:
			unsigned int ID = 0;
		public:
			DiagClient();
		public:
			virtual unsigned int GetID()  = 0;
	};
}
#endif

