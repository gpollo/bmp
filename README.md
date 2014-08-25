BMP
=======

This is a small program will apply an algorithm which I do not know the name to an image. I programmed it as a test for working with BMP file, image and pixel.


Installation
------------

	$ make
	$ sudo make install
	
Uninstallation
--------------

	$ sudo make uninstall

Usage
-----

This program takes 2 arguments. The input file and the output file. The files must be in BMP format. Do not expect all BMP files to works. I did not implement full BMP standard.

	$ bmp img/circle0.bmp img/circle1.bmp
  
An interesting effect happens when you recursively apply the algorithm to the output file. The image will get back to it's original form. I created a small script that will help you apply the algorithm multiple times.

	$ ./start
  
You might want to edit the script to fit your needs.


<p align="center">
	<img src="/img/example.png" alt="example.png">
</p>

