// exit_status.js
var wsh, err;

wsh = WScript.CreateObject("WScript.Shell");
err = wsh.Run("exit.exe", 0, 1);
WScript.Echo("µ²§ôª¬ºA½X¬° ",err," ¡C");

