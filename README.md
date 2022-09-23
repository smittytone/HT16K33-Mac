# Mac-I2C-Driver 1.0.0

A macOS-specific driver for the [Excamera Labs I2C Mini board](https://i2cdriver.com/mini.html). It is based on the official code, but with the non-MacOS stuff removed and the code tidied a little.

It is the basis for the [Matrix Driver](#matrix-driver), which is intended to provide command line support for Holtek HT16K33-based 8x8 matrix displays.

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
| :-: | :-- |
| `-a` | `on`, `off` or none | Activate or deactivate the display. Once activated, the matrix will remain so for as long as it is powered. Pass `on` (or `1`) to activate, `off` (or `0`) to deactivate. Calling without an argument is a *de facto* activation |
| `-b` | {0-15} | Set the brightness to a value between 0 (low but not off) and 15 (high) |
| `-c` | {ascii_code} [true|false] | Plot the specified character, by code, on the display. If the second argument is included and is `true` (or `1`), the character will be centred on the display |
| `-p` | {x} {y} [1|0] | Plot a point as the coordinates `{x,y}`. If the third argument is `1` (or missing), the pixel will be set; if it is `0`, the pixel will be cleared |
| `-t` | {string} [delay] | Scroll the specified string. The second argument is an optional delay be between column shifts in milliseconds. Default: 250ms |

## Licences and Copyright

The I2C driver is © 2019, James ????. It is licensed under the terms of the BSD 3 Licence.

The Matrix driver is © 2022, Tony Smith (@smittytone). It is licensed under the terms of the MIT Licence.