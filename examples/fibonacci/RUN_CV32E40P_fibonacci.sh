#!/bin/bash

cd $(dirname $0)
bindir=$(dirname $(dirname $(pwd)))/bin/Linux64

${bindir}/riscvOVPsimCOREV.exe \
    --program fibonacci.RISCV32.elf \
    --variant CV32E40P \
    "$@"
