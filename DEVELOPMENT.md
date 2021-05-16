To start developing the project I have to get used to the libraries I want to use. To do this I am going to begin the project by using
the open frameworks GUI add on to create some of the basic UI elements that I want to use. This includes drop down menus, buttons,
and sliders.

Slider were relatively easy to implement and the gui add on was easy to setup. I have been experimenting with mdoifying the various aspects of a shape and it has been going well.

I have also gotten dragging working and can now make the object follow your cursor when you press a certain button. Next up is the loading of images files which can be used as textures and then placing these textures on the shapes that are being drawn.

I have started the implementation of draging to create shapes of various sizes. I have also been working on the various buttons needed for creating different line thicknesses, color slider, and wether or not a shapes is filled. Issues I ran into was that the line thickness needed to stay with in a certain range and an ideal resolution had to be found as if the combination was not right there would be gaps or notches in the circle which looked very incorrect.

Here is my current to do list:

To do list:
* Find out how to overlay a texture on top of a shape in open frame works
* Create a struct that stores aspects of shapes such as their position, name, if they are filled, their fill color, their line thickness, their size, their texture, and their layer height
*	Add all these elements to be able to be modified if these shapes are selected in the gui
*	Add a way to display all the currently created shapes in a list on the side
*	Add a circle marker over the center of the shape that you currently have selected 
*	Add a way to free draw shapes using line by creating a vector of points and connecting them in order with the final point connecting back to the starting point
*	Add a way to display the points saved for these shapes and be able to modify them
*	Add a snapping effect for both drawing lines and moving shapes around that stops the cursor when they hover over position that lock with other objects or place lines so that they are equal to the x and y of other notable points 
*	Build up a library of textures and basic shapes that user can use
*	Allow the ability to type and add text to your maps
*	Add the ability to print out these maps as a pdf and distribute them across multiple sheets of paper or as individual elements
*	Add a grid to the view
*	Random generation
*	Add a way to create creature and hero tokens that can be added
*	Add clicking a dragging as an option for shape generation

Right now I am currently focused on getting to draw shapes of ofPolyline and using that tool to create shapes like squares, circles, rectangles, and triangles

I have fixed the texturing issue by using an fbo and setting an alpha mask for the shape over the image.

Shapes are now created as a vector of points that I can then read from. This makes them very easy to edit as I can just change the position of the points to easily change how the shapes look.

It also means that I can store them all in one shape struct and can use the same methods on all of them.

Issues were ran into in creating a list of buttons for all the shapes so you could select them as trying to create buttons ran into issues where all the buttons ended up being indentified as the same button depsite being created in seperate blocks of code. This was solved b placing the buttons in the shape struct which for some reason fixed the issue.

With the amount of time it took to implement each feature and the number of feature additions that I want to add to the project I have decidded to romove the random generation aspect of the project. Each was a stretch goal anyways and wasnt as directly related as the other parts. 

Code has been added to implement grids that the user can controll the color and size of. Code has also been implemented for adding text to the map. Much of this code works very similar to the shape code except it interacts with a slightly different struct. I tried to implement it in a way that had less redundant code but because of the way the struct was made and the multidude of differences between the two structs it did not really work. There were some issues with being able to scale the text but they were resolved once I switched to a font based system instead of a bitmap string.

The next feature implemtented was the ability to hide and delete shapes. This is important both from a user perspective and for my own uses as I would need to hide elements when I wanted to print the current screen to a file. The implementation of the toggles and the checks were relativley simple. An issue was ran into with creating a new shape after as a defined the selected shape on shape creation to the current shape count instead of the max instead of the shape vector so an out of bounds error would occur. This was an easy fix once the bug was noticed.

Now the only features left ot try and implement that arent add ons are printing the results to a file and the dragging feature.

The dragging feature has had various isssues in its developement so far. It has both inconsistent behavior and currently constantly shrinks when used. I will have to take the alorithm back to the drawing board most likley to figure out why.

Couldnt get drag working and I have ran out of time.

Movement of the index of shape and text ended up being relativley easy. Initially had issues with the gui not updating but placing a change in selected shape on move fixed the issue.

Deletion was also relatively easy although open frame works would not let me use the erase function, instead I had to add all the functions not to be delted to a vector and sub that new vector in for the old one. After that it worked well.

I thought about segmenting the program into a large number of files but I decided agaisnt it as most of the files are directly related and there werent distinct sections of my project. Eberything was presentation and user interaction and multiple files would just create uneccesary bloat and complexity.
