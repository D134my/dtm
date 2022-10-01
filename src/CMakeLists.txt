project(${project_name})

message("ok now creating ${project_name} lib begins")

file(GLOB src_files parser/*.cpp parser/*.hpp
                    msg/*.cpp   msg/*.hpp, 
                    hashing/*.cpp hashing/*.hpp
                    misc/*.cpp misc/*.hpp
                    socket/*.cpp socket/*.hpp
                    )

add_library(d_t_m ${src_files})