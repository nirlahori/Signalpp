cmake_minimum_required(VERSION 3.16)

project(Signalpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Signalpp main.cpp
    signal_service.hpp
    internal/sigset_impl.hpp
    signal_service_group.hpp
    signal_manager.hpp)

include(GNUInstallDirs)
install(TARGETS Signalpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
