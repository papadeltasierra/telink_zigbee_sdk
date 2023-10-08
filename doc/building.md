# Custom Telink Builds
> First install the [Telink (Eclipse) IDE], which is an old instance of Eclipse plus Telink custom tooling based on the [gcc] compiler tools.

## Eclipse Projects and Source Code
> If you understand the [Telink (Eclipse) IDE], you can skip this.  The author started out knowing nothing and these are some notes.
- The starting point is the [Telink (Eclipse) IDE] having imported all the `tc32` projects found in the [Telink Zigbee SDK] project.
  - The SDK supports both `tc32` and `riscv` processors and the TLSR8258 (being used by the author) is a `tc32` processor.
  - It does not appear to be possible tp import **both** the `tc32` and `riscv` projects at the same time without altering the project names in the `.cproject` and `.project` files to remove the name clashes.
- 6 _apps_ are present in the SDK and these map to 6 directories below `.../tl_zigbee_sdk/apps`
- Eclipse uses _project files_ to define projects and there are `.cproject` and `.project` files
- Copying a _project_ within the Eclipse IDE appears to copy refernces to the original files, which means that you can end up editing a file for project `Y` and also affecting project `X` from which it was copied.

> So what is the corect way to copy code and project definitions?

- There are _properties_ associated with a project and these reference the include paths to the application (typically).  It is these _properties_ that mean copying a project results in duplicated references
- Properties flow down from the top-level, `tl_zigbee_sdk`, through `apps` to specific applications so, for example, the archive to be used is set at the `tl_zigbee_sdk` scope and is always `-lzb_coordinator`.


---
### Ghidra and Source Code
It appears that Eclipse _finds_ code below specified directories so having extracted some code using Ghidra and placed it in a sibling directory below the archives, Eclipse tried to build this code despite no explcit instructions to do so.

**So don't place code there!**

---
### sampleGW

- `-DCOORDINATOR=1`; sets `ZB_ROUTER_ROLE` and `ZB_COORDINATOR_ROLE`
- `ZB_COORDINATE_ROLE` etc changes code in various Zigbee libraries

### CloudSMETS
Trying to create a new application for CloudSMETS...
1. Copied source code from the `sampleGW` directory
1. Copied the application project `sampleGW` to new `CloudSMETS` application
1. Created new cnofiguration via _Project_ menu item `CloudSMETS`
1. Edited `CloudSMETS` project to change all references from `sampleGW` to `CloudSMETS`
1. Tried building, and it did not work
    1. seems to still be pulling in code from `sampleGW`, resulting in duplicate symbols
    1. Looks like you have to change the build configuration settings at global scope too!
1. **STILL** doesn't build and **STILL** pulling in stuff from `sampleGW`!

> Really need to understand how this works.  Need a primer on Eclipse!

# Elipse
The Eclipse set-up for the TLSR8258 is:
- A single project
- Multiple configurations, each of which resolves to a combination of:
  - An application e.g. "sampleGW"
  - A specific board e.g. TLSR8258.
- By default, all software (sourfce files) found below the various directories are built whenever a configuration is built
- Specific portions of the project can be excluded from the build by right-clicking to open _Properties_, selecting the _C/C++ Build_ settnigs and checking the _Exclude
resource from build_ box for the specific configuration (selected via the drop-down)
- To build, use _Build Configurations_, _Build Selected..._ from a right-click to build just the part of the project that you want
- From the _Project Explorer_, each directory is a _linked_ directory to the real source code
  - Copied the source for the the _sampleGW_ application into a new directory _CloudSMETS_
  - Created a new linked folder below `tl_zigbee_sdk/apps` for **CloudSMETS**
  - Created a new configuration, _CloudSMETS_, copying the existing _sampleGW_ configuration, and ensured that the _sampleGW_ code is not built for this configuration (otherwise lots of duplicate definitions)
- ZHCI components can be enabled/disabled via the `app_cfg.h` file but the source code does not correctly handle the lack of support for these components
  - Source code modified to handle this and _build out_ components not selected

# Burning
> The USBCOMFlashTx.html tool seems to cache the image to be written which means that you need to refresh the screen to force it to read new images.

Burning it otherwise straight-forward but remember to close the _USB-COM_ connection before you try to use the UART, for example via the _ZGC_ tool.


[Telink (Eclipse) IDE]: http://wiki.telink-semi.cn/wiki/IDE-and-Tools/IDE-for-TLSR8-Chips/
[gcc]: https://gcc.gnu.org/
[Telink Zigbee SDK]: http://wiki.telink-semi.cn/tools_and_sdk/Zigbee/Zigbee_SDK.zip