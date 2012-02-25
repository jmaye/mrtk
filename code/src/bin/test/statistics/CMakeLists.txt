remake_find_library(RInside RInside/include/RInside.h PACKAGE RInside)
remake_find_library(Rcpp Rcpp/include/Rcpp.h PACKAGE Rcpp)
remake_find_library(R R.h PACKAGE r-base)

remake_include(${RINSIDE_HEADERS} ${RCPP_HEADERS} ${R_HEADERS})

remake_add_executables(TESTING LINK statistics ${RINSIDE_LIBRARY}
  ${RCPP_LIBRARY} ${R_LIBRARY})
