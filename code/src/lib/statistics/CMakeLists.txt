remake_find_library(ann ANN/ANN.h PACKAGE ANN)
remake_find_file(eigen2/Eigen/Core PACKAGE libeigen2-dev)

remake_include(${LIBEIGEN2_DEV_FILE}/eigen2)
remake_include(${ANN_HEADERS})

remake_add_library(statistics LINK exceptions misc ${ANN_LIBRARY})
remake_add_headers(INSTALL statistics)
