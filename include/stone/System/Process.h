namespace stone {

class Process;
class ProcessQueue;

enum class ProcessKind { Compile, Link };
class Process final {
  Action *Trigger;
  System *S;

public:
  llvm::SmallVector<Process *> Deps;
};

class ProcessQueue {};

} // namespace stone
