## **Project: HiddenVault**

### **Overview**

HiddenVault is a C++ project designed to create a password-protected folder, "HiddenVault," where users can securely store files. The folder is hidden and protected, and it includes the following features:

- Password protection with hashed password storage.
- System and hidden folder attributes to make it less accessible.
- Ability to lock and unlock the vault securely.
- Customizable folder icons (via `desktop.ini`).

### Watch the demo video
[![Click Here](https://i.ytimg.com/vi/mSnWiCBWjX0/maxresdefault.jpg)](https://www.youtube.com/watch?v=mSnWiCBWjX0)
---

### **Features**

1. **Password Protection**: Users can set a password upon first run, which is securely stored as a hash in a hidden file.
2. **Folder Locking and Unlocking**:
   - Locked: The folder is hidden and marked as a system folder.
   - Unlocked: The folder is visible with its contents.
3. **Custom Folder Icon**: Uses a `desktop.ini` file to set a custom icon for the folder.
4. **Hidden Password File**: Stores the hashed password in a hidden system file (`vault_password_hash.txt`) inside the vault.

---

### **Setup**

#### **Requirements**

- Windows OS
- C++ Compiler (e.g., GCC/MinGW, Visual Studio)

#### **Compilation Instructions**

1. Open a terminal or command prompt.
2. Use the following command to compile the source code:

   ```bash
   g++ vault.cpp -o HiddenVault.exe
   ```

3. Place the executable (`HiddenVault.exe`) in the folder where you want to manage the vault.

4. To change the logo (or icon) of an .exe file, you would need to embed an icon resource into the executable. This requires the use of a resource file (.rc file) that contains the icon, and then linking this resource when compiling the program.

Create a new file called resources.rc in your project directory. The contents of the .rc file will look like this:

```cpp
#include <windows.h>
IDR_MAINFRAME ICON DISCARDABLE "logo.ico"
```

---

Assuming you are using g++ (MinGW) to compile your C++ code, here’s how to link the resource file:

```
windres resources.rc -o resources.o
g++ vault.cpp resources.o -o vault
```

---

### **Usage Instructions**

1. **Run the Program**:
   Execute `HiddenVault.exe` in the directory of your choice. It will create a hidden folder named `HiddenVault`.

2. **Set Password**:
   On the first run, you’ll be prompted to set a password. This password is hashed and stored securely.

3. **Vault Menu**:

   - **1. Unlock Vault**: Enter your password to make the vault accessible.
   - **2. Lock Vault**: Hide and secure the vault again.
   - **3. Exit**: Close the program.

4. **Icon Customization**:
   - Replace `vault_icon.ico` inside the `HiddenVault` folder with a custom `.ico` file.
   - The folder automatically uses this icon upon unlocking.

---

### **Technical Details**

#### **Core Functionalities**

- **Password Handling**:
  - The password is hashed using `std::hash` and stored in `vault_password_hash.txt`.
  - The password file is hidden and marked as a system file.
- **Folder Locking/Unlocking**:
  - Uses Windows API (`SetFileAttributes`) to set `FILE_ATTRIBUTE_HIDDEN` and `FILE_ATTRIBUTE_SYSTEM` attributes for the folder and its associated files.
- **Custom Icon**:
  - Automatically creates `desktop.ini` to set a custom icon for the folder.
  - Both `desktop.ini` and the `.ico` file are hidden and protected.

#### **File Structure**

- **HiddenVault/** (created by the program)
  - `vault_password_hash.txt` (hidden system file)
  - `desktop.ini` (hidden system file for icon configuration)
  - `vault_icon.ico` (hidden icon file, customizable)

---

### **Important Notes**

1. **Security**:
   - The password is hashed but not encrypted. While secure for basic use, this is not recommended for highly sensitive data.
2. **Folder Visibility**:
   - The folder is hidden and system-protected but can still be accessed if exact paths are known.
3. **Customization**:
   - Replace `vault_icon.ico` with any valid `.ico` file to customize the folder's icon.
4. **Data Loss**:
   - If `vault_password_hash.txt` is deleted, you will lose access to the vault. There is no password recovery mechanism.

---

### **Known Limitations**

1. **Compatibility**:
   - This program is designed for Windows and uses Windows-specific APIs.
2. **Security Limitations**:
   - `std::hash` is used for password hashing, which is not cryptographically secure. Consider upgrading to a secure hashing library like OpenSSL or bcrypt for enhanced security.

---

### **Basic Concept of Hiding a Folder**
To hide a folder in a pendrive, first make sure to enter in the pendrive integrated CMD. Then, use these commands: E:\>attrib Hidden +H for hidden only, or E:\>attrib Hidden +S +H for hidden and system. To un-hide the folder, use E:\>attrib Hidden -S -H to remove both system and hidden where Hidden is folder name.

### **Contributors**

- **Arnab Nandi**

Feel free to contribute to the project by enhancing its features or addressing its limitations.

---
