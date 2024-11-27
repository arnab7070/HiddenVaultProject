#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <direct.h>   // For folder creation
#include <windows.h>  // For hiding/unhiding folder
#include <conio.h>    // For masked password input
#include <functional> // For std::hash

const std::string PASSWORD_FILE = "HiddenVault\\vault_password_hash.txt";

// Simple password hash using std::hash
std::size_t hashPassword(const std::string &password)
{
    std::hash<std::string> hash_fn;
    return hash_fn(password);
}

void createVault(const std::string &vaultPath)
{
    if (_mkdir(vaultPath.c_str()) == 0)
    {
        std::cout << "Vault created at: " << vaultPath << std::endl;
        SetFileAttributes(vaultPath.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    }
    else
    {
        std::cout << "Vault already exists!" << std::endl;
    }
}

void lockVault(const std::string &vaultPath)
{
    SetFileAttributes(vaultPath.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    std::cout << "Vault locked and hidden.\n";
}

void unlockVault(const std::string &vaultPath)
{
    SetFileAttributes(vaultPath.c_str(), FILE_ATTRIBUTE_SYSTEM);
    std::cout << "Vault unlocked! You can access it at: " << vaultPath << std::endl;
}

std::string getPasswordInput(const std::string &prompt)
{
    std::string password;
    char ch;
    std::cout << prompt;
    while (true)
    {
        ch = _getch(); // Get character without echoing to console
        if (ch == '\r')
            break; // Enter key pressed
        password.push_back(ch);
        std::cout << '*'; // Display '*' for each entered character
    }
    std::cout << std::endl;
    return password;
}

std::size_t readPasswordHashFromFile()
{
    std::ifstream file(PASSWORD_FILE);
    if (!file.is_open())
        return 0; // Return 0 if file doesn't exist
    std::size_t passwordHash;
    file >> passwordHash;
    file.close();
    return passwordHash;
}

void savePasswordHashToFile(std::size_t passwordHash)
{
    std::ofstream file(PASSWORD_FILE);
    if (file.is_open())
    {
        file << passwordHash;
        file.close();
        // Hide the password hash file after saving it
        SetFileAttributes(PASSWORD_FILE.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
        std::cout << "Password hash saved successfully.\n";
    }
    else
    {
        std::cout << "Error saving password hash.\n";
    }
}

bool verifyPassword(std::size_t correctPasswordHash)
{
    std::string enteredPassword = getPasswordInput("Enter Password: ");
    std::size_t enteredPasswordHash = hashPassword(enteredPassword);
    return enteredPasswordHash == correctPasswordHash;
}

std::string getCurrentDirectory()
{
    char buffer[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, buffer);
    return std::string(buffer);
}

int main()
{
    const std::string currentDir = getCurrentDirectory();
    const std::string vaultPath = currentDir + "\\HiddenVault";

    // Create the vault folder
    createVault(vaultPath);

    // Check if password file exists inside the vault
    std::size_t savedPasswordHash = readPasswordHashFromFile();
    if (savedPasswordHash == 0)
    {
        std::cout << "No password set. Please create a new password.\n";
        std::string newPassword = getPasswordInput("Enter New Password: ");
        std::size_t newPasswordHash = hashPassword(newPassword);
        savePasswordHashToFile(newPasswordHash);
        savedPasswordHash = newPasswordHash;
    }

    int choice;
    while (true)
    {
        std::cout << "\nVault Menu:\n";
        std::cout << "1. Unlock Vault\n";
        std::cout << "2. Lock Vault\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1: // Unlock Vault
            if (verifyPassword(savedPasswordHash))
            {
                unlockVault(vaultPath);
                return 0;
            }
            else
            {
                std::cout << "Incorrect Password!\n";
            }
            break;

        case 2: // Lock Vault
            lockVault(vaultPath);
            return 0;

        case 3: // Exit
            std::cout << "Exiting...\n";
            return 0;

        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
