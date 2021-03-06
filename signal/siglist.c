#include <signal.h>

const char* const _sys_siglist[__NSIG] = {
  "No signal",
  "Hangup",
  "Interrupt",
  "Quit",
  "Illegal Instruction",
  "Trace Trap",
  "Abort",
  "Privilege Violation",
  "Floating Point Exception",
  "Killed",
  "Bus Error",
  "Segmentation Fault",
  "Bad System Call",
  "Broken Pipe",
  "Alarm Clock",
  "Terminated",

  "Urgent Condition on I/O Channel",
  "Stopped (signal)",
  "Stopped",
  "Continued",
  "Child Process Exited",
  "Stopped (tty input)",
  "Stopped (tty output)",
  "I/O Possible",
  "CPU Limit Exceeded",
  "File Size Limit Exceeded",
  "Virtual Timer Alarm",
  "Profiling Signal",
  "Window System Signal",
  "User-defined Signal 1",
  "User-defined Signal 2",
  "Power failure restart",
};
weak_alias (_sys_siglist, sys_siglist)
