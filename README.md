# Bank Management System

## Overview
This Bank Management System is a C-based program that provides basic banking functionalities such as account creation, login, and transactions. User data is securely stored in a file, ensuring persistence across sessions.

## Features
1. **Account Creation**:
   - Create a new account by providing your name and age.
   - Eligibility: Age must be between 18 and 70.
   - Accounts are created with a zero balance.

2. **Account Login**:
   - Log in by entering your registered name.
   - Case-insensitive name matching ensures ease of access.

3. **Banking Operations**:
   - **Add Money**: Add funds to your account using a credit card.
   - **Transfer Money**: Transfer funds to another registered account securely.

4. **Data Persistence**:
   - User data is stored in a file (`names.txt`) in the format:
     ```
     name balance
     ```
   - Transactions update the file in real-time using a temporary file (`temp.txt`).

5. **Error Handling**:
   - Handles invalid inputs and ensures robust execution.
   - Prevents transactions with insufficient funds or invalid recipients.

## How It Works
### Account Creation
- Input your full name and age.
- If eligible, your account is created with a zero balance and stored in `names.txt`.

### Account Login
- Log in by providing your registered name.
- Once authenticated, you can:
  1. Add money to your account.
  2. Transfer money to another account.

### File Handling
- User data is stored persistently in `names.txt`.
- A temporary file (`temp.txt`) is used for updating balances during transactions to ensure data integrity.

## Setup Instructions
1. **Compilation**:
   - Compile the program using a C compiler (e.g., GCC):
     ```bash
     gcc -o bank_management bank_management.c
     ```
2. **Execution**:
   - Run the compiled program:
     ```bash
     ./bank_management
     ```
3. **Dependencies**:
   - Ensure `names.txt` exists in the working directory. If not, the program will create it automatically.

## Usage
1. Run the program.
2. Follow on-screen prompts to create an account, log in, or perform transactions.
3. Exit the portal when done.

## Example
### Sample `names.txt` File
```
john_doe 500.00
jane_smith 300.00
```
### Sample Execution
```
Are you an existing user?
1: Yes 0: No
> 0
Do you want to create an account?
1: Yes 0: No
> 1
Enter your full name: John Doe
Enter your age: 30
Account created successfully for John Doe with balance: 0.00
```

## Contributing
Feel free to contribute by forking this repository and submitting pull requests.

## License
This project is open-source and available under the MIT License.

## Contact
For inquiries or feedback, please reach out to [your-email@example.com].

