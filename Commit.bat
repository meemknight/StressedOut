@echo off

set /p input=Commit name: 

git add *.cpp
git add *.h
git add *.png
git add *.ttf
git add *.txt
git add debug/ *
git commit -m"%input%"
git push -u