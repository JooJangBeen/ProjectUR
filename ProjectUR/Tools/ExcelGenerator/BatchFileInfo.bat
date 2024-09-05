@echo off

REM 배치파일 현재 경로
set BATCH_PATH=%CD%

REM 파워쉘 스크립트 경로
set SCRIPT_PATH=%BATCH_PATH%\ExcelToCsv.ps1

REM 엑셀 위치 경로 설정
set EXCEL_PATH=C:\UnrealProject\ProjectUR\ProjectUR\Content\Data\Excel

REM CSV 파일 저장 경로 설정
set CSV_PATH=C:\UnrealProject\ProjectUR\ProjectUR\Content\Data\CSV\

REM JSON 파일 저장 경로 설정
set JSON_PATH=C:\UnrealProject\ProjectUR\ProjectUR\Content\Data\ExcelData.json

REM 언리얼 엔진 경로 설정
set UE5_PATH="C:\Program Files\Epic Games\UE_5.4"

REM .uproject 파일 경로 설정
set PROJECT_PATH="C:\UnrealProject\ProjectUR\ProjectUR\ProjectUR.uproject"

call ExcelToCsv.bat
call UnrealBuildTool.bat

pause