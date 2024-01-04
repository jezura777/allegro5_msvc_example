# Example C project of allegro5 that is prepared to compile with MSVC

You can compile and run the program from x64 Native tools cmd by copying and running this command from the example project file root.
```bat
cl.exe .\src\main.c /I .\include\ .\lib\*.lib -o bin\main.exe & bin\main.exe                  & :: Compiles main.c to main.exe and executes main.exe
```
The example android compatible can't be compiled by MSVC to target android for that you need android studio have look at [allegro android app template](https://github.com/jezura777/liballeg-android-app-template)



