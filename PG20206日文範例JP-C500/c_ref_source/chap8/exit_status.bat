@echo off

exit.exe
if errorlevel 2 echo "終了ステータスは2以上"
if errorlevel 1 echo "終了ステータスは1以上"
if errorlevel 0 echo "終了ステータスは0以上"

