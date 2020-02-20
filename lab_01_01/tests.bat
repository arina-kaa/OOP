@echo off

REM Путь к  тестируемой программе передается через 1-й аргумент командной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
    echo Please specify path to program
    exit /B 1
)

REM Копирование пустого файла
%MyProgram% input_empty.txt "%TEMP%\output.txt" || goto err
fc input_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Копирование не пустого файла
%MyProgram% input_non_empty.txt "%TEMP%\output.txt" || goto err
fc input_non_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Копирование отсутствующего файла
%MyProgram% input_missing.txt "%TEMP%\output.txt" > nul && goto err
echo Test 3 passed

REM На случай отсутствующего параметра командной строки
%MyProgram% input_missing.txt > nul && goto err
echo Test 4 passed

REM На случай отсутствующих параметров командной строки
%MyProgram% > nul && goto err
echo Test 5 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибка
:err
echo Test failed
exit /B 1