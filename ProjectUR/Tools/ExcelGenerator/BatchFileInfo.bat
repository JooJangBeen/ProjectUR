@echo off
set BATCH_PATH=%CD%
set SCRIPT_PATH=%BATCH_PATH%\ExcelToCsv.ps1
set EXCEL_PATH=C:\UnrealProject\ProjectUR\ProjectUR\Content\Data\Excel
set CSV_PATH=C:\UnrealProject\ProjectUR\ProjectUR\Content\Data\CSV\
set JSON_PATH=C:\UnrealProject\ProjectUR\ProjectUR\Content\Data\ExcelData.json

call ExcelToCsv.bat

pause