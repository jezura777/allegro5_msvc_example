# Example C project of allegro5 that is prepared to compile with MSVC

<<<<<<< HEAD
You can compile and run the program from x64 Native tools cmd by copying and running this command from the example project file root.
```bat
cl.exe .\src\main.c /I .\include\ .\lib\*.lib -o bin\main.exe & bin\main.exe                  & :: Compiles main.c to main.exe and executes main.exe
=======
You can compile and run the program from x64 Native tools cmd by copying and running this sequence of commands from the example project file root.
```bat
cl.exe .\src\main.c /I .\include\ .\lib\*.lib                       & :: Compiles the src/main.c with includes from include/ and all .lib from lib/ 
move main.exe bin\                                                  & :: Moves the main.exe to bin/main.exe the main.exe must be in bin/ because all the .dll that are there but if you installed allegro for mingw and the .dll's are in the PATH then you can run the main.exe from whereever you want 
del *.obj                                                           & :: Deletes all .obj
cd bin                                                              & :: goes to the bin/ directory
main.exe                                                            & :: Executes main.exe
cd ..                                                               & :: You are back to the directory root
>>>>>>> fcfa06237c93cb11281fa6ec6d2dd703f525b6c5
```
The example android compatible can't be compiled by MSVC to target android for that you need android studio have look at [allegro android app template](https://github.com/jezura777/liballeg-android-app-template)



