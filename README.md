# Mac-I2C-Driver 1.0.0

A macOS-specific driver for the [Excamera Labs I2C Mini board](https://i2cdriver.com/mini.html). It is based on the [official code](https://github.com/jamesbowman/i2cdriver), but with the non-MacOS stuff removed and the code tidied a little.

It is the basis for the [Matrix Driver](#matrix-driver), which is intended to provide command line support for [Holtek HT16K33](https://www.holtek.com/productdetail/-/vg/HT16K33A)-based 8x8 matrix displays.

## Matrix Driver

```shell
matrix {device} [I2C address] [commands]
```

The `{device}` is the path to the I2C Mini’s device file, eg. `/dev/cu.usbserial-DO029IEZ`.

`[I2C address]` is an optional I2C address. By default, the HT16K33 uses the address `0x70`, but this can be changed.

`[commands]` are a sequence of command blocks as described below.

### Commands

These are the currently supported commands. Arguments in braces `{}` are required; those in square brackets `[]` are optional.

| Command | Arguments | Description |
| :-: | :-: | :-- |
| `-a` | [`on`\|`off`] | Activate or deactivate the display. Once activated, the matrix will remain so for as long as it is powered. Pass `on` (or `1`) to activate, `off` (or `0`) to deactivate. Calling without an argument is a *de facto* activation |
| `-b` | {0-15} | Set the brightness to a value between 0 (low but not off) and 15 (high) |
| `-c` | {ascii_code} [`true`\|`false`] | Plot the specified character, by code, on the display. If the second argument is included and is `true` (or `1`), the character will be centred on the display |
| `-p` | {x} {y} [1\|0] | Plot a point as the coordinates `{x,y}`. If the third argument is `1` (or missing), the pixel will be set; if it is `0`, the pixel will be cleared |
| `-t` | {string} [delay] | Scroll the specified string. The second argument is an optional delay be between column shifts in milliseconds. Default: 250ms |

Multiple commands can be issued by sequencing them at the command line. For example:

```shell
matrix /dev/cu.usbserial-DO029IEZ 0x71 -p 0 0 -p 1 1 -p 2 2 -p 3 3 -p 4 4 -p 5 5 -p 6 6 -p 7 7 
```

You should note that the display buffer is not persisted across calls to `matrix`, so building up an image across calls will not work. The display is implicitly cleared with each new call.

## Build the Driver

#### Command Line

1. Clone this repo and `cd` into the directory.
1. Run `cmake -S . -B build`
1. Run `cmake --build build`

The binary, `matrix` can be found in the `build/matrix/` directory.

#### Visual Studio Code

Alternatively, open the workspace file `i2c.code-workspace` in [Microsoft Visual Studio Code](https://visualstudio.microsoft.com), select a compiler (“kit”) and click **Build**. To use Visual Studio Code, you will first need to install the [`CMake`](https://marketplace.visualstudio.com/items?itemName=twxs.cmake) and [`CMake Tools`](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extensions.

## Licences and Copyright

The I2C driver is © 2019, James Bowman. It is licensed under the terms of the BSD 3-Clause Licence.

The Matrix driver is © 2022, Tony Smith (@smittytone). It is licensed under the terms of the MIT Licence.