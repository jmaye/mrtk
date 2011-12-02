remake_find_library(ann ANN/ANN.h PACKAGE ANN)

remake_include(${ANN_HEADERS})

remake_add_library(ml LINK base ${ANN_LIBRARY})
remake_add_headers(INSTALL ml)
