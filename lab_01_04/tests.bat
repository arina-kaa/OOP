@echo off

REM ���� �  ����������� ��������� ���������� ����� 1-� �������� ��������� ������
SET PROGRAM="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %PROGRAM%=="" (
    echo Please specify path to program
    exit /B 1
)

REM ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err
echo Test 1 passed

REM ��� ������� � ����������� ����������� ��������� ������� ��� �������� (search �� ������)
%PROGRAM% input.txt "%TEMP%\output.txt" 1231234 000
if ERRORLEVEL 1 goto err
fc "%TEMP%\output.txt" input_with_replace.txt > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

REM ��� ������� � ����������� ����������� ��������� ������� ��� �������� (search ������)
%PROGRAM% input.txt "%TEMP%\output.txt" "" 000
if ERRORLEVEL 1 goto err
fc input.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

REM ��� ������� � ������ ������
%PROGRAM% input_empty.txt "%TEMP%\output.txt" 1231234 000
if ERRORLEVEL 1 goto err
fc input_empty.txt "%TEMP%\output.txt" > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1