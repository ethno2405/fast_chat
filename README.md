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

- C++20 compatible compiler (e.g., g++ 10+ for Linux, MSVC for Windows)
- CMake 3.19+
- [vcpkg](https://github.com/microsoft/vcpkg)

## Building

This project uses CMake presets for simplified configuration and building. The available presets are defined in `CMakePresets.json`:

- **with-vcpkg**: Uses the "Unix Makefiles" generator and the vcpkg toolchain for Linux and macOS.
- **with-vcpkg-win**: Uses the "Visual Studio 17 2022" generator and the vcpkg toolchain for Windows.

### Linux

1. **Install vcpkg**:

    ```sh
    git clone git@github.com:microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.sh
    ```

2. **Configure the project**:

    ```sh
    cmake --preset=(linux|win)-x64-(debug|release)
    # cmake --preset=linux-x64-debug
    # cmake --preset=win-x64-release
    ```

3. **Build the project**:

    ```sh
    cmake --build build --preset (linux|win)-x64-(debug|release)
    # cmake --build build --preset linux-x64-debug
    # cmake --build build --preset win-x64-release
    ```

4. **Run the server**:

    ```sh
    ./build/(Debug|Release)/http_api
    # ./build/Debug/http_api
    # ./build/Release/http_api
    ```

### Windows (Visual Studio 2022)

Visual Studio 2022 supports `vcpkg` manifest mode, so you can open the project directory directly. `File > Open > CMake > CMakeLists.txt`. 
The `vcpkg.json` file will be automatically detected.


## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.