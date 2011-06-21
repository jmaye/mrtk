remake_find_library(ann ANN/ANN.h PACKAGE ANN)

remake_include(${ANN_HEADERS})

remake_add_library(statistics LINK exceptions misc ${ANN_LIBRARY})
remake_add_headers(INSTALL statistics)
