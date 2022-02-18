# VarroaPop application

The original application is the work of Bob Curry (stratpilot at gmail dot com).

VarroaPop is an MFC application to perform colony age structure simulation by selecting a certain amount of options including but not limited to Queen strength, Mite treatments and so on.

MFC application are hard to port, but we needed a way to run the simulation on non-Windows platform. 

We ended up with a solution that is aim to create a command line VarroaPop application by implemented stub interfaces of MFC classes in a portable maner.

To built this version of the VarroaPop simulation tool, follow the instructions in [VarroaPop command line tool](./Linux/README.md)

# Roadmap

- Bring additional features available in the VarroaPop command line tool to the GUI version
- Create a dependency on the VarroaPop library to separate GUI and command line applications from algorithmic code  