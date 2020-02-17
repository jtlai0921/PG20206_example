' exit_status.vbs
Option Explicit
Dim wsh, err
set wsh = WScript.CreateObject("WScript.Shell")

err = wsh.Run("exit.exe", 0, 1)
WScript.Echo "終了ステータスは " & err & " です"


