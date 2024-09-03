[System.Console]::OutputEncoding = [System.Text.Encoding]::UTF8

$sourceFolder = $env:EXCEL_SOURCE_FOLDER
$outputFolder = $env:EXCEL_OUTPUT_FOLDER
$jsonFile = $env:EXCEL_JSON_FILE

$excelData = @()
Get-ChildItem $sourceFolder -Filter *.xlsx | ForEach-Object {
    $excelFile = $_.FullName
    $outputPath = $outputFolder + $_.BaseName
    $Excel = New-Object -ComObject Excel.Application
    $Excel.Visible = $false
    $Excel.DisplayAlerts = $false
    $Workbook = $Excel.Workbooks.Open($excelFile)
    $csvFileInfo = @()
    For ($i = 1; $i -le $Workbook.Sheets.Count; $i++) {
        $Sheet = $Workbook.Sheets.Item($i)
        $csvFile = $outputPath + '_' + $Sheet.Name + '.csv'
        $Sheet.SaveAs($csvFile, 6)
        $csvFileInfo += @{ SheetName = $Sheet.Name; CsvFileName = [System.IO.Path]::GetFileName($csvFile) }
    }
    $Workbook.Close($false)
    $excelData += @{ ExcelFileName = [System.IO.Path]::GetFileName($excelFile); Sheets = $csvFileInfo }
    $Excel.Quit()
    [System.Runtime.Interopservices.Marshal]::ReleaseComObject($Excel) | Out-Null
}
$excelData | ConvertTo-Json -Depth 3 | Set-Content $jsonFile -Encoding UTF8