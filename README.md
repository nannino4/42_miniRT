A 42 project about coding a simple cpu-based 3D raytracing engine in C.

The program takes as argument the path to the file containing the scene to be rendered.

The program can take different flags after the first argument:
  - `--save`      saves the rendered scene as an image;
  - `--aa`        renders the scene with anti aliasing;
  - `--threaded`  renders the scene using multithreading;

How to launch the program (MacOS):
- compile running the command `make` from the root project directory (the graphic library needs `swiftc` to be compiled!)
- run `./miniRT "PathToSceneFile" [--Options]`
- interact with mouse and keyboard (instructions for interactivity are found in the terminal once the program has been launched)

Some examples of how to run the program:
- `./miniRT scenes/cat.rt --threaded`
- `./miniRT scenes/shapes_0.rt --threaded --aa`
- `./miniRT scenes/wolf.rt --threaded --save`
