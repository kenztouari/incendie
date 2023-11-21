cmake_minimum_required(VERSION 3.26)
project(Incendie)

set(CMAKE_CXX_STANDARD 17)

add_executable(Incendie main.c
        src/etatForet.c
        include/etatForet.h
        src/case.c
        include/case.h
        src/interaction_utilisateur.c
        include/interaction_utilisateur.h
        src/simulation.c
        include/simulation.h
        include/global.h
        src/point.c
        include/point.h
)
