### ACHTUNG: um rekursive Aufrufe zu vermeiden, muss man
###          entweder in VSCode diese cmake-Steuerungsdatei konfigurieren
###          oder in der Kommandozeile - falls CMAKE_CXX_COMPILER nicht
###          den Standardwert "c++" hat - das Tool "cmake" aufrufen
###          mit dem Variablenwert ${CMAKE_CXX_COMPILER}, z.B. 
###            cmake -DCMAKE_CXX_COMPILER=/usr/local/bin/g++-11 ..

cmake_minimum_required(VERSION 3.20)
# Projektname und Version
project(Mandelbrot VERSION 1.0)

# C++ Standard
set(CMAKE_VERBOSE_MAKEFILE ON)

# Voreinstellung des C++-Compilers:
# set(CMAKE_CXX_COMPILER /usr/bin/g++-12)
# set(CMAKE_CXX_COMPILER g++-12)
# set(CMAKE_CXX_COMPILER /usr/local/bin/g++-11)

# zusaetzliche, sinnvolle GCC-Optionen
# 
add_compile_options(-pedantic -Wall -Wextra -Winline -Wmain )
# add_compile_options(-pedantic -Wall -Wextra -Winline -Wmain -fanalyzer)

# fuer GCC: Option "-std=c++23" wird dadurch gewaehlt ...
### set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD 20)
# ... zusammen mit dieser Einstellung, die die GCC-Erweiterungen
#     (mit der Option "-std=gnu++23" bzw. "-std=gnu++2a") verbietet!
set(CMAKE_CXX_STANDARD_REQUIRED ON)
### zusaetzlich:
set(CMAKE_CXX_EXTENSIONS OFF)


# !!!!!!!!!!!!! Exportiere compile_commands.json für Code-Analysetools !!!!!!!!!!!!!!!!!!! FÜR CLANG-TIDY
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# !!! Um folgende cmake-Warnungen wegen FetchContent_Declare(..) zu vermeiden ...
#   CMake Warning (dev) at /usr/local/Cellar/cmake/3.30.0/share/cmake/Modules/FetchContent.cmake:1373 (message):
#     The DOWNLOAD_EXTRACT_TIMESTAMP option was not given and policy CMP0135 is
#     not set.  The policy's OLD behavior will be used.  When using a URL
#     download, the timestamps of extracted files should preferably be that of
#     the time of extraction, otherwise code that depends on the extracted
#     contents might not be rebuilt if the URL changes.  The OLD behavior
#     preserves the timestamps from the archive instead, but this is usually not
#     what you want.  Update your project to the NEW behavior or specify the
#     DOWNLOAD_EXTRACT_TIMESTAMP option with a value of true to avoid this
#     robustness issue.
# ..., bitte einen der beiden Auswege waehlen !!!

# Ausweg (i): cmake-Policy einstellen, so dass bei extrahierten Dateien
#             von der angeforderten GoogleTest-Library
#             der Zeitstempel vom Auspackzeitpunkt genommen wird:
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

# Ausweg (ii): 
#   Option DOWNLOAD_EXTRACT_TIMESTAMP TRUE" in FetchContent_Declare(..)
#   entkommentieren

# automat. Herunterladen und Verwenden der GoogleTest-Library
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
### Option verwendet Auspackzeitpunkt als Zeitstempel
### DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Executable erstellen
add_executable(Mandelbrot aufg_09_mandelbrot.cpp Farbe.cpp)
add_executable(Test test.cpp Farbe.cpp)
add_executable(PPM aufg_09_ppm.cpp Farbe.cpp PPM_Datei.cpp PPM_Format.cpp)



enable_testing()

add_executable(
  hello_test
  farbe_unit_tests.cpp
  Farbe.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
