@echo off

exit.exe
if errorlevel 2 echo "終止狀態碼為2以上"
if errorlevel 1 echo "終止狀態碼為1以上"
if errorlevel 0 echo "終止狀態碼為0以上"

