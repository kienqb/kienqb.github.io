@echo off
chcp 65001 >nul
title Thay launcher goc Google TV bang launcher TvHome
echo ============================================================
echo  THAY LAUNCHER GOC GOOGLE TV BANG LAUNCHER TVHOME
echo ============================================================
echo  Dieu kien: TV da cai launcher TvHome (ban share), TV dang bat
echo  "Go loi ADB" va cung mang Wi-Fi/LAN voi may tinh nay.
echo  Script se TAT 2 goi cua Google TV:
echo    - com.google.android.tungsten.setupwraith (trinh cai dat)
echo    - com.google.android.apps.tv.launcherx   (launcher goc)
echo  Tat xong bam Home se ve launcher TvHome. Muon quay lai thi
echo  chay file: bat-lai-launcher-goc-google-tv.bat
echo ============================================================
echo.
set /p TVIP="Nhap dia chi IP cua TV (Cai dat > Mang tren TV), vi du 192.168.1.50: "
echo.
echo --- Dang ket noi toi TV %TVIP% ...
adb connect %TVIP%:5555
echo.
echo --- Kiem tra launcher TvHome da cai chua ...
adb -s %TVIP%:5555 shell pm list packages com.gathin.tvhome | findstr /C:"com.gathin.tvhome" >nul
if errorlevel 1 (
  echo [LOI] Chua thay launcher TvHome tren TV. Cai APK launcher truoc roi chay lai script nay.
  pause
  exit /b 1
)
echo [OK] Da thay launcher TvHome.
echo.
echo --- Mo thu launcher TvHome tren TV de kiem tra ...
adb -s %TVIP%:5555 shell am start -n com.gathin.tvhome/.MainActivity
echo Hay nhin len TV: launcher TvHome co hien len binh thuong khong?
echo Neu hien tot, bam phim bat ky de TIEP TUC tat launcher goc.
echo Neu khong hien/treo, dong cua so nay lai va dung lam tiep.
pause >nul
echo.
echo --- Dat TvHome lam man hinh chinh mac dinh ...
adb -s %TVIP%:5555 shell cmd package set-home-activity com.gathin.tvhome/.MainActivity
echo.
echo --- Tat trinh cai dat (setupwraith) ...
adb -s %TVIP%:5555 shell pm disable-user --user 0 com.google.android.tungsten.setupwraith
echo --- Tat launcher goc Google TV (launcherx) ...
adb -s %TVIP%:5555 shell pm disable-user --user 0 com.google.android.apps.tv.launcherx
echo.
echo --- Kiem tra: Home hien tai la ai? ---
adb -s %TVIP%:5555 shell cmd package resolve-activity --brief -a android.intent.action.MAIN -c android.intent.category.HOME
echo (Dong ket qua phai la: com.gathin.tvhome/.MainActivity)
echo.
echo ============================================================
echo  XONG. Bam nut HOME tren remote de kiem tra.
echo  Luu y:
echo   - Nut hinh banh rang (Cai dat nhanh) tren remote co the
echo     khong mo nua; vao Cai dat bang launcher TvHome.
echo   - Dung tat "Go loi ADB" tren TV: do la duong lui duy nhat
echo     neu can bat lai launcher goc.
echo   - Neu Wi-Fi cua TV bi rot sau khi tat, vao Cai dat > Mang
echo     tren TV ket noi lai binh thuong.
echo   - TV cap nhat phan mem lon co the tu bat lai launcher goc,
echo     gap lai thi chay lai script nay.
echo ============================================================
pause
