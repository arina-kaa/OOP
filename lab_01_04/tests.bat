@echo off

REM Путь к  тестируемой программе передается через 1-й аргумент командной строки
SET PROGRAM="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %PROGRAM%=="" (
    echo Please specify path to program
    exit /B 1
)

REM При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

REM При запуске с правильными параметрами ожидается нулевой код возврата (search не пустой)
%PROGRAM% input.txt "%TEMP%\output.txt" 1231234 000
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_with_replace.txt > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

REM При запуске с правильными параметрами ожидается нулевой код возврата (search пустой)
%PROGRAM% input.txt "%TEMP%\output.txt" "" 000
if ERRORLEVEL 1 goto err
fc input.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

REM При запуске с пустым файлом
%PROGRAM% input_empty.txt "%TEMP%\output.txt" 1231234 000
if ERRORLEVEL 1 goto err
fc input_empty.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибка
:err
echo Test failed
exit /B 1