@echo off
setlocal

set "ROOT=%~dp0"
if "%ROOT:~-1%"=="\" set "ROOT=%ROOT:~0,-1%"
set "BUILD_DIR=%ROOT%\build"
set "EXE=%BUILD_DIR%\craftworld.exe"
set "CXX="
set "CC="
set "ACTION=%~1"
if not defined ACTION set "ACTION=run"

pushd "%ROOT%" >nul

if /i "%ACTION%"=="clean" (
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
    popd >nul
    exit /b 0
)

if /i "%ACTION%"=="format" (
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
    where.exe clang-format >nul 2>nul
    if errorlevel 1 (
        echo Error: clang-format was not found in PATH.
        popd >nul
        exit /b 1
    )

    echo Formatting project with clang-format...
    for /r "%ROOT%\src" %%F in (*.c *.cc *.cpp *.cxx *.h *.hh *.hpp *.hxx) do clang-format -i -style=file "%%F"
)

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
    popd >nul
    exit /b 0
)

if not exist "%EXE%" (
    echo Error: expected executable was not created at "%EXE%".
    popd >nul
    exit /b 1
)

echo Running "%EXE%"...
"%EXE%"
set "RUN_EXIT=%ERRORLEVEL%"

popd >nul
exit /b %RUN_EXIT%
