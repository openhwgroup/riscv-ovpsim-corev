# riscvOVPsimCOREV
## A Complete, Fully Functional, Configurable RISC-V Simulator

Author    : Imperas Software, Ltd., using OVP Open Standard APIs

Date      : 17 Nov 2021

Version   : 20211117.0


License   : Model source included under Apache 2.0 open source license

License   : Imperas simulator for partner based on riscvOVPsimPlus and licensed under specific Imperas partner agreement

## Imperas Simulators
Imperas is the leading developer of RISC-V simulators for compliance testing, test development, hardware design verification, and operating system and application software development.

There are three simulators in the Imperas RISC-V range:

- the free riscvOVPsim from GitHub.com/riscv-ovpsim used for compliance testing and bare metal software runs
- the free riscvOVPsimPlus from OVPworld.org/riscv-ovpsim-plus (requiring registration) targeting test development and initial hardware verification
- the commercial M*SIM from Imperas Software, Inc., for professional developers, hardware design verification teams, operating system and advanced software developers.

There are also Imperas partner specific variations of riscvOVPsimPlus product available from Imperas partners.

All simulators are based on the Imperas CpuManager simulator base technology utilizing the OVP open standard APIs, and are targeted at different uses and have different capabilities.

## RISC-V Specifications currently supported in this riscvOVPsimCOREV product
- RISC-V - Instruction Set Manual, Volume I: User-Level ISA (user_version)
    - Version 2.2 : User Architecture Version 2.2
    - Version 2.3 : Deprecated and equivalent to 20191213
    - Version 20190305 : Deprecated and equivalent to 20191213
    - Version 20191213 : User Architecture Version 20191213

- RISC-V - Instruction Set Manual, Volume II: Privileged Architecture (priv_version)
    - Version 1.10 : Privileged Architecture Version 1.10
    - Version 1.11 : Deprecated and equivalent to 20190608
    - Version 20190405 : Deprecated and equivalent to 20190608
    - Version 20190608 : Privileged Architecture Version Ratified-IMFDQC-and-Priv-v1.11
    - Version master : Privileged Architecture Master Branch (1.12 draft)

- RISC-V I Base ISA
- RISC-V E Embedded ISA
- RISC-V M Multiply/Divide
- RISC-V A Atomic Instructions
- RISC-V F Single precision floating point
- RISC-V C Compressed instructions
- RISC-V S Supervisor mode
- RISC-V U User mode

## Additional specifications available in Imperas simulators currently not supported in this product
- RISC-V D Double precision floating point
- RISC-V N User-level interrupts
- RISC-V V Vector Extension  (vector_version)
    - Version 0.7.1-draft-20190605 : Vector Architecture Version 0.7.1-draft-20190605
    - Version 0.7.1-draft-20190605+ : Vector Architecture Version 0.7.1-draft-20190605 with custom features (not for general use)
    - Version 0.8-draft-20190906 : Vector Architecture Version 0.8-draft-20190906
    - Version 0.8-draft-20191004 : Vector Architecture Version 0.8-draft-20191004
    - Version 0.8-draft-20191117 : Vector Architecture Version 0.8-draft-20191117
    - Version 0.8-draft-20191118 : Vector Architecture Version 0.8-draft-20191118
    - Version 0.8 : Vector Architecture Version 0.8
    - Version 0.9 : Vector Architecture Version 0.9
    - Version 1.0-draft-20210130 : Vector Architecture Version 1.0-draft-20210130
    - Version 1.0-rc1-20210608 : Vector Architecture Version 1.0-rc1-20210608
    - Version master : Vector Architecture Master Branch as of commit 3570f99 (this is subject to change)

- RISC-V B Bit Manipulation Extension  (bitmanip_version)
    - Version 0.90 : Bit Manipulation Architecture Version v0.90-20190610
    - Version 0.91 : Bit Manipulation Architecture Version v0.91-20190829
    - Version 0.92 : Bit Manipulation Architecture Version v0.92-20191108
    - Version 0.93-draft : Bit Manipulation Architecture Version 0.93-draft-20200129
    - Version 0.93 : Bit Manipulation Architecture Version v0.93-20210110
    - Version 0.94 : Bit Manipulation Architecture Version v0.94-20210120
    - Version 1.0.0 : Bit Manipulation Architecture Version 1.0.0
    - Version master : Bit Manipulation Master Branch as of commit 1f56afe (this is subject to change)

- RISC-V H Hypervisor Extension  (hypervisor_version)
    - Version 0.6.1 : Hypervisor Architecture Version 0.6.1

- RISC-V K Cryptographic Extension  (crypto_version)
    - Version 0.7.2 : Cryptographic Architecture Version 0.7.2
    - Version 0.8.1 : Cryptographic Architecture Version 0.8.1
    - Version 0.9.0 : Cryptographic Architecture Version 0.9.0
    - Version 0.9.2 : Cryptographic Architecture Version 0.9.2
    - Version 1.0.0-rc1 : Cryptographic Architecture Version 1.0.0-rc1
    - Version 1.0.0-rc5 : Cryptographic Architecture Version 1.0.0-rc5

- RISC-V P DSP/SIMD Extension  (dsp_version)
    - Version 0.5.2 : DSP Architecture Version 0.5.2
    - Version 0.9.6 : DSP Architecture Version 0.9.6

- RISC-V Debug Module (debug_version)
    - Version 0.13.2
    - Version 0.14.0


## About riscvOVPsimCOREV
This riscvOVPsimCOREV simulator is a variation of riscvOVPsimPlus with specific Imperas partner configuration.

The Imperas RISC-V simulators implement the full and complete functionality of the RISC-V Foundation's public User and Privilege specifications.

The simulator is command line configurable to enable/disable all current optional and processor specific options. 

The simulator is developed, licensed and maintained by [Imperas Software](https://www.imperas.com/riscv) and it is fully compliant to the OVP open standard APIs. 

As a member of the RISC-V Foundation community of software and hardware innovators collaboratively driving RISC-V adoption, Imperas has developed the family of riscvOVPsim simulators to assist RISC-V adopters to become compliant to the RISC-V specifications.

The riscvOVPsim simulators include an industrial quality model and simulator of RISC-V processors for use for compliance testing purposes.

The model is provided as open source under the Apache 2.0 license. 

The simulator is provided under the Imperas partner agreement you signed to obtain access to this simulator.

Imperas actively maintains, enhances, and supports riscvOVPsimCOREV and its use. 

To ensure you make use of the current version of riscvOVPsimCOREV this release will expire. Please download the latest version.

Runtime configurable settings for all enabled RISC-V specification options makes it very easy to use.

Full commercial features are provided including variant selection, RISC-V specification model configuration options, semihosting, and RISC-V compliance group signature dump facility for compliance testing.

More information: [riscvOVPsimCOREV user guide](doc/riscvOVPsimCOREV_User_Guide.pdf) 

Model Source: [source](./source/README.md)

Examples: [examples](./examples/README.md)

![](riscvOVPsimCOREV.jpg)

riscvOVPsimCOREV is a fixed function simulation of one configurable processor model in a fixed platform. Full extendable platform simulations of reference designs booting FreeRTOS, Linux, SMP Linux etc. are available as open source and are available from [www.IMPERAS.com](https://www.imperas.com), [www.OVPworld.org](https://www.OVPworld.org).

## Debugging using GDB / Eclipse
The same fixed platform can be used to debug the application using GDB and Eclipse.

## Using riscvOVPsimCOREV
To use the simulator, just download the files, go into one of the example directories, and execute the provided run scripts.

For example on Linux:

         $ cd examples
         $ cd fibonacci
         $ ./RUN_RV32_fibonacci.sh

         riscvOVPsimCOREV (64-bit) v20210324.0 Open Virtual Platform simulator from www.IMPERAS.com.
         Copyright (c) 2005-2021 Imperas Software Ltd.  Contains Imperas Proprietary Information.
         Licensed Software, All Rights Reserved.
         Visit www.IMPERAS.com for multicore debug, verification and analysis solutions.

         riscvOVPsimCOREV started: Fri Mar 12 12:12:06 2021

         Info (OR_OF) Target 'riscvOVPsim/cpu' has object file read from 'fibonacci.RISCV32-O0-g.elf'
         Info (OR_PH) Program Headers:
         Info (OR_PH) Type           Offset     VirtAddr   PhysAddr   FileSiz    MemSiz     Flags Align
         Info (OR_PD) LOAD           0x00000000 0x00010000 0x00010000 0x00016998 0x00016998 R-E   1000
         Info (OR_PD) LOAD           0x00017000 0x00027000 0x00027000 0x000009c0 0x00000a54 RW-   1000
         starting fib(38)...
         fib(0) = 0
         fib(1) = 1
         fib(2) = 1
         fib(3) = 2
         ...
         fib(36) = 14930352
         fib(37) = 24157817
         finishing...
         Info
         Info ---------------------------------------------------
         Info CPU 'riscvOVPsim/cpu' STATISTICS
         Info   Type                  : riscv (RVB32I+MC)
         Info   Nominal MIPS          : 100
         Info   Final program counter : 0x100ac
         Info   Simulated instructions: 4,400,537,204
         Info   Simulated MIPS        : 1439.2
         Info ---------------------------------------------------
         Info
         Info ---------------------------------------------------
         Info SIMULATION TIME STATISTICS
         Info   Simulated time        : 44.01 seconds
         Info   User time             : 3.06 seconds
         Info   System time           : 0.00 seconds
         Info   Elapsed time          : 3.10 seconds
         Info   Real time ratio       : 14.18x faster
         Info ---------------------------------------------------

         riscvOVPsimCOREV finished: Fri Mar 12 12:12:10 2021

         riscvOVPsimCOREV (64-bit) v20210324.0 Open Virtual Platform simulator from www.IMPERAS.com.
         Visit www.IMPERAS.com for multicore debug, verification and analysis solutions.

## Measuring Instruction Functional Coverage with the coverage engine
Instruction Functional Coverage as it relates to processor verification is a technology solution to measure what is being stimulated in the ISA in terms of which instructions, operands and values are driven into a processor.


The Imperas coverage technology is developed using the Imperas VAP intercept technology and is provided as part of riscvOVPsimCOREV.


Example coverage command:


        $ ./RUN_E31_fibonacci.sh --cover basic --extensions I --reportfile impCov.log

The Imperas Instruction Functional Coverage works by monitoring every instruction as it retires and recording information about it.


At the end of simulation this data is summarized in the console and simulation log file.


        COVERAGE :: I :: threshold : 1 : instructions: seen 13/40 :  32.50%, coverage points hit: 262/2952 :   8.88%

Full details are provided in the report file.


You can get coverage reports for one run or merge results from many runs. You can select which instruction extension to report on, or even select just individual instructions to report on.


There is currently 'basic' and 'extended' coverage measuring.


Please read the [riscvOVPsimCOREV user guide](doc/riscvOVPsimCOREV_User_Guide.pdf) for full operational instructions.


If a signature comparison based verification methodology is adopted (as in the RISC-V Compliance suites) for comparison between device under test and reference, then functional coverage is only part of the story, as it is essential to measure the successful propagation of the results of the input instructions/values into the signature.

Read more about this in the section on Mutation Testing in the [riscvOVPsimCOREV user guide](doc/riscvOVPsimCOREV_User_Guide.pdf).


The coverage technology provided as part of riscvOVPsimCOREV has fixed functionality. The Imperas coverage technology is available as an extension library as source as a standard part of the Imperas commercial product offerings and this allows users to extend and modify functionality and coverage capability. Contact Imperas for more information.

## Extending riscvOVPsim and building your own models and platforms
riscvOVPsimCOREV is a fixed function simulator of one configurable processor model in a fixed platform.

Full extendable platform simulations of reference designs booting FreeRTOS, Linux, SMP Linux etc. are available as open source and are available from [www.IMPERAS.com](https://www.imperas.com), and [www.OVPworld.org](https://www.OVPworld.org).

## About Open Virtual Platforms (OVP) and Imperas Software
**Open Virtual Platforms** was created in 2008 to provide an open standard set of APIs and methodology to develop virtual platforms and simulation technology. 

[www.OVPworld.org](https://www.OVPworld.org/riscv).

**Imperas Software Ltd.** is the leading independent commercial developer of virtual platforms and high-performance software simulation solutions for embedded processor and systems. Leading semiconductor and embedded software companies use Imperas simulators for their processor based simulation solutions.

[www.imperas.com](https://www.imperas.com/riscv).

![OVP Image ](https://www.imperas.com/sites/default/files/partner-logos/ovp_0.jpg)  

![Imperas Imperas](https://www.imperas.com/sites/default/files/imperas-web-logo_2.png)  

This is the riscvOVPsimCOREV/README.md

