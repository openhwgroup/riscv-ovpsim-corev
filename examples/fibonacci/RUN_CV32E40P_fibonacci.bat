@echo off

;rem move into the Example Directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

..\..\bin\Windows64\riscvOVPsimCOREV.exe ^
    --program fibonacci.RISCV32.elf ^
    --variant CV32E40P ^
    --processorname CVE4P ^
    %*

if not defined calledscript ( pause )
