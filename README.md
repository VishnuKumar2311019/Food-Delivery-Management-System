# 🍔 Food Ordering System

A **C-based Food Ordering System with a GTK+ graphical user interface** that helps users discover nearby hotels, explore food items, manage their cart, calculate bills, and receive food recommendations based on previous orders.

The system combines **location-based hotel discovery, sorting algorithms, file-based data persistence, user authentication, cart management, and recommendation logic** into a single desktop application.

---

## 📌 Overview

The Food Ordering System is designed to provide a convenient platform for users to browse available hotels and food items based on their preferences.

Users can:

* 🔐 Register and log in securely
* 📍 Enter their location using latitude and longitude
* 🏨 Discover hotels based on proximity and preferences
* 🎯 Sort hotels by distance and discounts
* 🍽️ Browse food items from selected hotels
* 🛒 Add and remove items from the cart
* 💰 Calculate the total bill
* ⭐ Receive recommendations based on popular previously ordered items
* 💾 Persist user, hotel, and order information using files

The application is implemented in **C** and uses **GTK+** to provide a graphical user interface.

---

## ✨ Key Features

### 🔐 User Authentication

* User registration and login
* Username and password-based authentication
* User credentials stored in `users.dat`
* New users can create accounts through the application

### 📍 Location-Based Hotel Discovery

Users can enter their latitude and longitude to find hotels based on geographical proximity.

The system uses the **Haversine Formula** to calculate the great-circle distance between the user's location and available hotels.

### 🏨 Hotel Filtering & Sorting

Hotels can be organized based on:

* Distance
* Discount percentage
* User preferences
* Vegetarian / non-vegetarian preference

The system first filters relevant hotels and then presents the available options to the user.

### 🍽️ Food Browsing

After selecting a hotel, users can browse available:

* Starters
* Main courses
* Desserts
* Beverages

Each food item is displayed along with its price.

### 🛒 Shopping Cart

The cart module allows users to:

* Add food items
* Remove food items
* View selected items
* Calculate the total bill

### ⭐ Food Recommendations

The system maintains previously sold items in `sold.csv`.

It calculates the frequency of food items and recommends the **top five popular items** to users.

### 💾 File-Based Data Management

The application uses files for persistent storage:

| File        | Purpose                                          |
| ----------- | ------------------------------------------------ |
| `users.dat` | Stores user credentials                          |
| `var1.dat`  | Stores hotel and food information                |
| `sold.csv`  | Stores sold-item information for recommendations |

---

## 🧠 Algorithms Used

### 1. Haversine Formula

The Haversine formula calculates the geographical distance between two points using their latitude and longitude.

In this project, it is used to:

* Calculate the distance between users and hotels
* Identify nearby hotels
* Sort hotels according to proximity
* Support location-based recommendations

Conceptually:

```text
User Location
      │
      ▼
Latitude + Longitude
      │
      ▼
Haversine Distance Calculation
      │
      ▼
Distance from Each Hotel
      │
      ▼
Sort Hotels
      │
      ▼
Display Nearby Hotels
```

### 2. Binary Insertion Sort

Binary insertion sort is used as part of the sorting approach for organizing data efficiently.

The algorithm uses binary search to identify the appropriate insertion position before inserting a new element into an already sorted sequence.

The project report identifies **Haversine Formula** and **Binary Insertion Sort** as the major algorithms explored for the system.

---

## 🏗️ System Workflow

```text
                 ┌─────────────────────┐
                 │       User          │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │  Login / Register   │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ User Preferences &  │
                 │ Location Input      │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Hotel Data          │
                 │ Retrieval           │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Haversine Distance  │
                 │ Calculation         │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Hotel Sorting &     │
                 │ Filtering           │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Select Hotel        │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Browse Food Items   │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Add / Remove Cart   │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Calculate Bill      │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Store Order Data    │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │ Popular Food        │
                 │ Recommendations     │
                 └─────────────────────┘
```

---

## 🖥️ Application Modules

### User Module

Handles the customer-facing functionality:

* Registration
* Login
* Preference selection
* Location input
* Hotel discovery
* Food browsing
* Cart management
* Bill calculation
* Recommendations

### Admin Module

The admin component is responsible for managing hotel and food information.

The implementation uses structured data and binary file storage to maintain hotel records and food information.

---

## 🛠️ Tech Stack

| Category             | Technology                               |
| -------------------- | ---------------------------------------- |
| Programming Language | **C**                                    |
| GUI Framework        | **GTK+**                                 |
| Data Storage         | Binary Files / CSV                       |
| Algorithms           | Haversine Formula, Binary Insertion Sort |
| Data Structures      | C Structures, Arrays                     |
| Development Focus    | Food Ordering & Recommendation System    |

---

## 📂 Data Structures

The application uses C structures to organize its data.

Important structures include:

* `User`
* `Distance`
* `Starter`
* `Main Course`
* `Dessert`
* `Beverage`
* `Food`
* `Hotel`
* `Cart`
* `Cart Item`
* `Frequent Item`

These structures allow the application to organize users, hotels, food items, carts, orders, and recommendation data.

The report specifically describes these structures as the core data organization mechanism of the application.

---

## 🖼️ GUI

The application uses **GTK+** to provide a multi-page graphical interface.

The GUI includes pages for:

* Preferences
* Distance-based hotel sorting
* Discount-based sorting
* Food items
* Cart management
* Recommendations

GTK components used include:

```text
GtkNotebook
GtkEntry
GtkTextView
GtkButton
```

These components provide navigation, input fields, data display, and user interaction throughout the application.

---

## 🔄 Application Flow

```text
Register / Login
       ↓
Set Preferences
       ↓
Enter Location
       ↓
Find Hotels
       ↓
Calculate Distance
       ↓
Sort / Filter Hotels
       ↓
Select Hotel
       ↓
Browse Food
       ↓
Add Items to Cart
       ↓
Manage Cart
       ↓
Calculate Bill
       ↓
Store Order
       ↓
Generate Popular Food Recommendations
```

---

## 🚀 Getting Started

### Prerequisites

Make sure your system has:

* A C compiler such as GCC
* GTK+ development libraries
* `pkg-config`
* Linux or another environment configured for GTK+ development

### Clone the Repository

```bash
git clone https://github.com/<your-username>/<your-repository>.git
cd <your-repository>
```

### Build

The exact compilation command depends on the source-file structure of the repository and the installed GTK version.

For GTK-based C projects, compilation generally requires linking the GTK libraries through `pkg-config`.

Example pattern:

```bash
gcc <source-files>.c -o food-ordering $(pkg-config --cflags --libs gtk+-3.0)
```

> **Note:** Replace `<source-files>.c` with the actual source files in the repository.

### Run

```bash
./food-ordering
```

Before running the application, make sure the required data files such as `users.dat`, `var1.dat`, and `sold.csv` are available in the expected project directory.

---

## 📁 Suggested Repository Structure

```text
Food-Ordering-System/
│
├── src/
│   ├── main.c
│   ├── ...
│
├── data/
│   ├── users.dat
│   ├── var1.dat
│   └── sold.csv
│
├── screenshots/
│   ├── login.png
│   ├── hotels.png
│   ├── food-items.png
│   ├── cart.png
│   └── recommendations.png
│
├── docs/
│   └── project-report.pdf
│
├── .gitignore
└── README.md
```

> Adjust the structure to match the actual files in your repository rather than restructuring the project solely for the README.

---

## 🧪 Testing

The project report includes validation through test cases covering different application scenarios.

Testing focuses on areas such as:

* User authentication
* Input handling
* Hotel selection
* Distance calculation
* Sorting
* Food selection
* Cart operations
* Bill calculation
* Recommendation functionality

The implementation also incorporates input validation and error handling as part of the application workflow.

---

## ⚠️ Current Limitations

The current implementation has several limitations:

* The login interface is command-line based while the main application uses GTK+, resulting in an inconsistent interface.
* There is no logout or user-switching functionality.
* Multiple languages/locales are not supported.
* Payment functionality is limited to cash on delivery.
* Restaurant owners cannot directly manage their information.
* Real-time order status tracking is not implemented.

These limitations are documented in the submitted project report.

---

## 🔮 Future Enhancements

Potential improvements include:

* 🌐 Full web or mobile version
* 🔐 Improved authentication and session management
* 🚪 Logout and account switching
* 💳 Multiple payment methods
* 📦 Real-time order tracking
* 🏪 Restaurant-owner dashboard
* 🌍 Multi-language and localization support
* 🗺️ Interactive map integration
* 🤖 More advanced personalized recommendations
* 🔒 Improved security and data protection
* 📊 Restaurant and order analytics

---

## 🎯 Learning Outcomes

This project provided practical experience in:

* C programming
* Structures and arrays
* File handling
* GUI development using GTK+
* User authentication
* Sorting algorithms
* Geographical distance calculation
* Data organization
* Input validation
* Modular application development
* Building a complete software application from requirements to implementation

The project report specifically highlights learning in C file handling, arrays of structures, input validation, error handling, and integrating modules into a full application.

---

## 👥 Project Team

**Sri Sivasubramaniya Nadar College of Engineering**

Department of Computer Science and Engineering

| Member             | Role      |
| ------------------ | --------- |
| **Vishnu Kumar S** | Developer |
| **Vigneshwar K**   | Developer |
| **Tharun Kumar S** | Developer |

---

## 📚 Project Information

**Course:** UCS2265 – Fundamentals and Practice of Software Development
**Institution:** Sri Sivasubramaniya Nadar College of Engineering
**Department:** Computer Science and Engineering
**Project Type:** Academic Software Development Project
**Year:** 2023–2024

---

## 📄 Documentation

The complete academic project report contains the system's:

* Problem statement
* Algorithm analysis
* Data Flow Diagrams
* Architecture
* Module descriptions
* Implementation details
* Test cases
* Limitations
* Social, legal, environmental and ethical considerations
* Learning outcomes

---

## ⭐ If You Found This Project Useful

If this project helped you understand C, GTK+, file handling, sorting algorithms, or location-based food recommendation systems, consider giving the repository a ⭐.

---

## 📜 License

This project was developed as an academic project for educational purposes.
