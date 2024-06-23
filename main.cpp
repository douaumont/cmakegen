/*
    Copyright 2024 Artyom Makarov

    This file is part of cmakegen.

    cmakegen is free software: you can redistribute it and/or modify it under the terms of the 
    GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.

    cmakegen is distributed in the hope that it will be useful, 
    but WITHOUT ANY WARRANTY; 
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with cmakegen. 
    If not, see <https://www.gnu.org/licenses/>. 
*/


#include <filesystem>
#include <format>
#include <print>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <boost/program_options.hpp>
#include <boost/nowide/args.hpp>

namespace po = boost::program_options;

struct Options
{
    std::string cmakeVersion, projectName, projectType;
    int cxxStd;
    Options(const po::variables_map& options)
        :
        cmakeVersion(options.at("cmake-version").as<std::string>()),
        projectName(options.at("project-name").as<std::string>()),
        projectType(options.at("project-type").as<std::string>()),
        cxxStd(options.at("cxx-std").as<int>())
    {
    }
};

void GenerateCMakeLists(const Options& options)
{
    std::ofstream cmakeLists{std::filesystem::current_path() / "CMakeLists.txt"};

    auto printToFile = [&cmakeLists]
    <typename... Args>
    (std::format_string<Args...> fmt, Args&&... args)
    {
        std::println(cmakeLists, fmt, args...);
    };

    if (cmakeLists.is_open())
    {
        printToFile("cmake_minimum_required(VERSION {})", options.cmakeVersion);
        printToFile("project({} LANGUAGES CXX)", options.projectName);
        printToFile("");
        printToFile("add_{}(${{PROJECT_NAME}})", options.projectType);
        printToFile("");
        printToFile("target_compile_features(${{PROJECT_NAME}} PRIVATE cxx_std_{})", options.cxxStd);
    }
}

int main(int argc, char** argv)
{
    boost::nowide::args _(argc, argv);
    po::options_description optionsDesc("Allowed options");
    optionsDesc.add_options()
        ("help,h", "Show this message")
        ("cmake-version,v", po::value<std::string>()->default_value("3.0"), "Minimum CMake version")
        ("project-name,n", po::value<std::string>()->default_value("NewProject"), "Project name")
        ("project-type,t", po::value<std::string>()->default_value("executable"), "Project type: executable (default) or library")
        ("cxx-std", po::value<int>()->default_value(11), "Prefered C++ standard");
    
    po::variables_map parsedArgs;
    po::store(po::parse_command_line(argc, argv, optionsDesc), parsedArgs);

    if (parsedArgs.contains("help"))
    {
        optionsDesc.print(std::cout);
        return EXIT_SUCCESS;
    }
    else  
    {
        Options options{parsedArgs};
        GenerateCMakeLists(options);
    }

    return EXIT_SUCCESS;
}