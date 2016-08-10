@echo off
if not exist "%~dp0Project" mkdir %~dp0Project
cd %~dp0Project
cmake -G "Visual Studio 14 2015 Win64" ..
cd %~dp0
