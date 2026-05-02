@echo off
rem ============================================================================
rem File: build_and_run.bat
rem Brief: Windows helper script for formatting, configuring, building, and
rem        running Craftworld.
rem
rem Details:
rem   This script is the command-line entry point used by VS Code tasks and by
rem   developers working in a terminal. It chooses the project directory,
rem   verifies required tools, configures CMake with the Ninja generator and
rem   MinGW compilers, builds craftworld.exe, and optionally launches it.
rem
rem   For a beginner: double-clicking or running this script is like pressing a
rem   "prepare and start the game" button. The script runs the build tools in
rem   the correct order so you do not have to type every command manually.
rem
rem Copyright 2026 Craftworld contributors
rem
rem Licensed under the Apache License, Version 2.0 (the "License");
rem you may not use this file except in compliance with the License.
rem You may obtain a copy of the License at
rem
rem     http://www.apache.org/licenses/LICENSE-2.0
rem
rem Unless required by applicable law or agreed to in writing, software
rem distributed under the License is distributed on an "AS IS" BASIS,
rem WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
rem See the License for the specific language governing permissions and
rem limitations under the License.
rem
rem SPDX-License-Identifier: Apache-2.0
rem ============================================================================

setlocal

rem Resolve paths relative to this script so the command works from VS Code,
rem PowerShell, Command Prompt, or File Explorer.
set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"
set "BUILD_DIR=%ROOT%\build"
set "EXE=%BUILD_DIR%\craftworld.exe"
set "CXX="
set "CC="
set "ACTION=%~1"
if not defined ACTION set "ACTION=run"

rem Run all following commands from the project root. This makes generated files
rem predictable and avoids depending on the caller's current directory.
pushd "%ROOT%" >nul

if /i "%ACTION%"=="clean" (
    rem Delete generated build output. Source files are never removed here.
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
    popd >nul
    exit /b 0
)

if /i "%ACTION%"=="format" (
    rem Format only the project source tree, then stop.
    where.exe clang-format >nul 2>nul
    if errorlevel 1 (
        echo Error: clang-format was not found in PATH.
        popd >nul
        exit /b 1
    )

    echo Formatting project with clang-format...
    for /r "%ROOT%\src" %%F in (*.c *.cc *.cpp *.cxx *.h *.hh *.hpp *.hxx) do clang-format -i -style=file "%%F"
    popd >nul
    exit /b 0
)

if /i "%ACTION%"=="dev" (
    rem Dev mode is used by Ctrl+Shift+B in VS Code: format, configure, build,
    rem and run with one command.
    where.exe clang-format >nul 2>nul
    if errorlevel 1 (
        echo Error: clang-format was not found in PATH.
        popd >nul
        exit /b 1
    )

    echo Formatting project with clang-format...
    for /r "%ROOT%\src" %%F in (*.c *.cc *.cpp *.cxx *.h *.hh *.hpp *.hxx) do clang-format -i -style=file "%%F"
)

rem CMake creates the build configuration. Ninja performs the actual build.
where.exe cmake >nul 2>nul
if errorlevel 1 (
    echo Error: cmake was not found in PATH.
    popd >nul
    exit /b 1
)

where.exe ninja >nul 2>nul
if errorlevel 1 (
    echo Error: ninja was not found in PATH.
    popd >nul
    exit /b 1
)

rem Pick the first MinGW gcc/g++ pair found on PATH. Passing explicit compiler
rem paths prevents CMake or VS Code from asking the user to select a compiler.
for /f "delims=" %%G in ('where.exe gcc.exe 2^>nul') do if not defined CC set "CC=%%G"
for /f "delims=" %%G in ('where.exe g++.exe 2^>nul') do if not defined CXX set "CXX=%%G"

if not defined CC (
    echo Error: gcc was not found in PATH. Install MinGW-w64 or configure another CMake compiler.
    popd >nul
    exit /b 1
)

if not defined CXX (
    echo Error: g++ was not found in PATH. Install MinGW-w64 or configure another CMake compiler.
    popd >nul
    exit /b 1
)

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

rem Configure only when Ninja's generated files are missing. Normal source and
rem header changes are handled by the build step.
if not exist "%BUILD_DIR%\build.ninja" set "NEEDS_CONFIGURE=1"
if not exist "%BUILD_DIR%\CMakeFiles\rules.ninja" set "NEEDS_CONFIGURE=1"

if defined NEEDS_CONFIGURE (
    echo Configuring with CMake, Ninja, and MinGW...
    cmake -S "%ROOT%" -B "%BUILD_DIR%" -G Ninja "-DCMAKE_C_COMPILER=%CC%" "-DCMAKE_CXX_COMPILER=%CXX%"
    if errorlevel 1 (
        popd >nul
        exit /b 1
    )
)

if /i "%ACTION%"=="configure" (
    rem Configure-only mode is useful for editor setup and toolchain debugging.
    popd >nul
    exit /b 0
)

echo Building executable...
cmake --build "%BUILD_DIR%" --parallel
if errorlevel 1 (
    popd >nul
    exit /b 1
)

if /i "%ACTION%"=="build" (
    rem Build-only mode stops before launching the game executable.
    popd >nul
    exit /b 0
)

if not exist "%EXE%" (
    echo Error: expected executable was not created at "%EXE%".
    popd >nul
    exit /b 1
)

rem Propagate the game's exit code so VS Code and scripts can detect runtime
rem failures.
echo Running "%EXE%"...
"%EXE%"
set "RUN_EXIT=%ERRORLEVEL%"

popd >nul
exit /b %RUN_EXIT%
