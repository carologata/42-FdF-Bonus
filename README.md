> <h1>FdF</h1>

Status: finished

> <h3>New knowledge: </h3>
  + Basic Computer Graphics

> <h3>Description: </h3>
FdF is a short for 'fil de fer' which means wireframe model in french.
The purpose of this project is to build a representation of a landscape in 3D. 
It is achieved using the Codam Graphical Library as it includes basic necessary tools to open a window, create images
and deal with keyboard and mouse events. For more information access their repository https://github.com/codam-coding-college/MLX42.

> <h3> How to compile: </h3>

```bash
# clone repository
git clone https://github.com/carologata/42-FdF.git

# enter thee folder
cd 42-FdF

# compile Mandatory using Makefile
make

# the result of compilation is the executable
./fdf

# compile Bonus using Makefile
make bonus

# the result of compilation is the executable
./fdf_bonus

# There are some available maps to test in the maps directory.
# You can open the 3D maps using the command below, for example
./fdf maps/42.fdf

```

When the window is opened, the landscape is in Isometric Perspective, but when using the executable ./fdf_bonus you are allowed to do some rotations, translations, zooms etc.
See below some keyboard events:

+ Rotation in x
  + KEY A
  + KEY D

+ Rotation in y
  + KEY W
  + KEY S

+ Rotation in z
  + KEY K
  + KEY J

+ Translation in x
  + KEY RIGHT
  + KEY LEFT

+ Translation in y
  + KEY UP
  + KEY DOWN

+ Zoom
  + KEY KP ADD
  + KEY KP SUBTRACT

+ Increase or decrease the lanscape's height
  + KEY KP MULTIPLY
  + KEY KP DIVIDE

+ Views
  + KEY KP 1 (Isometric Perspective)
  + KEY KP 2 (Oblique Perspective)

+ Close the window
ESC

> <h3> Examples of 3D landscapes generated: </h3>

![Screenshot from 2024-03-05 09-30-18](https://github.com/carologata/42-FdF/assets/105884639/384867dc-4cd1-44a4-a97a-25ef8f1b3dd3)

![Screenshot from 2024-03-05 09-32-04](https://github.com/carologata/42-FdF/assets/105884639/7c71e7be-33a1-4c53-a3c9-ef4cbb7c1f12)

