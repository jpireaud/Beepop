Created by Julien Pireaud (jpireaud at gmail dot com)

This file is to guide you through compile VarroaPop simulator on Linux / macOS

Run setup.py to prepare the Linux folder to be ready to build

For C++ dependency management we use Hunter package manager.

To compile in release:

1. create a directory <build>
2. call `cmake --build <build> --config Release --target VarroaPop -- -j <number of threads>`
3. call program `./<build>/VarroaPop -h`

To time an execution you can use:

- On Linux: `time ./<build>/VarroaPop -d VarroaPop/files/ -v exe/default.vrp -o output/vp_output_linux.txt -i input/vp_linux.txt -f`
- On Windows (PowerShell): `Measure-Command {start-process Release\VarroaPop.exe -argumentlist "exe\default.vrp /b /or output\vp_output_win.txt /i input\vp_input.txt" -wait}` 
