#include "varroapopcmd.h"

#include "stdafx.h"

#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

int main(int argc, char** argv)
{
    VarroaPopCmd app;

#ifdef WINDOWS
	const std::string rootFolder = "C:\\dev\\github\\Beepop\\Simulations\\VarroaPy\\VarroaPy\\files";
#else
	const std::string rootFolder = "/mnt/c/dev/github/Beepop/Simulations/VarroaPy/VarroaPy/files";
#endif

	const std::string inputFile = (bfs::path(rootFolder) / "input" / "vp_linux_input.txt").string();
	const std::string resultsFile = (bfs::path(rootFolder) / "output" / "vp_linux_results.txt").string();

	const bool inputFileOk = bfs::exists(inputFile); 

	if (inputFileOk)
	{
		// Read input file
		app.ProcessInputFile(inputFile);

		// Read weather file
		// -> Done in ProcessInputFile

		// Set results filename
		app.SetResultsFileName(resultsFile);

		// Run simulation
		app.Simulate();
	}

    return 0;
}
