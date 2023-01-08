# Ghidra Decompiled Code
---
- This code was decompiled using [Ghidra] from the `sampleGW` project, compiled for the TLSR8258 target with full [gcc] debugging and linked with the `libzb_coordinator.a` archive
- This code will probably not compile
- This code may not even be a fatihful reproduction of the original [Telink ZigBee SDK]; see below for details.
---
## Acknowledgements
- [Ryan Govostes] for producing the initial [Telink TC32 Processor Specification for Ghidra]
- [trust1995] for producing [Multiple disassembly improvements]

## Why On Earth would You Do That?
I was trying to write a program for the Telink TLSR8258 but could not figure out how to make the program work.  The documentation was insufficient and the program entered the opaque world of the supplied library.

I eventually decided that the only course of action was to decompile the library and walk through the code as far as was required to see why the code was not doing what I expected.  So I built the `sampleGW` program for the TLSR8258 with fully [gcc] debugging and then passed it to [Ghidra].  I then made some pretty minimal tweak to add missing type definitions and extracted the source code.

Next step was to split the source code back into the modules indicated by an `nm` symbol dump of the library and creating the `zigbee_library` directory structure.

---
The `_ghidra` directory is a special directory and contains the following:
- the `nm` symbol dump
- the `decompiled.c` output from [Ghidra] {1}
- decompiled source code as yet **NOT** assigned to a module file {2}
- a simple Python script to split the decompiled code into module files.
---
1. It would probably be possible to improve the [Ghidra] output by more manual tweaking of (mainly internal) function prototypes, improving `enum` definitions and identifying more `structure` types.
2. Unassigned functions could be _hidden_ internal library functions or they may be functions for which the SDK already provides source, for excample the `main()` function for `sampleGW`.  Unassigned functions will be assigned to modules as the author finds this neccessary and helpful.

## Proving The Code
> How do we prove that the decompiled and then manually reworked code matches the function of the original library?

This will be hard to achieve.  In the ideal case we want to:
- Look at the source code and define tests that hit every line of code
- Run the test against the modified [Ghidra] version and the original [Telink Zigbee SDK] version
- Mocking dependent functions could make this hard.

## Manual Improvements
The following improvements are just some that must be made:
- Replace [Ghidra] type guesses with the standard [Telink Zigbee SDK] equivalents
- As far as possible, identify internal structures, define them and update the code to use them.  These are typically identified via variables with names such as `something._0_4_` where this is a _4-byte_ field starting at _offset 0_ in the variable `something`

[Ghidra]: https://ghidra-sre.org/
[gcc]: https://gcc.gnu.org/
[Telink Zigbee SDK]: http://wiki.telink-semi.cn/tools_and_sdk/Zigbee/Zigbee_SDK.zip
[Ryan Govostes]: https://github.com/rgov
[Telink TC32 Processor Specification for Ghidra]: https://github.com/rgov/Ghidra_TELink_TC32
[trust1995]: https://github.com/trust1995
 [Multiple disassembly improvements]: https://github.com/rgov/Ghidra_TELink_TC32/pull/1