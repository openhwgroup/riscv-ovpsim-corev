/*
 * Copyright (c) 2005-2023 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// VMI header files
#include "vmi/vmiDoc.h"

// base model header files
#include "riscvConfig.h"

// extension header files
#include "openhwConfig.h"

//
// Emit common restrictions
//
static void restrictionsCommon(riscvP riscv, vmiDocNodeP node) {

}

//
// TODO: additional documentation for the PULP extensions should be added to openhwDoc.c
// This legacy stuff is inadequate, but has been left here for the owners to update
//
static RV_DOC_FN(restrictCV32E20) {
    restrictionsCommon(riscv, node);
    vmidocAddText(node, "Updated to v0.2 specification (with clarification for mtvec access)");

}

static RV_DOC_FN(restrictCV32E41P) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "The Custom instructions are unimplemented "
    );
}

static RV_DOC_FN(restrictCV32A6) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
    );
}

static RV_DOC_FN(restrictCV64A6) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
    );
}

//
// Mandatory extension configuration macro
//
#define OPENHW_EXTENSION(_FEATURES, _TDATA1_RESET, _DCSR_RESET, _CPUCTRL_RESET) \
    .extensionConfigs = (riscvExtConfigCP[]){      \
        &(const riscvExtConfig){                   \
            .id       = OPENHW_OVP_CONFIG_ID,      \
            .userData = &(const openhwConfig){     \
                .features      = (_FEATURES),      \
                .tdata1_reset  = (_TDATA1_RESET),  \
                .dcsr_reset    = (_DCSR_RESET),    \
                .cpuctrl_reset = (_CPUCTRL_RESET), \
            }                                      \
        },                                         \
        0                                          \
    }

//
// Defined configurations
//
static const riscvConfig configList[] = {
    {
        .name                = "CV32E20",
        .arch                = RV32I|ISA_C|ISA_M,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_C|ISA_E|ISA_M), // C,E,M bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts
        .nmi_is_latched      = 1,           // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A110808,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // mcycle and minstret
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = 0x1ffd,      // specific counters present
        .mcounteren_present  = True,        // mcounteren is present
        .noinhibit_mask      = 0x1ffd,

        .ecode_mask          = 0x8000001F,  // Only valid bits
        .ecode_nmi           = 0x8000001F,  // Only valid bits

        .tval_zero           = True,        // [smu]tval are always zero
        .tval_zero_ebreak    = True,        // [smu]tval zero on ebreak
        .tval_ii_code        = True,        // On illegal instruction

        .unaligned           = True,        // unaligned accesses are allowed

        .mtvec_is_ro         = False,       // mtvec can be written
        .tvec_align          = 256,         // mtvec alignment
        .mtvec_sext          = False,       // mtvec zero-extend

        .noZifencei          = False,       // Zifencei is implemented

        // memory access constraints
        .amo_constraint      = RVMC_USER1,  // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,  // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,  // PUSH/POP memory access constraint

        .restrictionsCB      = restrictCV32E20,
        OPENHW_EXTENSION(OHWF_NA|OHWF_STOPCOUNT_0, 0x28001040, 0x40000003, 0x0),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x14}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF00}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    {
        .name                = "CV32E41P",
        .arch                = RV32I|ISA_C|ISA_F|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_X),    // only X bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        .Zfinx_version       = RVZFINX_0_41,    // Zfinx version
        .Zcea_version        = RVZCEA_0_50_1,   // Zcea version
        .Zceb_version        = RVZCEB_0_50_1,   // Zceb version
        .Zcee_version        = RVZCEE_1_0_0_RC, // Zcee version

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts
        .nmi_is_latched      = 1,           // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = True,        // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // mcycle and minstret
        .instret_undefined   = False,       // instret CSR is defined
        .cycle_undefined     = False,       // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = True,        // PMP registers are undefined

        .counteren_mask      = -1,          // all counters are present
        .mcounteren_present  = False,       // mcounteren is not present

        .ecode_mask          = 0x0000001F,  // Only valid WLRL bits

        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        // memory access constraints
        .amo_constraint      = RVMC_USER1,  // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,  // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,  // PUSH/POP memory access constraint

        .restrictionsCB      = restrictCV32E41P,
        OPENHW_EXTENSION(OHWF_NA|OHWF_STOPCOUNT_0, 0x28001040, 0x40000003, 0x0),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x4}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF01}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    {
        .name                = "CV32A6",
        .arch                = RV32I|ISA_A|ISA_C|ISA_M|ISA_S|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_10,   // Privileged version 1.10
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2 (TODO: spec says 0.13)

        // memory access constraints
        .amo_constraint      = RVMC_USER1,  // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,  // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,  // PUSH/POP memory access constraint

        .restrictionsCB      = restrictCV32A6,
        OPENHW_EXTENSION(OHWF_NA|OHWF_STOPCOUNT_0, 0x0, 0x0, 0x0),

    },
    {
        .name                = "CV64A6",
        .arch                = RV64I|ISA_A|ISA_C|ISA_M|ISA_S|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_10,   // Privileged version 1.10
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2 (TODO: spec says 0.13)

        // memory access constraints
        .amo_constraint      = RVMC_USER1,  // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,  // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,  // PUSH/POP memory access constraint

        .restrictionsCB      = restrictCV64A6,
        OPENHW_EXTENSION(OHWF_NA|OHWF_STOPCOUNT_0, 0x0, 0x0, 0x0),

    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

