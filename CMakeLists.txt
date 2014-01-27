project(katereplicodeplugin)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include_directories(${KDE4_INCLUDES} ${QT_INCLUDES})
add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

set(katereplicode_SRCS replicodeplugin.cpp replicodeconfigpage.cpp replicodeconfig.cpp replicodeview.cpp replicodesettings.cpp)

kde4_add_ui_files(ui_SRCS config.ui)

kde4_add_plugin(katereplicodeplugin ${katereplicode_SRCS} ${ui_SRCS})

target_link_libraries(katereplicodeplugin ${KDE4_KDEUI_LIBS} ${KDE4_KTEXTEDITOR_LIBS} kateinterfaces)

install(TARGETS katereplicodeplugin DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES ui.rc DESTINATION ${DATA_INSTALL_DIR}/kate/plugins/katereplicodeplugin)

install(FILES katereplicodeplugin.desktop DESTINATION ${SERVICES_INSTALL_DIR})
 
