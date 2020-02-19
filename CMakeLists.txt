cmake_minimum_required(VERSION 3.08)

project(szachy-c)

set(SHARED OFF) # force static libs in allegro
add_subdirectory(allegro5)

add_executable(${PROJECT_NAME}
  src/main.c
  src/board.c
  src/game.c
  src/pieces.c
  src/allegro/alButtons.c
  src/allegro/alImages.c
  src/allegro/alMouse.c
  src/allegro/alWindow.c
  )

target_include_directories(${PROJECT_NAME}
  PRIVATE
  include/
  allegro5/include/
  allegro5/addons/font/
  allegro5/addons/ttf/
  allegro5/addons/image/
  allegro5/addons/primitives/
  allegro5/addons/native_dialog/
  allegro5/addons/color/
  ${PROJECT_BINARY_DIR}/allegro5/include/ # generated headers
  )

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  allegro_ttf
  allegro_primitives
  allegro_image
  allegro_font
  allegro_dialog
  allegro_color
  allegro
  )
