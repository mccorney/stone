// Include the common option parsing interfaces.
include "llvm/Option/OptParser.td"

/////////
// Flags

// The option should be accepted by cram 
def CompileOption : OptionFlag;

// The option should not be accepted by the build.
def NoCompileOption : OptionFlag;

// The option should not be accepted by the build.
def SystemOption : OptionFlag;

// The option should not be accepted by the build.
def NoSystemOption : OptionFlag;

// The option should not be accepted by the build.
def DebugOption : OptionFlag;

def ActionGroup : OptionGroup<"<action options>">, HelpText<"ACTIONS">;
class ActionOpt : Group<ActionGroup>;


def InternalGroup : OptionGroup<"<Stone internal options>">;
def InternalDebugGroup :
OptionGroup<"<Stone debug/development internal options>">,
Group<InternalGroup>, HelpText<"DEBUG/DEVELOPMENT OPTIONS">;

class InternalDebugOpt : Group<InternalDebugGroup>,
Flags<[HelpHidden]>;

//COMPILE ACTIONS

def Parse: Flag<["-"], "parse">,
HelpText<"Parse input file(s)">, ActionOpt,
Flags<[CompileOption]>;

def TypeCheck : Flag<["-"], "type-check">,
HelpText<"Parse and type-check input file(s)">, ActionOpt,
Flags<[CompileOption]>;

//	def EmitLibrary : Flag<["-"], "emit-library">,
//  HelpText<"Emit a linked library">, ActionOpt,
//  Flags<[NoInteractiveOption]>;

def EmitObj : Flag<["-"], "emit-obj">,
HelpText<"Emit object file(s) (-C)">, ActionOpt,
Flags<[CompileOption]>;

def C : Flag<["-"], "C">, Alias<EmitObj>,
Flags<[CompileOption]>, ActionOpt;

def EmitASM : Flag<["-"], "emit-asm">,
HelpText<"Emit assembly file(s) (-S)">, ActionOpt,
Flags<[CompileOption]>;

def S: Flag<["-"], "S">, Alias<EmitASM>,
Flags<[CompileOption]>, ActionOpt;

def EmitBC : Flag<["-"], "emit-bc">,
HelpText<"Emit LLVM BC file(s)">, ActionOpt,
Flags<[CompileOption]>;

def EmitIR : Flag<["-"], "emit-ir">,
HelpText<"Emit LLVM IR file(s)">, ActionOpt,
Flags<[CompileOption]>;

def DumpAST : Flag<["-"], "dump-ast">,
HelpText<"Parse and type-check input file(s) and dump AST(s)">, ActionOpt,
Flags<[CompileOption]>;

def Help : Flag<["-", "--"], "help">, 
Flags<[CompileOption, SystemOption]>,
HelpText<"Display available options">, ActionOpt;

def h : Flag<["-"], "h">, Alias<Help>;

def HelpSecrete : Flag<["-", "--"], "help-hidden">,
Flags<[CompileOption]>,
HelpText<"Display available options, including hidden options">;


def Version : Flag<["-", "--"], "version">,
Flags<[SystemOption]>,
HelpText<"Print version information and exit">, ActionOpt;

def v : Flag<["-"], "v">, 
Flags<[SystemOption]>,
HelpText<"Show commands to run and use verbose output">;

def Link : Flag<["-"], "sys-link">,
HelpText<"Specifies a library which should be linked against">, ActionOpt,
Flags<[SystemOption]>;

//GENERAL OPTIONS 
def Target : Separate<["-"], "sys-target">,
Flags<[CompileOption, SystemOption]>,
HelpText<"Generate code for the given target">;

def TargetVariant : Separate<["-"], "sys-target-variant">,
  Flags<[CompileOption, SystemOption]>,
  HelpText<"Generate 'zippered' code for macCatalyst that can run on the specified"
           " variant target triple in addition to the main -target triple">;

def TargetCPU : Separate<["-"], "target-cpu">, Flags<[CompileOption]>,
HelpText<"Generate code for a particular CPU variant">;

// DEV OPTIONS 

def ShowAction : Flag<["-"], "sys-show-action">,
Flags<[DebugOption]>,
HelpText<"Show every step in the lifecycle of the actions">;

def ShowTasks : Flag<["-"], "sys-show-tasks">,
Flags<[DebugOption]>,
HelpText<"Show every step in the lifecycle of the actions">;

def ShowTime : Flag<["-"], "sys-show-time">,
Flags<[DebugOption]>,
HelpText<"Show time in the lifecycle of actions and jobs">;

def ShowProcs : Flag<["-"], "sys-show-procs">,
Flags<[DebugOption]>,
HelpText<"Show time in the lifecycle of actions and jobs">;

def MainFile : Separate<["-"], "main-file">,
  HelpText<"Produce output for this file, not the whole module">;
