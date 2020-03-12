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
%PROGRAM% pack input_empty.txt > nul
if NOT ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM При запуске компрессии
%PROGRAM% pack input_empty.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" output_empty.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% pack input_3_0.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" output_3_0.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% pack input_255_A.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" output_255_A.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% pack input_256_A.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" output_256_A.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% pack input_257_AB.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" output_257_AB.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% pack input_with_spaces.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" output_with_spaces.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

REM При запуске декомпрессии
%PROGRAM% unpack output_empty.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_empty.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% unpack output_3_0.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_3_0.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% unpack output_255_A.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_255_A.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% unpack output_256_A.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_256_A.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% unpack output_257_AB.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_257_AB.txt > nul
if ERRORLEVEL 1 goto err
echo Test %COUNTER% passed
set /A COUNTER=%COUNTER%+1

%PROGRAM% pack "D:\IPS\OOP\lab_01_04_01\Debug\lab_01_04_01.exe" "%TEMP%\output_exe.exe"
if ERRORLEVEL 1 goto err
%PROGRAM% unpack "%TEMP%\output_exe.exe" "%TEMP%\output.exe"
if ERRORLEVEL 1 goto err
fc /B "%TEMP%\output.exe" "D:\IPS\OOP\lab_01_04_01\Debug\lab_01_04_01.exe" > nul
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