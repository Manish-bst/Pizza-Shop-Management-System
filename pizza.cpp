#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Define a struct for pizza
struct Pizza {
    string name;
    double smallPrice;
    double mediumPrice;
    double largePrice;
};

// Define a struct for side dish
struct SideDish {
    string name;
    double price;
};

// Define a struct for soft drink
struct SoftDrink {
    string name;
    double price;
};

// Function to display pizzas
void displayPizzas(const Pizza menu[], int pizzaSize) {
    cout << "Pizzas:\n";
    for (int i = 0; i < pizzaSize; ++i) {
        cout << i+1 << ". " << menu[i].name << " - Small: " << menu[i].smallPrice << " INR, Medium: " << menu[i].mediumPrice << " INR, Large: " << menu[i].largePrice << " INR\n";
    }
}

// Function to display side dishes
void displaySideDishes(const SideDish sides[], int sideSize) {
    cout << "Side Dishes:\n";
    for (int i = 0; i < sideSize; ++i) {
        cout << i+1 << ". " << sides[i].name << " - " << sides[i].price << " INR\n";
    }
}

// Function to display soft drinks
void displaySoftDrinks(const SoftDrink drinks[], int drinkSize) {
    cout << "Soft Drinks:\n";
    for (int i = 0; i < drinkSize; ++i) {
        cout << i+1 << ". " << drinks[i].name << " - " << drinks[i].price << " INR\n";
    }
}

// Function to display order summary
void displayOrderSummary(int totalQuantity, double totalPrice) {
    cout << "Your order summary:\n";
    cout << "Total items: " << totalQuantity << endl;
    cout << "Total price (INR): " << totalPrice << endl;
}

// Function to write order details to a file
void writeOrderToFile(ofstream& file, const string& itemName, int quantity, double price) {
    file << itemName << "," << quantity << "," << price << endl;
}

// Function to take order
void takeOrder(const Pizza menu[], int pizzaSize, const SideDish sides[], int sideSize, const SoftDrink drinks[], int drinkSize) {
    // Variables to store order details
    int totalQuantity = 0;
    double totalPrice = 0;
    double price = 0;

    // Open a file to write orders
    ofstream outFile("orders.txt");
    if (!outFile) {
        cerr << "Error opening file." << endl;
        return;
    }

    // Loop to allow multiple item selections
    char continueOrder;
    do {
        // Display options for the customer to choose from
        cout << "Please select a category:\n";
        cout << "1. Pizza\n";
        cout << "2. Side Dishes\n";
        cout << "3. Soft Drinks\n";
        cout << "Enter your choice: ";

        int categoryChoice;
        cin >> categoryChoice;

        switch (categoryChoice) {
            case 1:
                // Order Pizza
                cout << "You selected Pizza.\n";
                displayPizzas(menu, pizzaSize);

                // Ask for user selection within the chosen category
                cout << "Enter the number corresponding to the pizza you want to order (or 0 to exit):\n";
                int pizzaChoice;
                cin >> pizzaChoice;

                // Exit loop if the user chooses to exit
                if (pizzaChoice == 0)
                    break;

                // Validate choice
                if (pizzaChoice < 1 || pizzaChoice > pizzaSize) {
                    cout << "Invalid choice. Please try again.\n";
                    continue;
                }

                // Ask for quantity
                int quantity;
                cout << "Enter quantity: ";
                cin >> quantity;

                // Update total quantity
                totalQuantity += quantity;

                // Ask for size
                cout << "Select pizza size:\n";
                cout << "1. Small\n";
                cout << "2. Medium\n";
                cout << "3. Large\n";
                cout << "Enter your choice: ";
                int sizeChoice;
                cin >> sizeChoice;

                // Validate size choice
                if (sizeChoice < 1 || sizeChoice > 3) {
                    cout << "Invalid size choice. Please try again.\n";
                    continue;
                }

                // Calculate price based on the selected item and size
                switch (sizeChoice) {
                    case 1:
                        price = menu[pizzaChoice - 1].smallPrice * quantity;
                        break;
                    case 2:
                        price = menu[pizzaChoice - 1].mediumPrice * quantity;
                        break;
                    case 3:
                        price = menu[pizzaChoice - 1].largePrice * quantity;
                        break;
                }

                // Write order details to file
                writeOrderToFile(outFile, menu[pizzaChoice - 1].name, quantity, price);

                // Update total price
                totalPrice += price;
                break;

            case 2:
                // Order Side Dishes
                cout << "You selected Side Dishes.\n";
                displaySideDishes(sides, sideSize);

                // Ask for user selection within the chosen category
                cout << "Enter the number corresponding to the side dish you want to order (or 0 to exit):\n";
                int sideChoice;
                cin >> sideChoice;

                // Exit loop if the user chooses to exit
                if (sideChoice == 0)
                    break;

                // Validate choice
                if (sideChoice < 1 || sideChoice > sideSize) {
                    cout << "Invalid choice. Please try again.\n";
                    continue;
                }

                // Ask for quantity
                int sideQuantity;
                cout << "Enter quantity: ";
                cin >> sideQuantity;

                // Update total quantity
                totalQuantity += sideQuantity;

                // Calculate price based on the selected item and quantity
                price = sides[sideChoice - 1].price * sideQuantity;

                // Write order details to file
                writeOrderToFile(outFile, sides[sideChoice - 1].name, sideQuantity, price);

                // Update total price
                totalPrice += price;
                break;

            case 3:
                // Order Soft Drinks
                cout << "You selected Soft Drinks.\n";
                displaySoftDrinks(drinks, drinkSize);

                // Ask for user selection within the chosen category
                cout << "Enter the number corresponding to the soft drink you want to order (or 0 to exit):\n";
                int drinkChoice;
                cin >> drinkChoice;

                // Exit loop if the user chooses to exit
                if (drinkChoice == 0)
                    break;

                // Validate choice
                if (drinkChoice < 1 || drinkChoice > drinkSize) {
                    cout << "Invalid choice. Please try again.\n";
                    continue;
                }
             int drinkQuantity;
                cout << "Enter quantity: ";
                cin >> drinkQuantity;
                // Update total quantity
                totalQuantity += drinkQuantity;

                // Calculate price based on the selected item and quantity
                price = drinks[drinkChoice - 1].price * drinkQuantity;
                
                writeOrderToFile(outFile, drinks[drinkChoice - 1].name, drinkQuantity, price);

                // Update total price
                totalPrice += price;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                continue; // Continue to next iteration if choice is invalid
        }

        // Display order summary after each item is ordered
        displayOrderSummary(totalQuantity, totalPrice);
        // Ask if the customer wants to continue ordering
        cout << "Do you want to order anything else? (y/n): ";
        cin >> continueOrder;
    } while (continueOrder == 'y' || continueOrder == 'Y');
}
int main() {
    const int MAX_MENU_SIZE = 10;
    const int MAX_SIDE_SIZE = 5;
    const int MAX_DRINK_SIZE = 9;
    Pizza menu[MAX_MENU_SIZE] = {{"Margherita", 200, 250, 300}, {"Farmhouse", 250, 300, 350}, {"Peppy Paneer", 220, 270, 320}, {"Mexican Green Wave", 300, 350, 400}, {"Deluxe Veggie", 270, 320, 370}, {"Veg Extravaganza", 320, 370, 420}, {"Cheese n Corn", 240, 290, 340}, {"Paneer Makhani", 280, 330, 380}, {"Veggie Paradise", 260, 310, 360}, {"Indi Tandoori Paneer", 310, 360, 410}};
    SideDish sides[MAX_SIDE_SIZE] = {{"French Fries", 100}, {"Garlic Bread", 120}, {"Potato Wedges", 90}, {"Onion Rings", 110}, {"Mozzarella Sticks", 130}};
    SoftDrink drinks[MAX_DRINK_SIZE] = {{"Coke", 40}, {"Diet Coke", 45}, {"Fanta", 35}, {"Sprite", 35}, {"Thums Up", 40}, {"Pepsi", 40}, {"Pepsi Black", 45}, {"Limca", 35}, {"Mountain Dew", 40}};
    int pizzaSize = 10;
    int sideSize = 5;
    int drinkSize = 9;

    // Take order
    takeOrder(menu, pizzaSize, sides, sideSize, drinks, drinkSize);

    return 0;
}