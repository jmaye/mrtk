cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  online-recog
  VERSION 0.1
  RELEASE alpha
  SUMMARY "Online place recognition for mobile robots"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "http://aslforge.ethz.ch/projects/online-recog"
  LICENSE "GNU Lesser General Public License (LGPL)"
  INSTALL /usr
)

remake_pack_deb(libann0 libqt4-gui libqwt5-qt4)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  online-recog
  libann-dev
  libqwt5-qt4-dev
  libqt4-dev
  libeigen2-dev
)

remake_doc(
  html
  latex
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
  online-recog
)
