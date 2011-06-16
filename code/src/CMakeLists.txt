remake_qt4_include()
remake_find_package(OpenCV REQUIRED)

remake_project_header(config.h.remake)

remake_include(${OpenCV_DIR})

remake_add_directories(lib bin)
