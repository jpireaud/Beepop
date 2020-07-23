Created by Julien Pireaud 

This file is to guide you through compile VarroaPop simulator on Linux / macOS

## Compilation

Run setup.py to prepare the Linux folder to be ready to build

For C++ dependency management we use Hunter package manager.

To compile in release:

1. create a directory <build>
1. move in <build> directory
1. execute `python ../setup.py` to generate appropriate CMakeLists.txt file for datamodel
1. prepare cmake folder `cmake -DCMAKE_BUILD_TYPE=Release ..`
1. call `cmake --build <build> --target VarroaPop -- -j <number of threads>`
1. call program `./<build>/VarroaPop -h`

To time an execution you can use:

- On Linux: `time ./<build>/VarroaPop -d VarroaPop/files/ -v exe/default.vrp -o output/vp_output_linux.txt -i input/vp_linux.txt -f`
- On Windows (PowerShell): `Measure-Command {start-process Release\VarroaPop.exe -argumentlist "exe\default.vrp /b /or output\vp_output_win.txt /i input\vp_input.txt" -wait}` 

## Run Simulations

The options that we keep for now are:
 - `-f` to force overwriting existing files
 - `-v simplified.vrp` minimal VRP file
 - `-i rcp85-input.txt` 
 - `--binaryWeatherFileFormat Rcp85` specifies the binary format of the weather file Observed|Modeled|Rcp85 
 - `-w data_46.03125_-118.34375` weather file 
 - `-o output.txt` output file 
 - `--forageDayNoTemp  --hourlyTemperaturesEstimation  --foragersAlwaysAgeBasedOnForageInc  --adultAgingBasedOnLaidEggs  --inOutEvents` options to properly run the simulations with the selected aging model

## Helper scrips 

- `run-simulations.py` will run simulations for omak, wenatchee, walla-walla with historical and future weather simulations. Make sure the path to executable in the script is correct.
- `scripts/plots.py` sample script which aim to automate plots generation, this is out of date but is a good source of inspiration
- `scripts/simulations.py` sample script to call VarroaPop simulations with different sets of options

## Weather format supported 

- ObservedHistorical starting 1/1/1979 
- ModeledHistorical starting 1/1/1950
- Rcp85 starting 1/1/2006