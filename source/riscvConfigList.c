/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
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
#include "riscvVariant.h"

// extension header files
#include "openhwConfig.h"

//
// Emit common restrictions
//
static void restrictionsCommon(riscvP riscv, vmiDocNodeP node) {

}

//
// Emit N-variant restrictions
//
static RV_DOC_FN(restrictCV32E20) {
    restrictionsCommon(riscv, node);
}

static RV_DOC_FN(restrictCV32E40P) {
    restrictionsCommon(riscv, node);
    vmidocAddText(
        node,
        "Certain custom features of the CV32E40P are unimplemented. "
        "The following Registers are unimplemented: "
        "PCCRs, MIEX, MIPX, PCER, PCMR, HWLP "
        "PRIVLV. "
        "The Custom instructions are unimplemented "
    );
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
        "Zce, "
        "Bus Error, "
        "ISA_B (exists in other models, to be added when ratified), "
        "ISA_P (exists in other models, to be added when ratified)."
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
#define OPENHW_EXTENSION(_FEATURES) \
    .extensionConfigs = (riscvExtConfigCP[]){                               \
        &(const riscvExtConfig){                                            \
            .id       = OPENHW_OVP_CONFIG_ID,                               \
            .userData = &(const openhwConfig){                              \
                .features = (_FEATURES),                                    \
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

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E20,
        OPENHW_EXTENSION(OHWF_NA),

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
        .name                = "CV32E40P",
        .arch                = RV32I|ISA_C|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_X),    // only X bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

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

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40P,
        OPENHW_EXTENSION(OHWF_NA),

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

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E41P,
        OPENHW_EXTENSION(OHWF_NA),

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
        .name                = "CV32E40Pv2",
        .arch                = RV32I|ISA_C|ISA_F|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_X),    // only X bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

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

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40P,
        OPENHW_EXTENSION(OHWF_NA),

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
        .arch                = RV32I|ISA_C|ISA_M|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

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

        .ecode_mask          = 0x000000FF,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40S,
        OPENHW_EXTENSION(OHWF_PMA16),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x15}},
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
    //    typedef struct packed {
    //      logic [31:0] word_addr_low;
    //      logic [31:0] word_addr_high;
    //      logic        main;
    //      logic        bufferable;
    //      logic        cacheable;
    //      logic        atomic;
    //    } pma_region_t;
    //    main
    //
    //   Zce
    //   Adds exceptions 1 and 24
    //       1 - Instruction Access Fault (misaligned Address)
    //      24 - Instruction Bus Fault (custom)
    //   ISA_B (exists in other models) added when ratified
    //   ISA_P ..
    //
    {
        .name                = "CV32E40X",
        .arch                = RV32I|ISA_A|ISA_B|ISA_C|ISA_M|ISA_X,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(ISA_A|ISA_B|ISA_X), // A,B,P,X controlled by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_11,   // Privileged version 1.11
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2
        .bitmanip_version    = RVBV_1_0_0,  // Bit Manipulation version 1.0.0

        // local interrupts
        .local_int_num       = 16,          // Number of local interrupts

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

        .ecode_mask          = 0x000000FF,  // Only valid WLRL bits

        .tval_ii_code        = True,
        .tval_zero           = True,        // [smu]tval are always zero
        .unaligned           = True,        // unaligned accesses are allowed

        .restrictionsCB      = restrictCV32E40X,
        OPENHW_EXTENSION(OHWF_PMA16|OHWF_BUS_FAULT),

        .csr = {
            .mvendorid = {u32 : {bits   : 0x0602}},
            .marchid   = {u32 : {bits   : 0x14}},
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

        .restrictionsCB      = restrictCV32A6,
        OPENHW_EXTENSION(OHWF_NA),

    },
    {
        .name                = "CV64A6",
        .arch                = RV64I|ISA_A|ISA_C|ISA_M|ISA_S|ISA_U,
        .archMask            = 0x0,         // misa is read-only
        .archFixed           = ~(0),        // no bit can be changed by parameter
        .user_version        = RVUV_2_3,    // User version 2.3
        .priv_version        = RVPV_1_10,   // Privileged version 1.10
        .dbg_version         = RVDBG_0_13_2,// Debug version 0.13.2 (TODO: spec says 0.13)

        .restrictionsCB      = restrictCV64A6,
        OPENHW_EXTENSION(OHWF_NA),

    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

