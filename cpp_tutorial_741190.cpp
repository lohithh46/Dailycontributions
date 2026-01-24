// Learning Objective:
// This tutorial will teach you how to render and explore the Mandelbrot fractal
// in C++ using basic graphics. We will focus on the core concept of iterating
// a complex function and mapping the results to colors, providing a visual
// representation of this fascinating mathematical set.

#include <iostream>  // For standard input/output operations (like printing messages)
#include <complex>   // For using complex numbers (essential for Mandelbrot)
#include <vector>    // For storing pixel data (our image)
#include <fstream>   // For writing the image to a file (PPM format)

// Define a simple struct to represent an RGB color
struct RGB {
    unsigned char r, g, b;
};

// Function to map the iteration count to an RGB color.
// This is where the visual "coloring" of the fractal happens.
// Different coloring schemes can dramatically change the appearance.
RGB getColor(int iterations, int maxIterations) {
    // If the point escaped (reached maxIterations), color it black.
    if (iterations == maxIterations) {
        return {0, 0, 0}; // Black
    }

    // Otherwise, create a color based on how quickly it escaped.
    // This is a simple gradient. More complex schemes exist.
    // We use modulo to cycle through a range of colors.
    int colorValue = (iterations * 255) / maxIterations;
    return {(unsigned char)(colorValue % 255), (unsigned char)(colorValue * 2 % 255), (unsigned char)(colorValue * 4 % 255)};
}

// Function to generate the Mandelbrot fractal image.
// It iterates over each pixel, maps it to a complex number,
// and calculates its escape time.
void generateMandelbrot(int width, int height, int maxIterations, double zoom, double offsetX, double offsetY, const std::string& filename) {
    // We'll store our image data as a vector of RGB pixels.
    std::vector<RGB> image(width * height);

    // The Mandelbrot set is defined in the complex plane.
    // These variables define the boundaries of the region we are viewing.
    // By changing zoom, offsetX, and offsetY, we can "zoom into" and "pan" the fractal.
    double realStart = -2.0 * zoom - offsetX;
    double realEnd = 1.0 * zoom - offsetX;
    double imagStart = -1.5 * zoom - offsetY;
    double imagEnd = 1.5 * zoom - offsetY;

    // Loop through each pixel in the image.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Map the pixel coordinates (x, y) to a complex number (c) in the complex plane.
            // This is a linear mapping from pixel space to the complex plane's real and imaginary axes.
            double real = realStart + (double)x / (width - 1) * (realEnd - realStart);
            double imag = imagStart + (double)y / (height - 1) * (imagEnd - imagStart);
            std::complex<double> c(real, imag); // The complex number we test

            // Now, we iterate the Mandelbrot function: z = z*z + c
            // starting with z = 0.
            std::complex<double> z(0.0, 0.0);
            int iterations = 0;

            // The core of the Mandelbrot calculation.
            // We check if the magnitude of 'z' exceeds a certain threshold (typically 2.0).
            // If it does, the point is considered to have "escaped" the set.
            // If it doesn't escape within 'maxIterations', we assume it's part of the set.
            while (std::norm(z) < 4.0 && iterations < maxIterations) { // std::norm(z) is |z|^2
                z = z * z + c; // The Mandelbrot formula
                iterations++;
            }

            // Store the color for this pixel based on how many iterations it took to escape.
            image[y * width + x] = getColor(iterations, maxIterations);
        }
    }

    // Save the generated image to a file in PPM format.
    // PPM is a simple, uncompressed image format that is easy to write.
    std::ofstream ofs(filename);
    if (!ofs.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // PPM header: P3 means color, followed by width, height, and max color value.
    ofs << "P3\n" << width << " " << height << "\n255\n";

    // Write the pixel data.
    for (const auto& pixel : image) {
        ofs << (int)pixel.r << " " << (int)pixel.g << " " << (int)pixel.b << "\n";
    }

    ofs.close();
    std::cout << "Mandelbrot image saved to " << filename << std::endl;
}

// Example Usage:
// This demonstrates how to call the generateMandelbrot function.
// You can modify the parameters to explore different parts of the fractal.
int main() {
    // Image dimensions
    const int IMAGE_WIDTH = 800;
    const int IMAGE_HEIGHT = 600;
    // Maximum number of iterations. Higher values reveal more detail but take longer.
    const int MAX_ITERATIONS = 100;

    // Parameters for initial view:
    // zoom = 1.0 shows the standard view. Smaller values zoom in.
    // offsetX, offsetY shift the center of the view.
    double zoom = 1.0;
    double offsetX = 0.0;
    double offsetY = 0.0;

    // Generate the fractal and save it to "mandelbrot.ppm"
    generateMandelbrot(IMAGE_WIDTH, IMAGE_HEIGHT, MAX_ITERATIONS, zoom, offsetX, offsetY, "mandelbrot.ppm");

    // Example of zooming into a specific region:
    // Let's try zooming into a visually interesting part.
    // You can find coordinates and zoom levels by trial and error or
    // by using specialized fractal viewers.
    std::cout << "\nGenerating a zoomed-in view..." << std::endl;
    generateMandelbrot(IMAGE_WIDTH, IMAGE_HEIGHT, 500, 0.001, -0.7436, 0.1318, "mandelbrot_zoomed.ppm");

    return 0;
}