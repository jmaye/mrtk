remake_qt4_include()
remake_find_library(qwt-qt4 qwt-qt4/qwt.h PACKAGE libqwt5-qt4-dev)
#remake_find_package(OpenCV REQUIRED)

remake_project_header(config.h.remake)

#remake_include(${OpenCV_DIR})
remake_include(${QWT_QT4_HEADERS})

remake_add_directories(lib bin)
