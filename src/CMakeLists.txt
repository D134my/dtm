project(${project_name})

message("ok now creating ${project_name} lib begins")
file(GLOB src_files parser/*.cpp parser/*.hpp
                    msg/*.cpp   msg/*.hpp)

message("files are ${src_files}")
add_library(d_t_m ${src_files})