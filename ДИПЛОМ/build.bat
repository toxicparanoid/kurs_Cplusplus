@echo off
echo === Starting clean rebuild of Search Engine ===

if not exist CMakeLists.txt (
    echo Error: CMakeLists.txt not found. Run this script from project root.
    pause
    exit /b 1
)

if exist build (
    echo Removing old build folder...
    rmdir /s /q build
)

echo Creating new build folder...
mkdir build

cd build

echo Configuring CMake...
cmake .. -DCMAKE_BUILD_TYPE=Release

echo Building project...
cmake --build . --config Release -j4

cd ..

echo === Build completed successfully! ===
echo Executables are in: .\build\
echo.
echo Run indexer:   .\build\indexer.exe
echo Run searcher:  .\build\searcher.exe

pause