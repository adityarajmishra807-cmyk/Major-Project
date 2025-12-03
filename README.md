## Food Ordering System
Description
The Food Ordering System is a console-based application designed to streamline the process of ordering food and generating bills in a restaurant setting. It allows users to view the menu, place orders for multiple items, automatically calculate totals with GST and discounts, view order history, and provide customer ratings. This project demonstrates the use of structured programming in C, file handling for data persistence (orders.txt and ratings.txt), and a user-interactive menu-driven design. It serves as an excellent major project for academic purposes, showcasing real-world logic implementation.

Repository Structure
```
/
|-- src/              (all .c files)
|-- include/          (all .h files)
|-- docs/             (project report, flowcharts, assets)
|-- assets/           (optional: screenshots, diagrams)
|-- README.md         (this file)
|-- sample_input.txt  (optional test inputs)
```

Getting Started
Prerequisites
To compile and run the project, ensure you have:

A C compiler (GCC recommended)

A terminal or command prompt

Make (optional, if using a Makefile)

Build Instructions
Step 1: Clone the Repository

git clone https://github.com/yourusername/food-ordering-system.git
Step 2: Navigate to the Source Directory

cd food-ordering-system/src
Step 3: Compile the Program
Bash

gcc main.c -o FoodOrder
Usage

+Run the program using the following command:

Bash

./FoodOrder
Key Features to Try:

Place Order: Select items by code, add quantities, and watch the system calculate the subtotal.

Discounts: Try entering code SAVE10 or FLAT50 when prompted.

Ratings: Leave a 5-star rating to see it saved in the feedback file.

Contributing
Fork the repository

Create a new branch (git checkout -b feature-new-menu)

Commit your changes (git commit -m 'Added new menu items')

Push the branch (git push origin feature-new-menu)

Create a pull request
