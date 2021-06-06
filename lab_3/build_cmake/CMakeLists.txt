cmake_minimum_required(VERSION 3.0)
project(lab_03)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

#прописать в терминале! export PATH=/usr/local/opt/qt@5/bin:$PATH

add_executable(${PROJECT_NAME}
        ../src/main.cpp
        ../inc/mainwindow.h
        ../src/mainwindow.cpp
        ../inc/model/dot.h
        ../src/model/dot.cpp
        ../src/model/link.cpp
        ../inc/model/link.h
        ../src/model/model_struct.cpp
        ../inc/model/model_struct.h
        ../src/model/model.cpp
        ../inc/model/model.h
        ../inc/object/object.h
        ../src/object/composite.cpp
        ../inc/object/composite.h
        ../src/camera/camera.cpp
        ../inc/camera/camera.h
        ../inc/visitor/visitor.h
        ../src/scene/scene.cpp
        ../inc/scene/scene.h
        ../inc/managers/base_manager.h
        ../src/managers/scene/scene_manager.cpp
        ../inc/managers/scene/scene_manager.h
        ../inc/managers/scene/scene_manager_creator.h
        ../src/managers/scene/scene_manager_creator.cpp
        ../inc/managers/transform/transform_manager_creator.h
        ../inc/managers/transform/transform_manager.h
        ../src/managers/transform/transform_manager.cpp
        ../src/managers/transform/transform_manager_creator.cpp
        ../src/managers/draw/draw_manager.cpp
        ../inc/managers/draw/draw_manager.h
        ../inc/managers/draw/draw_manager_creator.h
        ../src/managers/draw/draw_manager_creator.cpp
        ../inc/drawer/abstract_drawer.h
        ../inc/drawer/abstract_drawer_factory.h
        ../inc/drawer/drawer_qt.h
        ../src/drawer/drawer_qt.cpp
        ../inc/drawer/drawer_qt_factory.h
        ../src/drawer/drawer_qt_factory.cpp
        ../inc/managers/load/load_manager.h
        ../src/managers/load/load_manager.cpp
        ../inc/managers/load/abstract_load_controller.h
        ../src/managers/load/abstract_load_controller.cpp
        ../inc/managers/load/load_manager_creator.h
        ../src/managers/load/load_manager_creator.cpp
        ../inc/builder/base_builder.h
        ../inc/builder/builder_model.h
        ../src/builder/builder_model.cpp
        ../inc/builder/builder_camera.h
        ../src/builder/builder_viewer.cpp
        ../src/builder/builder_scene.cpp
        ../inc/builder/builder_scene.h
        ../inc/loader/base_loader.h
        ../inc/loader/base_loader_model.h
        ../inc/loader/loader_model_file.h
        ../src/loader/loader_model_file.cpp
        ../inc/loader/base_loader_camera.h
        ../inc/loader/loader_camera_file.h
        ../src/loader/loader_camera_file.cpp
        ../src/loader/loader_scene_file.cpp
        ../inc/loader/loader_scene_file.h
        ../inc/loader/base_loader_scene.h
        ../inc/managers/load/load_model_controller.h
        ../src/managers/load/load_model_controller.cpp
        ../src/managers/load/load_model_controller_creator.cpp
        ../inc/managers/load/load_model_controller_creator.h
        ../inc/managers/load/load_scene_controller.h
        ../inc/managers/load/load_scene_controller_creator.h
        ../src/managers/load/load_scene_controller.cpp
        ../src/managers/load/load_scene_controller_creator.cpp
        ../inc/commands/base_command.h
        ../inc/commands/camera_command.h
        ../src/commands/camera_command.cpp
        ../src/commands/model_command.cpp
        ../inc/commands/model_command.h
        ../src/commands/scene_command.cpp
        ../inc/commands/scene_command.h
        ../inc/facade/facade.h
        ../src/facade/facade.cpp
        ../inc/exceptions.h
        ../inc/configuration/abstract_cfg.h
        ../inc/configuration/creator_cfg.h
        ../src/configuration/creator_cfg.cpp
        ../src/configuration/configuration.cpp
        ../inc/configuration/configuration.h
        )

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} -L/usr/local/Cellar/libconfig/1.7.2/lib/ -lconfig++)
