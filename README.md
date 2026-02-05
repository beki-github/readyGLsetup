
<h1 align="center">readyGLsetup</h1>

![image alt](https://github.com/beki-github/readyGLsetup/blob/d9ca29622e9976226ec7c4816c6eb2d172d603d9/Screenshot%202026-02-05%20185130.png)

NO MORE "IT WORKS ON MY MACHINE"
## Why I Built This
Setting up a C++ graphics environment is notoriously frustrating. Between linking static libraries, managing DLLs, and configuring CMake paths, many beginners quit before they even draw their first triangle.
I created this integrated development environment so that anyone can clone this repository and immediately start working in a lightweight VS Code setup. No manual configuration, no "missing .dll" errors just the code.

## Key Features
Pre-linked for GLFW and GLAD.

Automated Asset Pipeline: Shaders are automatically copied from the source to the build directory on every compile.

Cross-Platform Ready: Supports Windows (MSVC/MinGW) and Linux (GCC) via a unified CMake script.

Clean Deployment: it enables you to share your executable by sharing the executable file. 

## Quick Start
# 1. Prerequisites
windows: VS Code that's already configured for c++ and CMake Tools extensions.

Linux: vs code with CMake tools and build-essential cmake libglfw3-dev packages.

# 2. Launching 
Clone the Repo:

Bash

git clone https://github.com/beki-github/readyGLsetup
Open in VS Code: File > Open Folder... and select the project root.

Configure & Build:
Click "Select a Kit" in the bottom status bar and choose Visual Studio Community 2022 Release - amd64 (x64).
Press F7 to build or click the Build button.

Run:
Click the Play button in the status bar.
