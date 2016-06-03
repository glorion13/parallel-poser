# parallel-poser
System for automatically posing 3D models from 2D images.

GPU-PSO
============

Required libraries:
-------------------

* OpenCV (>2.4.2)
* Assimp SDK
* Freeglut

Environment variables:
----------------------

* ASSIMP_INCLUDE: assimp\assimp--3.0.1270-sdk\include;C:\Programming\assimp\assimp--3.0.1270-sdk\lib\assimp_debug-dll_win32;C:\Programming\assimp\assimp--3.0.1270-sdk\lib\assimp_debug-dll_x64;C:\Programming\assimp\assimp--3.0.1270-sdk\lib\assimp_release-dll_win32;C:\Programming\assimp\assimp--3.0.1270-sdk\lib\assimp_release-dll_x64
* FREEGLUT: freeglut\
* opencv\opencv2-4-6\

To-do list:
-----------

* Loading of 3D models.
* Loading of skeletons.
* Animation (joint manipulation, joint constraints).
* Silhouette descriptor.
* Joint descriptor.
* Distance metrics.

Completed:
----------

* PSO implementation.
* Overall structure of the project.
* OpenGL rendering.
* Separation of fitness function from main meta-heuristic algorithm.
* Seperation of update functions for particles for further experimentation.

Further research notes:
-----------------------

* * KD-tree? Either to limit the search space, but also for combination with database.
* Different meta-heuristics?
* Different descriptors? Silhouette, edge, joint... what else? (e.g. DCT better than HLAC and other nonlinear methods)
* Additional user input (e.g. relative depths between joints)
* IK initialisation
* What happens with multiple frames if temporal data exists?

For UI:
--------

* GrabCut to segment character from background?

Greater picture:
----------------

* First go through past papers where they do it with video
* Then show how some other metrics/descriptors actually improve performance
* Transfer this to the drawing problem rather than video
* Show how you can estimate the 3D pose similarly
* From optimisation go to database
* Show how database can work and what results it brings
* Show how it can be linked with the optimisation approach
* Unified system
