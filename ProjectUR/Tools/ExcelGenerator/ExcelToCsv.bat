@echo off

setlocal

REM 환경 변수로 설정
set "EXCEL_SOURCE_FOLDER=%EXCEL_PATH%"
set "EXCEL_OUTPUT_FOLDER=%CSV_PATH%"
set "EXCEL_JSON_FILE=%JSON_PATH%"

REM PowerShell 스크립트 실행
powershell -NoProfile -ExecutionPolicy Bypass -File %SCRIPT_PATH%

REM 변환 완료 메시지
echo 모든 Excel 파일이 CSV로 변환되었으며, 모든 정보가 하나의 JSON 파일에 저장되었습니다.

endlocal