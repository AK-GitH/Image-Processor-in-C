<head>
    <title>HSHEX Image Processing</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
        }
        h1, h2, h3 {
            color: #333;
        }
        p {
            margin-bottom: 15px;
        }
        pre {
            background-color: #f4f4f4;
            padding: 10px;
            overflow-x: auto;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <h1>HSHEX Image Processing Tasks</h1>
    <section id="hshex-description">
        <h2>HSHEX Image Format Description</h2>
        <p>An HSHEX image consists entirely of ASCII text. It starts with a header:</p>
        <pre>
HSHEX
width height here:
        </pre>
        <p>Explanation of fields:</p>
        <ul>
            <li><strong>HSHEX</strong> — fixed code indicating HSHEX format</li>
            <li><strong>width</strong> — integer number of columns</li>
            <li><strong>height</strong> — integer number of rows</li>
        </ul>
        <p>The image data follows the header. Each pixel is stored as three unsigned 16-bit values as hexadecimal numbers.</p>
    </section>
    <section id="mono-task">
        <h2>Task MONO: Convert Image to Monochrome (Greyscale)</h2>
        <p>The apply_MONO function converts an image from color to monochrome (greyscale) using the following formula:</p>
        <pre style="font-family: monospace;">0.299R + 0.587G + 0.114B</pre>
        <p>This formula computes a weighted sum of the red, green, and blue components of each pixel to produce greyscale output.</p>
        <!-- Add more explanation or instructions if needed -->
    </section>
    <section id="hist-task">
        <h2>Task HIST: Compute Histogram of Image</h2>
        <p>The apply_HIST function computes a histogram of the red, green, and blue values used in the image. It counts how many times each value occurs and displays the results.</p>
        <p>Example output:</p>
        <pre>
Value 0: 123 pixels
Value 1: 55 pixels
Value 2: 8729 pixels
...
Value 255: 17 pixels
        </pre>
    </section>
</body>
</html>


Steps to run:
---------------------------------------------->
1) run "gcc -o process process.c" or run "make"

2) ./process input_file.hshex output_file.hshex
(input and output file are the image names to be replaced with. eg: if using bars image, it will be "./process bars.hshex outputbars.hshex")

3) ./hsconvert -f PPM output_file.hshex output_file.ppm
(eg: if you have outputbars.hshex, it will be "./hsconvert -f PPM outputbars.hshex outputbars.ppm")
