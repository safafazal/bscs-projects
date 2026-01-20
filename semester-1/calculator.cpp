#include <iostream>
using namespace std;

int main()
{
    int choice;
    float num1, num2;

    while (true)
    {
        cout << "\n------ SIMPLE CALCULATOR ------\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5)
        {
            cout << "Program Exit Successfully.\n";
            break;
        }

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter second number: ";
        cin >> num2;

        switch (choice)
        {
            case 1:
                cout << "Result = " << num1 + num2 << endl;
                break;

            case 2:
                cout << "Result = " << num1 - num2 << endl;
                break;

            case 3:
                cout << "Result = " << num1 * num2 << endl;
                break;

            case 4:
                if (num2 != 0)
                    cout << "Result = " << num1 / num2 << endl;
                else
                    cout << "Error: Division by zero not allowed\n";
                break;

            default:
                cout << "Invalid Choice! Try again.\n";
        }
    }

    return 0;
}
