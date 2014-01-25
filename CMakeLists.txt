project(ktexteditor_replicode)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(ktexteditor_replicode_SRCS replicodeplugin.cpp)

kde4_add_plugin(ktexteditor_replicode ${ktexteditor_replicode_SRCS})

target_link_libraries(ktexteditor_replicode ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS})

install(TARGETS ktexteditor_replicode DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES replicodeui.rc DESTINATION ${DATA_INSTALL_DIR}/ktexteditor_replicode)

install(FILES ktexteditor_replicode.desktop DESTINATION ${SERVICES_INSTALL_DIR})
 
