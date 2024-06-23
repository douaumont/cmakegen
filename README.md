# cmakegen

This is a utility command-line program to generate `CMakeLists.txt` scripts for C++ projects.

## Supported args

| Name | Description | Example |
| :-:  | ----------- | :------ |
|`cmake-version` | Minimum CMake version | `--cmake-version=3.19, -v 3.19` |
| `project-name` | Project name | `--project-name=Test, -n Test` |
| `project-type` | Project type: executable or library | `--project-type=library, -t executable` |
| `cxx-std` | C++ standard to be used by the project | `--cxx-std=23` |