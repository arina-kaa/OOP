@echo off

REM ���� �  ����������� ��������� ���������� ����� 1-� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
    echo Please specify path to program
    exit /B 1
)

REM ����������� ������� �����
%MyProgram% input_empty.txt "%TEMP%\output.txt" || goto err
fc input_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM ����������� �� ������� �����
%MyProgram% input_non_empty.txt "%TEMP%\output.txt" || goto err
fc input_non_empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM ����������� �������������� �����
%MyProgram% input_missing.txt "%TEMP%\output.txt" > nul && goto err
echo Test 3 passed

REM �� ������ �������������� ��������� ��������� ������
%MyProgram% input_missing.txt > nul && goto err
echo Test 4 passed

REM �� ������ ������������� ���������� ��������� ������
%MyProgram% > nul && goto err
echo Test 5 passed

REM ����� ������ �������
echo All tests passed successfully
exit /B 0

REM ������
:err
echo Test failed
exit /B 1