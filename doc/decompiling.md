# Decompiling
---
> **WARNING**: All decompiled code is coordinator/router and 8258 specific.
---
## Progress
- Decompiling the `libzb_coordinator.a` archive
- Build `sampleGW` for the TLSR8258 with...
  - Maximal `gcc` debug options
  - Linker `--whole-archive` to ensure that unused objects are still retained
- Working up from the bottom

## Before Decompilation
- Expand all manual enuerations so that Ghidra can use the correct values

### After decompilation
Do the following using a `Python` script if possible
- Replace _Ghidra_ types such as `byte` with _Telink_ types such as `u8`
- Determine correct location for source files in the tree
- Split decompiled files into source files defined by the symbol lists from the `libzb_coordinator.a` archive
  - Place functions into appropriate files
  - Place globals into appropriate files
  - Retain remnants in a non-C file

### After splitting
- Create a suitable build configuration
- Make all _not exported_ functions into `static`
- Find enums and fix the return/parameter types accordingly
- Look for all bitfields where source code exposes as `u8` and mask <br/>e.g. `return g_zbNwkCtx._45_1_ & 1;`
- Sort out the `FUN*` functions
- Identify structtures, e.g. fields `_0_4_` and fix-up
- Identify unions, memory overlaps, and fix-up
