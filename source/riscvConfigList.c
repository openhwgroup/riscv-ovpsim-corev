/*
 * Copyright (c) 2005-2022 Imperas Software Ltd., www.imperas.com
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

static const char *specificDocCV32E40S[] = {
    "RTL https://docs.openhwgroup.org/projects/cv32e40s-user-manual/en/latest/preface.html#release-0-2-0",
    0
};
static const char *specificDocCV32E40S_DEV[] = {
    "RTL https://docs.openhwgroup.org/projects/cv32e40s-user-manual/en/latest/preface.html#release-0-4-0",
    0
};
static const char *specificDocCV32E40X[] = {
    "RTL https://docs.openhwgroup.org/projects/cv32e40x-user-manual/en/latest/preface.html#release-0-2-0",
    0
};
static const char *specificDocCV32E40X_DEV[] = {
    "RTL https://docs.openhwgroup.org/projects/cv32e40x-user-manual/en/latest/preface.html#release-0-4-0",
    0
};

//
// TODO: additional documentation for the PULP extensions should be added to openhwDoc.c
// This legacy stuff is inadequate, but has been left here for the owners to update
//
static RV_DOC_FN(restrictCV32E20) {
    restrictionsCommon(riscv, node);
    vmidocAddText(node, "Updated to v0.2 specification (with clarification for mtvec access)");

}

static RV_DOC_FN(restrictCV32E40P) {
    restrictionsCommon(riscv, node);
}

static RV_DOC_FN(restrictCV32E41P) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "The Custom instructions are unimplemented "
    );
}

static RV_DOC_FN(restrictCV32E40S) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
        "Awaiting information for: "
        "PMA (bespoke model requiring specification), "
        "Zce, "
        "ePMP, "
        "Bus Error."
    );
}

static RV_DOC_FN(restrictCV32E40X) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "THIS IS A STARTING POINT AS THE SPECS DEVELOP "
        "More detail to be added once confirmed "
        "Awaiting information for: "
        "PMA (bespoke model requiring specification), "
        "ISA_P (exists in other models, to be added when ratified)."
        "Default Bit Manipulation setting = B_NONE"
    );
    vmidocAddText(node, "in order to get ZBA_ZBB_ZBS ");
    vmidocAddText(node, "  --override root/cpu/Zba=1 ");
    vmidocAddText(node, "  --override root/cpu/Zbb=1 ");
    vmidocAddText(node, "  --override root/cpu/Zbs=1 ");
    vmidocAddText(node, "in order to get ZBA_ZBB_ZBC_ZBS ");
    vmidocAddText(node, "  --override root/cpu/Zba=1 ");
    vmidocAddText(node, "  --override root/cpu/Zbb=1 ");
    vmidocAddText(node, "  --override root/cpu/Zbc=1 ");
    vmidocAddText(node, "  --override root/cpu/Zbs=1 ");
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
#define OPENHW_EXTENSION(_FEATURES, _RTLVERSION) \
    .extensionConfigs = (riscvExtConfigCP[]){                               \
        &(const riscvExtConfig){                                            \
            .id       = OPENHW_OVP_CONFIG_ID,                               \
            .userData = &(const openhwConfig){                              \
                .features   = (_FEATURES),                                  \
                .RTLversion = _RTLVERSION,                                  \
            }                                                               \
        },                                                                  \
        0                                                                   \
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
        .tinfo               = 0x00000002,  // tinfo default value
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
        OPENHW_EXTENSION(OHWF_NA, OHRV_MASTER),

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
        .name                = "CV32E40P",
        .arch                = RV32I|ISA_C|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_X|ISA_F),
        .user_version        = RVUV_2_3,    // User version 2.3, equivalent to 20191213
        .priv_version        = RVPV_1_11,   // Privileged version 1.11, equivalent to 2019060
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts
        .nmi_is_latched      = 1,           // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_JUMP,  // *RET in Debug mode behavior
        .defer_step_bug      = True,        // enable erratum step behavior

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

        .restrictionsCB      = restrictCV32E40P,
        OPENHW_EXTENSION(OHWF_NA, OHRV_MASTER),

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
        OPENHW_EXTENSION(OHWF_NA, OHRV_MASTER),

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

    //
    // TBD add (in Limitations to be added when spec available and stable)
    //   PMA (bespoke model require spec)
    //   Zce
    //   ePMP
    //   Bus Error
    //
    {
        .name                = "CV32E40S",
        .arch                = RV32I|ISA_B|ISA_C|ISA_M|ISA_U|ISA_X,
        .archMask            = 0x0,           // misa is read-only
        .archFixed           = ~(ISA_M),      // M controlled by parameter

        .user_version        = RVUV_20191213, // User version RVUV_20191213
        .priv_version        = RVPV_1_12,     // Privileged version 1.12
        .dbg_version         = RVDBG_1_0_0,   // Debug version 1.0.0

        .bitmanip_version    = RVBV_1_0_0,    // Bit Manipulation version 1.0.0

        .compress_version    = RVCV_0_70_5,
        .compress_present    = (RVCS_Zca|RVCS_Zcb|RVCS_Zcmb|RVCS_Zcmp|RVCS_Zcmt),

        .Smepmp_version      = RVSP_1_0,

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts
        .nmi_is_latched      = 1,           // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_priority      = RVDP_ORIG,
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_TRAP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000004,  // tinfo default value
        .mcontext_undefined  = False,       // mcontext is defined
        .scontext_undefined  = False,       // scontext is defined
        .tcontrol_undefined  = False,       // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // mcycle and minstret
        .instret_undefined   = False,       // instret CSR is undefined
        .cycle_undefined     = False,       // cycle CSR is undefined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = False,       // unimplemented PMP registers do not cause exceptions

        .counteren_mask      = 0,           // no counters are present
        .mcounteren_present  = True,        // mcounteren is present always read 0

        .ecode_mask          = 0x000007FF,  // Only valid WLRL bits

        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        // memory access constraints
        .amo_constraint      = RVMC_USER1,  // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,  // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,  // PUSH/POP memory access constraint

        .specificDocs        = specificDocCV32E40S,
        .restrictionsCB      = restrictCV32E40S,
        OPENHW_EXTENSION(OHWF_PMA16|OHWF_SEC|OHWF_BUS_FAULT|OHWF_PARITY_FAULT, OHRV_MASTER),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x15}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF81}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
        },
    },

    /*
     * Differences from 0.2.0 -> 0.4.0
     * https://draftable.com/compare/SZlHwXYpPqHE
     *
     * P.11: Zc requested v0.70.4, actual config is v0.70.5
     * P.44: cs.push etc config ... - TBD
     * P.56: mcontext, mscontext removed - OK
     * P.58: CSR JVT WARL behavior, 1024 byte aligned - OK
     *       bits 9:0 always 0x0
     * P.61: mtvt WARL check (CLIC Enabled) - CHECK
     *       SMCLIC=1, then SMCLICC_ID_WIDTH
     *       override mtvt_mask
     * P.62 mcounteren hardwired 0 - OK
     * P.63 smstateen should be present - TBD
     * P.64 menvcfg/menvcfgh should be 0x0 - OK
     *
     *
     */
    {
        .name                = "CV32E40S_DEV",
        .arch                = RV32I|ISA_B|ISA_C|ISA_M|ISA_U|ISA_X,
        .archMask            = 0x0,           // misa is read-only
        .archFixed           = ~(ISA_M),      // M controlled by parameter

        .user_version        = RVUV_20191213, // User version RVUV_20191213
        .priv_version        = RVPV_1_12,     // Privileged version 1.12
        .dbg_version         = RVDBG_1_0_0,   // Debug version 1.0.0

        .bitmanip_version    = RVBV_1_0_0,    // Bit Manipulation version 1.0.0

        .compress_version    = RVCV_0_70_5,
        .compress_present    = (RVCS_Zca|RVCS_Zcb|RVCS_Zcmb|RVCS_Zcmp|RVCS_Zcmt),

        .Smepmp_version      = RVSP_1_0,


        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts
        .nmi_is_latched      = 1,           // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_priority      = RVDP_ORIG,
        .debug_mode          = RVDM_VECTOR, // DM implemented as vector
        .debug_address       = 0x1A110800,  // debug vector address
        .dexc_address        = 0x1A111000,  // debug exception address
        .debug_eret_mode     = RVDRM_TRAP,  // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,           // number of implemented triggers
        .tinfo               = 0x00000060,  // tinfo default value
        .trigger_match       = 0x000d,      // legal trigger match values
        .mcontext_undefined  = True,        // mcontext is defined
        .scontext_undefined  = True,        // scontext is defined
        .mscontext_undefined = True,        // mscontext is mot defined
        .tcontrol_undefined  = False,       // tcontrol is undefined
        .mcontext_bits       = 0,           // implemented bits in mcontext
        .scontext_bits       = 0,           // implemented bits in scontext
        .no_hit              = True,        // tdata1.hit is unimplemented

        // cycle and instret
        .minstret_undefined  = False,       // instret CSR is defined
        .mcycle_undefined    = False,       // cycle CSR is defined
        .instret_undefined   = True,        // instret CSR is defined
        .cycle_undefined     = True,        // cycle CSR is defined

        .time_undefined      = True,        // time CSR is undefined
        .PMP_undefined       = False,       // unimplemented PMP registers do not cause exceptions

        .counteren_mask      = 0,           // no counters are present
        .mcounteren_present  = True,        // mcounteren is  present

        .ecode_mask          = 0x000007FF,  // Only valid WLRL bits

        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        // memory access constraints
        .amo_constraint      = RVMC_USER1,  // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,  // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,  // PUSH/POP memory access constraint

        .specificDocs        = specificDocCV32E40S_DEV,
        .restrictionsCB      = restrictCV32E40S,
        OPENHW_EXTENSION(OHWF_PMA16|OHWF_SEC|OHWF_BUS_FAULT|OHWF_PARITY_FAULT|OHWF_0_4_0, OHRV_DEV),

        .csr = {
            .mvendorid  = {u32 : {bits   : 0x0602}},
            .marchid    = {u32 : {bits   : 0x15}},
            .mimpid     = {u32 : {bits   : 0x0}},
            .mtvec      = {u32 : {fields : {MODE:1}}},
            .mstatus    = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec      = {u32 : {bits  : 0xFFFFFF81}},
            .jvt        = {u32 : {bits  : 0xFFFFFC00}},
            .envcfg     = {u64 : {bits  : 0x0000000000000000ULL}},
        },
    },

    /*
     * NOTE: THIS MATCHES RTL, BUT NO SPECIFICATION: DO NOT CHANGE
     */
    {
        .name                = "CV32E40X",
        .arch                = RV32I|ISA_B|ISA_C|ISA_M,
        .archMask            = 0x0,                     // misa is read-only
        .archFixed           = ~(ISA_A|ISA_M|ISA_X),    // A,M,X controlled by parameter
        .user_version        = RVUV_2_3,                // User version 2.3
        .priv_version        = RVPV_1_12,               // Privileged version 1.12
        .dbg_version         = RVDBG_1_0_0,             // Debug version 1.0.0

        .bitmanip_version    = RVBV_1_0_0,              // Bit Manipulation version 1.0.0

        .compress_version    = RVCV_0_70_1,
        //.compress_present    = (RVCS_Zca|RVCS_Zcb|RVCS_Zcmb|RVCS_Zcmp|RVCS_Zcmt),

        // local interrupts
        .local_int_num       = 16,                      // Number of local interrupts
        .nmi_is_latched      = 1,                       // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_priority      = RVDP_HALT_NOT_STEP,
        .debug_mode          = RVDM_VECTOR,             // DM implemented as vector
        .debug_address       = 0x1A110800,              // debug vector address
        .dexc_address        = 0x1A111000,              // debug exception address
        .debug_eret_mode     = RVDRM_TRAP,              // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,                       // number of implemented triggers
        .tinfo               = 0x00000004,              // tinfo default value
        .mcontext_undefined  = False,                   // mcontext is defined
        .scontext_undefined  = True,                    // scontext is undefined
        .mscontext_undefined = False,                   // mscontext is defined
        .tcontrol_undefined  = False,                   // tcontrol is defined
        .mcontext_bits       = 0,                       // implemented bits in mcontext
        .no_hit              = True,                    // tdata1.hit is unimplemented

        // mcycle and minstret
        .minstret_undefined  = False,                   // minstret CSR is defined
        .mcycle_undefined    = False,                   // mcycle CSR is defined

        .time_undefined      = True,                    // time CSR is undefined
        .PMP_undefined       = True,                    // PMP registers are undefined

        .counteren_mask      = -1,                      // all counters are present
        .mcounteren_present  = False,                   // mcounteren is not present

        .ecode_mask          = 0x000007FF,              // Only valid WLRL bits

        .tval_zero           = True,                    // [smu]tval are always zero
        .unaligned           = True,                    // unaligned accesses are allowed

        // memory access constraints
        .amo_constraint      = RVMC_USER1,              // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,              // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,              // PUSH/POP memory access constraint

        .specificDocs        = specificDocCV32E40X,
        .restrictionsCB      = restrictCV32E40X,
        OPENHW_EXTENSION(OHWF_PMA16|OHWF_BUS_FAULT|OHWF_TRIGGERNZ|OHWF_E40X_2, OHRV_MASTER),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x14}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF81}},
            .tdata1    = {u32 : {bits   : 0x00000004}},
            .jvt       = {u32 : {bits   : 0xFFFFFFC0}},
        },
    },

    /*
     * Differences from 0.2.0 -> 0.4.0
     * https://draftable.com/compare/fPbEGksbVUvT
     *
     * P.11: Zc[a,b,cmb,cmp] optional to always enabled - OK
     *
     * P.20: B_EXT now 3 groups // use override - OK
     *      NONE
     *      ZBA_ZBB
     *      ZBA_ZBB_ZBC_ZBS
     *
     *  P.35: lr.w, sc.w supported on A_EXT, ISA_A controlled by override - OK
     *
     *  P.38: main memory vs i/o - OK
     *
     *  P.52: mcontext, mscontext removed - OK
     *
     *  P.53: CSR JVT WARL behavior, 1024 byte aligned - OK
     *      bits 9:0 always 0x0
     *
     *  P.54: mstatus.mpie R -> RW - (documentation error not intended) - OK
     *
     *  P.56: mtvec.base[31:7] RW -> WARL - OK ?
     *  [6:2] always 0
     *  [1:0] WARL check added mtvecW
     *
     *  P.57: mtvt WARL check (CLIC Enabled) - CHECK
     *  SMCLIC=1, then SMCLICC_ID_WIDTH
     *  override mtvt_mask
     *
     *  P.60: SMCLIC=1 mcause reset 0x0000_0000 -> 0x3000_0000 - TBD
     *  P.60: SMCLIC=1 mcause minhv R -> RW - TBD
     *  P.60: SMCLIC=1 mcause MPIE  R -> RW - TBD
     *  P.60: mcause.exccode WLRL what is the specified behavior on illegal value ?
     *  https://github.com/openhwgroup/cv32e40x/issues/618
     *
     *
     *
     */
    {
        .name                = "CV32E40X_DEV",
        .arch                = RV32I|ISA_B|ISA_C|ISA_M,
        .archMask            = 0x0,                     // misa is read-only
        .archFixed           = ~(ISA_A|ISA_M|ISA_X),    // A,M,X controlled by parameter
        .user_version        = RVUV_2_3,                // User version 2.3
        .priv_version        = RVPV_1_12,               // Privileged version 1.12
        .dbg_version         = RVDBG_1_0_0,             // Debug version 1.0.0

        .bitmanip_version    = RVBV_1_0_0,              // Bit Manipulation version 1.0.0

        .compress_version    = RVCV_0_70_5,
        .compress_present    = (RVCS_Zca|RVCS_Zcb|RVCS_Zcmb|RVCS_Zcmp|RVCS_Zcmt),

        // local interrupts
        .local_int_num       = 16,                      // Number of local interrupts
        .nmi_is_latched      = 1,                       // NMI is latched when asserted

        // Add debug module (defaults)
        .debug_priority      = RVDP_HALT_NOT_STEP,
        .debug_mode          = RVDM_VECTOR,             // DM implemented as vector
        .debug_address       = 0x1A110800,              // debug vector address
        .dexc_address        = 0x1A111000,              // debug exception address
        .debug_eret_mode     = RVDRM_TRAP,              // *RET in Debug mode behavior

        // trigger module
        .trigger_num         = 1,                       // number of implemented triggers
        .tinfo               = 0x00000060,              // tinfo default value
        .trigger_match       = 0x000d,                  // legal trigger match values
        .mcontext_undefined  = True,                    // mcontext is undefined
        .scontext_undefined  = True,                    // scontext is undefined
        .mscontext_undefined = True,                    // mscontext is undefined
        .tcontrol_undefined  = False,                   // tcontrol is defined
        .mcontext_bits       = 0,                       // implemented bits in mcontext
        .no_hit              = True,                    // tdata1.hit is unimplemented

        // mcycle and minstret
        .minstret_undefined  = False,                   // minstret CSR is defined
        .mcycle_undefined    = False,                   // mcycle CSR is defined

        .time_undefined      = True,                    // time CSR is undefined
        .PMP_undefined       = True,                    // PMP registers are undefined

        .counteren_mask      = -1,                      // all counters are present
        .mcounteren_present  = False,                   // mcounteren is not present

        .ecode_mask          = 0x000007FF,              // Only valid WLRL bits

        .tval_zero           = True,                    // [smu]tval are always zero
        .unaligned           = True,                    // unaligned accesses are allowed

        // memory access constraints
        .amo_constraint      = RVMC_USER1,              // AMO memory access constraint
        .lr_sc_constraint    = RVMC_USER1,              // LR/SC memory access constraint
        .push_pop_constraint = RVMC_USER1,              // PUSH/POP memory access constraint

        .specificDocs        = specificDocCV32E40X_DEV,
        .restrictionsCB      = restrictCV32E40X,
        OPENHW_EXTENSION(OHWF_PMA16|OHWF_BUS_FAULT|OHWF_0_4_0, OHRV_DEV),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x14}},
            .mimpid    = {u32 : {bits   : 0x0}},
            .mtvec     = {u32 : {fields : {MODE:1}}},
            .mstatus   = {u32 : {fields : {MPP:3}}},
        },
        .csrMask = {
            .mtvec     = {u32 : {bits   : 0xFFFFFF81}},
            .jvt       = {u32 : {bits   : 0xFFFFFC00}},
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
        OPENHW_EXTENSION(OHWF_NA, OHRV_MASTER),

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
        OPENHW_EXTENSION(OHWF_NA, OHRV_MASTER),

    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

