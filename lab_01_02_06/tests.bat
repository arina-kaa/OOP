@echo off

REM Путь к  тестируемой программе передается через 1-й аргумент командной строки
set PROGRAM="%~1"
set COUNTER=1

REM Защита от запуска без аргумента, задающего путь к программе
if %PROGRAM%=="" (
    echo Please specify path to program
    exit /B 1
)

REM Запуск без аргументов
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Некорректное количество аргументов
%PROGRAM% 2 2 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Некорректная исходная нотация
%PROGRAM% 0 2 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% -1 2 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Некорректная итоговая нотация
%PROGRAM% 2 0 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% 2 -1 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Число не входит в диапазон допустимых значений нотации
%PROGRAM% 2 2 A > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% 2 2 2 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% 10 2 -21474800000000 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% 10 2 2147483648 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% 10 2 -2147483648 > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод положительного числа из 10 в 16
%PROGRAM% 10 16 255 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\255_10_16.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод отрицательного числа из 10 в 16
%PROGRAM% 10 16 -255 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\-255_10_16.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод нуля из 10 в 16
%PROGRAM% 10 16 0 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\0_10_16.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод положительного числа из 16 в 10
%PROGRAM% 16 10 fF > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\fF_16_10.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод отрицательного числа из 16 в 10
%PROGRAM% 16 10 -fF > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\-fF_16_10.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод нуля из 16 в 10
%PROGRAM% 16 10 0 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\0_16_10.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод INT_MAX из 10 в 2
%PROGRAM% 10 2 2147483647 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\2147483647_10_2.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Перевод INT_MIN из 10 в 2
%PROGRAM% 10 2 -2147483647 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\-2147483647_10_2.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Ошибка
:err
echo Test failed
exit /B 1
