@echo off
@echo Check and Commit first
@echo Begin push ...
cd F:\workspace\Wallpaper
F:
hg push F:\����\SynWork\wallpaper
@echo push end.
cd F:\����\SynWork\wallpaper
hg update
@echo end
pause
cmd.exe
