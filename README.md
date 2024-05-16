<!DOCTYPE html>
<html lang="en">
<body>
    <h1>HSHEX Image Processing in C</h1>
    <hr>
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
    <hr>
    <section id="mono-task">
        <h2>Task MONO: Convert Image to Monochrome (Greyscale)</h2>
        <p>The apply_MONO function converts an image from color to monochrome (greyscale) using the following formula:</p>
        <pre style="font-family: monospace;">0.299R + 0.587G + 0.114B</pre>
        <p>This formula computes a weighted sum of the red, green, and blue components of each pixel to produce greyscale output.</p>
        <!-- Add more explanation or instructions if needed -->
    </section>
    <hr>
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
    <hr>
    <h1>Steps to Run Image Processing:</h1>
    <ol>
        <li>Run <code>gcc -o process process.c</code> or run <code>make</code>.</li>
        <li>Run <code>./process input_file.hshex output_file.hshex</code>. <br>(input and output files are the image names to be replaced with. For example, if using the bars image, it will be <code>./process bars.hshex outputbars.hshex</code>).</li>
        <li>Run <code>./hsconvert -f PPM output_file.hshex output_file.ppm</code>. <br>(For example, if you have <code>outputbars.hshex</code>, it will be <code>./hsconvert -f PPM outputbars.hshex outputbars.ppm</code>).</li>
    </ol>
</body>
</html>
