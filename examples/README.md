riscvOVPsimCOREV/examples/README.md
---
In this directory are several examples showing the use of the riscvOVPsimCOREV platform.

Application ELF Files
---
The examples include cross-compiled C applications as  _elf_  files and scripts to load onto the processor in the riscvOVPsimCOREV platform and execute.

The source of the applications are included and it is expected that you have your own cross-compiler toolchain installed to re-compile.

Debugging Applications
---
If you want to see an example of debugging an application using GDB, then look at the [dhrystone](dhrystone) example.

Notes
---
You must ensure that the binary executable you try and execute is appropriate for your host computer.  
For example, if you try and run the Linux64 executable on a Linux32 host you get an error such as:

> bin/Linux64/riscvOVPsimCOREV.exe: cannot execute binary file

