cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  mrtk
  VERSION 0.1
  RELEASE alpha
  SUMMARY "A C++ based library for robotic algorithms and tools development"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "https://github.com/jmaye/mrtk"
  LICENSE "GNU Lesser General Public License (LGPL)"
  INSTALL /usr
  EXTRA_CXX_FLAGS -std=c++0x
)

remake_pack_deb(libann0 libqt4-gui libqwt5-qt4 libgsl0ldbl libdai)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  mrtk
  libdai-dev
  libann-dev
  libqwt5-qt4-dev
  libqt4-dev
  libeigen2-dev
  libgsl0-dev
)

remake_doc(
  html
  latex
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
  mrtk
)
