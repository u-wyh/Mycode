@echo off
cd /d "C:\洛谷"
set total=0

for /r %%i in (*.cpp *.c *.py) do (
    for /f %%j in ('type "%%i" 2^>nul ^| find /c /v ""') do (
        set /a total+=%%j
        echo [%%~ni] 行数: %%j
    )
)

echo.
echo ==========================
echo 总文件数: %count%
echo 总代码行数: %total%
echo ==========================
pause