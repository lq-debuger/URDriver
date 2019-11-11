add_executable(mainwindow main.cpp MainWindow.cpp)
target_link_libraries(
        mainwindow
        ${QT_LIBRARIES}
)