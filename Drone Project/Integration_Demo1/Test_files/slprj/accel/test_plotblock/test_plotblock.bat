@echo off
set MATLAB=C:\Program Files\MATLAB\R2015a
"%MATLAB%\bin\win64\gmake" -f test_plotblock.mk  ISPROTECTINGMODEL=NOTPROTECTING
