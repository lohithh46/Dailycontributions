// Learning Objective: This tutorial will teach you how to create a basic animated image gallery with smooth fade transitions using JavaScript and CSS.
// We will focus on manipulating CSS classes with JavaScript to achieve the animation.

// HTML Structure (Conceptual - assume this is in your HTML file):
/*
<div class="gallery-container">
  <div class="gallery-item active">
    <img src="image1.jpg" alt="Image 1">
  </div>
  <div class="gallery-item">
    <img src="image2.jpg" alt="Image 2">
  </div>
  <div class="gallery-item">
    <img src="image3.jpg" alt="Image 3">
  </div>
  // ... more gallery items
</div>
<button id="prev-btn">Previous</button>
<button id="next-btn">Next</button>
*/

// CSS Styling (Conceptual - assume this is in your CSS file):
/*
.gallery-container {
  position: relative; // Important for positioning absolute elements within
  width: 600px;
  height: 400px;
  overflow: hidden; // Hides images that are not currently active
}

.gallery-item {
  position: absolute; // Allows images to stack on top of each other
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  opacity: 0; // Initially hide all images
  transition: opacity 0.5s ease-in-out; // Smooth fade transition over 0.5 seconds
  pointer-events: none; // Prevent interaction with non-active images
}

.gallery-item.active {
  opacity: 1; // Make the active image visible
  pointer-events: auto; // Allow interaction with the active image
}

.gallery-item img {
  width: 100%;
  height: 100%;
  object-fit: cover; // Ensures images cover the container without distortion
}

button {
  margin: 10px;
  padding: 10px 20px;
  cursor: pointer;
}
*/

// JavaScript Code

// 1. Get references to the necessary HTML elements.
// We need the container that holds all our images and the previous/next buttons.
const galleryContainer = document.querySelector('.gallery-container');
const galleryItems = document.querySelectorAll('.gallery-item'); // Get all image slides
const prevButton = document.getElementById('prev-btn');
const nextButton = document.getElementById('next-btn');

// 2. Initialize variables to keep track of the current image.
// `currentIndex` will tell us which image is currently displayed.
let currentIndex = 0;

// 3. Function to show a specific image by its index.
// This is the core logic for updating the gallery.
function showImage(index) {
  // First, remove the 'active' class from all gallery items.
  // This will trigger the CSS transition to fade them out.
  galleryItems.forEach(item => item.classList.remove('active'));

  // Then, add the 'active' class to the gallery item at the specified index.
  // This will trigger the CSS transition to fade this image in.
  // We also handle wrapping around if the index is out of bounds.
  if (index >= galleryItems.length) {
    currentIndex = 0; // Wrap around to the first image
  } else if (index < 0) {
    currentIndex = galleryItems.length - 1; // Wrap around to the last image
  } else {
    currentIndex = index; // Set the current index to the provided index
  }

  // Apply the 'active' class to the correct item.
  galleryItems[currentIndex].classList.add('active');
}

// 4. Add event listeners to the navigation buttons.
// When the 'Next' button is clicked, we increment `currentIndex` and call `showImage`.
nextButton.addEventListener('click', () => {
  showImage(currentIndex + 1); // Move to the next image
});

// When the 'Previous' button is clicked, we decrement `currentIndex` and call `showImage`.
prevButton.addEventListener('click', () => {
  showImage(currentIndex - 1); // Move to the previous image
});

// 5. Initialize the gallery by showing the first image when the page loads.
// This ensures that the gallery is ready to be viewed from the start.
document.addEventListener('DOMContentLoaded', () => {
  showImage(currentIndex); // Display the first image (index 0)
});

// Example Usage:
// 1. Create your HTML file with the gallery structure and buttons.
// 2. Link your CSS file for styling.
// 3. Link this JavaScript file at the end of your HTML's <body> tag.
// 4. Replace "image1.jpg", "image2.jpg", etc., with your actual image paths.
// 5. Test by clicking the "Previous" and "Next" buttons. You should see a smooth fade transition between images.