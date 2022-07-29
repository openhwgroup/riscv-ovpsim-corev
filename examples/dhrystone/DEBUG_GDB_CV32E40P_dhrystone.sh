#!/bin/bash

cd $(dirname $0)

# To start GDB connected to the simulator we add -gdbconsole
RUN_CV32E40P_dhrystone.sh -gdbconsole "$@"
