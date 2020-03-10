#include <boost/filesystem.hpp>
namespace bfs = boost::filesystem;

std::string FindSimulationDir()
{
    bfs::path current = bfs::path(__FILE__).parent_path();
    bfs::path previous;
    bfs::path simulations;
    do 
    {
        previous = current;
        simulations = current / "Simulations";
        current /= "..";
    }
    while (previous != current && (!bfs::exists(simulations) || !bfs::is_directory(simulations)));

    std:: string simulationsDir;
    if (bfs::exists(simulations) && bfs::is_directory(simulations))
    {
        simulationsDir = simulations.string();
    }
    return simulationsDir;
}

std::string GetSimulationsDir()
{
    static const std::string sSimulationDir = FindSimulationDir();
    return sSimulationDir;
}
