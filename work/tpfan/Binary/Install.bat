@copy tpfan.sys %systemroot%\system32\drivers
@sc create tpfan binPath= "%systemroot%\system32\drivers\tpfan.sys" type= kernel start= auto DisplayName= "ThinkPad Fan Control"
@sc start tpfan
@copy Monitor.exe "%USERPROFILE%\..\All Users\Start Menu\Programs\Startup"
