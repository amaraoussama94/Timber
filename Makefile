# === CONFIGURATION ===
# Sets the name of your final executable
PROJECT_NAME = Zombie_Shooter
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# SFML submodule and build paths
SFML_DIR = external/SFML
SFML_BUILD_DIR = $(SFML_DIR)/build
SFML_INSTALL_DIR = $(SFML_DIR)/install

#SFML_INSTALL_DIR = $(SFML_DIR)/install

# Compiler configuration
CXX = g++

# Compiler flags
# -std=c++17: use C++17 standard
# -Wall: enable all warnings
# -I...: include SFML and project headers
CXXFLAGS = -std=c++17 -Wall -I$(SFML_INSTALL_DIR)/include -I$(INC_DIR)

# Linker flags
LDFLAGS = -L$(SFML_INSTALL_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Finds all .cpp files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
# Maps each .cpp file to a corresponding .o file in build/
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))
#	CMake flags
CMAKE_FLAGS += --no-warn-unused-cli
CMAKE_FLAGS += -DCMAKE_SH="/usr/bin/bash"


# === OS DETECTION ===
# === OS DETECTION ===
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	EXE = $(BIN_DIR)/$(PROJECT_NAME)
	COPY_DLLS = @true
	CMAKE_GENERATOR = -G "Unix Makefiles"
	CMAKE_ENV =
	MAKE_PROGRAM := $(shell which make)
else ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	EXE = $(BIN_DIR)/$(PROJECT_NAME).exe
	COPY_DLLS = cp -u $(SFML_INSTALL_DIR)/bin/*.dll $(BIN_DIR) 2>/dev/null || true
	CMAKE_GENERATOR = -G "MinGW Makefiles"
else ifeq ($(findstring MSYS,$(UNAME_S)),MSYS)
	EXE = $(BIN_DIR)/$(PROJECT_NAME).exe
	COPY_DLLS = cp $(SFML_INSTALL_DIR)/bin/*.dll $(BIN_DIR) 2>/dev/null || true
	CMAKE_GENERATOR = -G "Unix Makefiles"
else
	$(error Unsupported platform: $(UNAME_S))
endif

# === UNIVERSAL FONT COPY ===
# This copies all font files from your `fonts/` directory into `bin/` regardless of OS.
COPY_FONTS = cp -r fonts/* $(BIN_DIR) 2>/dev/null || true

# === COMPILER AND MAKE PROGRAMS ===
# This section sets the C++ compiler, C compiler, and make program based on the detected OS.
# It ensures the correct tools are used for building the project, especially on Windows with MinGW
ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	CXX := $(shell which g++)
	CC := $(shell which gcc)
	MAKE_PROGRAM := $(shell which mingw32-make)
	CMAKE_ENV = CMAKE_POLICY_VERSION_MINIMUM=3.5 CC=$(CC) CXX=$(CXX) CMAKE_MAKE_PROGRAM=$(MAKE_PROGRAM) SHELL=/usr/bin/bash
endif

# === ENVIRONMENT CHECK ===
# This target prints environment variables and compiler settings for debugging.
# It helps verify that the Makefile is using the correct tools and paths.
check-env:
	@echo "UNAME_S = $(UNAME_S)"
	@echo "MSYSTEM = $(shell echo $$MSYSTEM)"
	@echo "CXX = $(CXX)"
	@echo "CC = $(CC)"
	@echo "PATH = $$PATH"


# === DEBUG PATHS ===
# This target checks if the SFML graphics library file exists in the expected location.	
debug-paths:
	@echo "SFML_GRAPHICS_LIB = $(SFML_GRAPHICS_LIB)"
	@echo "Checking if file exists:"
	@test -f $(SFML_GRAPHICS_LIB) && echo "Found" || echo "Missing"

# === TARGETS ===
# The default target. It builds SFML first, then your game.
# Updated to trigger SFML build based on the presence of either static or shared libraries.
ifeq ($(UNAME_S),Linux)
SFML_GRAPHICS_LIB = $(SFML_INSTALL_DIR)/lib/libsfml-graphics.a
else
SFML_GRAPHICS_LIB = $(SFML_INSTALL_DIR)/bin/sfml-graphics-3.dll
SFML_AUDIO_LIB     = $(SFML_INSTALL_DIR)/bin/sfml-audio-3.dll
endif

all: check-shell $(SFML_GRAPHICS_LIB) $(SFML_AUDIO_LIB) $(EXE)

# === Build and Install SFML from Source ===
# This rule ensures SFML is built and installed before compiling the game.
# It triggers when either the static or shared graphics library is missing from the install directory.
# 
# Steps:
# 1. Creates the SFML build directory if it doesn't exist.
# 2. Runs CMake to configure the SFML project:
#    - Uses the appropriate generator (e.g. "MinGW Makefiles" on Windows).
#    - Sets the install prefix to SFML_INSTALL_DIR to isolate headers/libs/DLLs.
#    - Enables shared library builds for dynamic linking.
#    - Explicitly sets compiler and make program on Windows to avoid CMake errors.
# 3. Builds SFML using make.
# 4. Installs the built libraries, headers, and DLLs into SFML_INSTALL_DIR.
#
# This setup ensures your project uses a clean, portable, and compiler-compatible SFML build.

$(SFML_INSTALL_DIR)/lib/libsfml-graphics.a $(SFML_INSTALL_DIR)/bin/sfml-graphics-3.dll   $(SFML_INSTALL_DIR)/bin/sfml-audio-3.dll:
	@echo "Building SFML in $(SFML_BUILD_DIR)..."
	mkdir -p $(SFML_BUILD_DIR)
	cd $(SFML_BUILD_DIR) && $(CMAKE_ENV) cmake .. $(CMAKE_GENERATOR) $(CMAKE_FLAGS) \
		-DCMAKE_INSTALL_PREFIX="$(abspath $(SFML_INSTALL_DIR))" \
 	-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_SHARED_LIBS=TRUE \
		-DSFML_USE_SYSTEM_FREETYPE=TRUE \
		$(CMAKE_FLAGS) 
	$(MAKE_PROGRAM) -C $(SFML_BUILD_DIR)
	$(MAKE_PROGRAM) -C $(SFML_BUILD_DIR) install
	@echo "Contents of SFML install directory:"
	@sh -c "if [ \"$(UNAME_S)\" = \"Linux\" ]; then \
		ls -l $(SFML_INSTALL_DIR)/lib || echo 'No .so files found'; \
	else \
		ls -l $(SFML_INSTALL_DIR)/bin || echo 'No DLLs found'; \
	fi"

check-shell:
ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
	@if [ "$$MSYSTEM" != "MINGW64" ]; then \
 		echo "Please run this Makefile from the MSYS2 MinGW64 shell (not cmd.exe or PowerShell)"; \
			exit 1; \
	fi
endif



# Compiles each .cpp file into a .o object file
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Links all object files into the final executable
$(EXE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Executable built at: $(EXE)"
	@ls -l $(EXE) || echo "Executable not found"
	@echo "DLLS path: $(COPY_DLLS)"
	$(COPY_DLLS)
	@echo "Copying fonts..."
	$(COPY_FONTS)
	@echo "Contents of bin directory after copying DLLs:"
	@ls -l $(BIN_DIR)

# Deletes your object files and final binary
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Also deletes the SFML build and install directories
clean-all: clean
	rm -rf $(SFML_BUILD_DIR) $(SFML_INSTALL_DIR)
# === Run the game after building ===
run: all
	@echo "Launching $(EXE)..."
	@$(EXE)
.PHONY: all clean clean-all