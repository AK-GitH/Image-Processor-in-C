1) Format: HSHEX    
2) Color-effect: MONO
3) Histogram of the pixels

Steps to run:
---------------------------------------------->
1) run "gcc -o process process.c" or run "make"

2) ./process input_file.hshex output_file.hshex
(input and output file are the image names to be replaced with. eg: if using bars image, it will be "./process bars.hshex outputbars.hshex")

3) ./hsconvert -f PPM output_file.hshex output_file.ppm
(eg: if you have outputbars.hshex, it will be "./hsconvert -f PPM outputbars.hshex outputbars.ppm")
