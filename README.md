# fast_chat

fast_chat is a simple modular chat server implemented in C++20. It features user registration, authentication and chat room management. The project is organized into two main components:

- **domain**: Core chat logic, user and room management.
- **http-api**: HTTP API integration.

## Features

- User registration and authentication
- Password hashing with SHA-512 (libsodium)
- Chat room creation and user management
- Modular codebase for easy extension

## Prerequisites

- C++20 compatible compiler (e.g., g++ 10+)
- CMake 3.19+
- [Boost](https://www.boost.org/) (system, thread, json)
- [libsodium](https://libsodium.gitbook.io/doc/)
- [vcpkg](https://github.com/microsoft/vcpkg) (recommended for dependency management)

## Building

1. **Install dependencies** (recommended via vcpkg):

    ```sh
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ./vcpkg install boost-system boost-thread boost-json libsodium
    ```

2. **Configure the project** (from the project root directory):

    ```sh
    cmake --preset with-vcpkg
    ```

3. **Build the project**:

    ```sh
    cmake --build build
    ```

4. **Run the server**:

    ```sh
    ./build/http-api/http_api
    ```

## Project Structure

- `domain/` - Core chat logic and data structures
- `http-api/` - Main application and API integration
- `.vscode/` - Editor configuration for VS Code
- `CMakeLists.txt` - Top-level build configuration

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.