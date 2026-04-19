find_path(
  WAYLAND_CLIENT_INCLUDE_DIR
  NAMES wayland-client.h
)

find_library(
  WAYLAND_CLIENT_LIBRARY
  NAMES wayland-client libwayland-client libwayland-client0
)

if(WAYLAND_CLIENT_INCLUDE_DIR AND WAYLAND_CLIENT_LIBRARY)
  add_library(wayland::client UNKNOWN IMPORTED)

  set_target_properties(
    wayland::client PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${WAYLAND_CLIENT_INCLUDE_DIR}"
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
    IMPORTED_LOCATION "${WAYLAND_CLIENT_LIBRARY}"
  )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  Wayland
  REQUIRED_VARS WAYLAND_CLIENT_LIBRARY WAYLAND_CLIENT_INCLUDE_DIR
)

mark_as_advanced(
  WAYLAND_CLIENT_INCLUDE_DIR
  WAYLAND_CLIENT_LIBRARY
)