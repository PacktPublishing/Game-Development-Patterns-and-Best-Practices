::******************************************************************************
::Filename: PostBuild.bat
::author:   Matt Casanova 
::e-mail:   mcasanov@digipen.edu
::Course:   cs180
::date:     2012/3/21
::
::Brief:
::This helper batch file will move .h and lib files from the Engine directory
::To the demo directory.
::******************************************************************************
@echo off

::Change to source directory
cd Source\Core

::Run doxygen and copy files
echo Running Doxygen
doxygen > nul 2> DoxyErrors.txt

::Step into doxygen directory and get index.chm
cd html
copy index.chm "..\Mach5Dox.chm" > nul 2> nul
::Step out
cd..

::Delete doxygen folder
rmdir /S /Q html > nul 2> nul


