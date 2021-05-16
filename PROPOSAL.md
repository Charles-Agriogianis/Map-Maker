This project will be focused on creating a map creation tool for tabletop and board games as well as a randomised generator that creates
maps based on certain criteria given by the user.

The parts of this project are:
  * A drag and drop user interface where the user can create objects for things like tables, chairs, and other forms of cover and place
    them were they want
  * A randomiser that has several drop down menus to customize parameters and creates a randomly generated map
  * A file interaction system that can store these parts as files for printing and split them into multiple sheets of paper that a
    person could then assemble to create a larger map
  * A way to print out the smaller elements of a map to be placed on top of a grid
  * A way to create basic and hand drawn shapes and fill them in with texture
  * A way to define rooms so that player can print them seperately or print correctly sized covers for those rooms that they can cut out
  * A system the generates a key for the map that tells the players what everything is
    
Libraries that are needed:
  * A library that can create or use basic shapes and images to represent part of the map
  * A library to create UI elements and allow for the dragging and dropping of objects as well as the use of drop down menus
  
For now both of these will be achieved through open frameworks with the cairo library and open gl inside open frameworks being used for the shape generation and other libraries and features of open frame works for the various aspects of the GUI, most of these will be contained in the GUI add on for open frame works.
