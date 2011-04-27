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

remake_pack_deb()
