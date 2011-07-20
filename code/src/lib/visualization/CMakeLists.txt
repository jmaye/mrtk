remake_qt4_ui(visualization)
remake_qt4_moc(visualization)

remake_add_library(visualization LINK ${QT_QTGUI_LIBRARY} ${QWT_QT4_LIBRARY}
  ${QWTPLOT3D_QT4_LIBRARY} exceptions base)
remake_add_headers(INSTALL visualization)
