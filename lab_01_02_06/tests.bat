@echo off

REM ���� �  ����������� ��������� ���������� ����� 1-� �������� ��������� ������
SET PROGRAM="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %PROGRAM%=="" (
    echo Please specify path to program
    exit /B 1
)

REM ������ ��� ����������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

REM ������������ ���������� ����������
%PROGRAM% 2 2 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 2 passed

REM ������������ �������� �������
%PROGRAM% 0 2 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 3 passed

%PROGRAM% -1 2 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 4 passed

REM ������������ �������� �������
%PROGRAM% 2 0 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 5 passed

%PROGRAM% 2 -1 0 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 6 passed

REM ����� �� ������ � �������� �������
%PROGRAM% 2 2 A > nul
if NOT ERRORLEVEL 1 goto err
echo Test 7 passed

%PROGRAM% 2 2 2 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 8 passed

%PROGRAM% 10 2 -21474800000000 > nul
if NOT ERRORLEVEL 1 goto err
echo Test 9 passed

REM ������� �������������� ����� �� 10 � 16
%PROGRAM% 10 16 255 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\255_10_16.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

REM ������� �������������� ����� �� 10 � 16
%PROGRAM% 10 16 -255 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\-255_10_16.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

REM ������� ���� �� 10 � 16
%PROGRAM% 10 16 0 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\0_10_16.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 12 passed

REM ������� �������������� ����� �� 16 � 10
%PROGRAM% 16 10 fF > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\fF_16_10.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 13 passed

REM ������� �������������� ����� �� 16 � 10
%PROGRAM% 16 10 -fF > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\-fF_16_10.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 14 passed

REM ������� ���� �� 16 � 10
%PROGRAM% 16 10 0 > "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc tests\0_16_10.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 15 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1
