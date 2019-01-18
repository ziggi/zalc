# Zalc

A small, FLTK-based calculator

# Building on Windows

Before building, you should download latest version of FLTK from the https://www.fltk.org/software.php page.

Then, unpack it, and do the following commands:
```bash
cd YOUR_FLTK_DIR
mkdir build
cd build
cmake ..
```

Then build it by Visual Studio.

After it, do this:

```
mkdir build
cd build
cmake .. -DFLTK_DIR=D:/Downloads/fltk-1.3.4-2/build
```

And build it by Visual Studio.

# Building on Linux

You know what to do.
