@echo off
chcp 65001 >nul
title Bat lai launcher goc Google TV
echo ============================================================
echo  BAT LAI LAUNCHER GOC GOOGLE TV (hoan nguyen)
echo ============================================================
echo  TV phai dang bat "Go loi ADB" va cung mang voi may tinh.
echo.
set /p TVIP="Nhap dia chi IP cua TV, vi du 192.168.1.50: "
echo.
adb connect %TVIP%:5555
echo --- Bat lai launcher goc (launcherx) ...
adb -s %TVIP%:5555 shell pm enable com.google.android.apps.tv.launcherx
echo --- Bat lai trinh cai dat (setupwraith) ...
adb -s %TVIP%:5555 shell pm enable com.google.android.tungsten.setupwraith
echo --- Kiem tra: Home hien tai la ai? ---
adb -s %TVIP%:5555 shell cmd package resolve-activity --brief -a android.intent.action.MAIN -c android.intent.category.HOME
echo.
echo XONG. Bam nut HOME tren remote, TV se ve launcher goc.
pause
