#include "varroapopcmd.h"

int main(int argc, char** argv)
{
    VarroaPopCmd app;

    // Read input file
    app.ProcessInputFile("/mnt/dev/github/Beepop/Simulations/varroapy/varroapy/files/input/vp_linux_input.txt");

    // Read weather file
    // -> Done in ProcessInputFile

    // Set results filename
    app.SetResultsFileName("/mnt/c/dev/github/Beepop/Simulations/VarroaPy/VarroaPy/files/output/vp_linux_results.txt");

    // Run simulation
    app.Simulate();

    return 0;
}
