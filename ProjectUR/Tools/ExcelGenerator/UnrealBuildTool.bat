@echo off

REM Generate Visual Studio project files 실행
%UE5_PATH%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe -projectfiles -project=%PROJECT_PATH% -game -engine -progress

pause