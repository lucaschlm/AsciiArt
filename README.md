# PGM to ASCII Art Converter

A command-line application written in C++ that converts PGM images to ASCII art. 

## Features

- Output can be sent to the console or to a .txt file
- Includes support for multiple palettes with the ability to create your own
- Characters can be in UTF-8
- Run the executable with the --help parameter for a list of commands

## Usage

```
PgmToAsciiArt.exe --input [input_file] --output [output_file] --palette [palette_file] --width [width] --height [height]
```
- The `--input` flag is used to specify the PGM image file to convert. If this parameter is not specified, the file will be prompted for via the console.
- The `--output` flag is used to specify the name of the text file that will contain the ASCII art. If this parameter is not specified, the ASCII art will be output to the console.
- The `--palette` flag is used to specify a text file containing the ASCII color palette. Each line of the file should contain a UTF-8 character, from darkest to lightest. If this parameter is not specified, the default palette "W", "w", "l", "i", ":", ",", ".", " " will be used.
- The `--width` flag is used to specify the maximum width of the ASCII art. If this parameter is not specified, no limit will be set.
- The `--height` flag is used to specify the maximum height of the ASCII art. If this parameter is not specified, no limit will be set.
- The `--help` flag will display this help message.

**Remarks**:
Regardless of the values of the `--width` and `--height` options, the size of the ASCII art is bounded by the size of the input image. The size of the ASCII art always keeps the same ratio as the input image, the values of the options `--width` and `--height` are only maximums.
