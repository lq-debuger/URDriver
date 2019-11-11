add_executable(mainwindow main.cpp MainWindow.cpp)
# 指定包含头文件路径
include_directories(../driver)
target_link_libraries(
        mainwindow
        ${QT_LIBRARIES}
        driver
)