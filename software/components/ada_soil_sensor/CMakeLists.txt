set(srcs)
set(include_dirs ".")

list(APPEND srcs "ada_soil_sensor.c")

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       PRIV_REQUIRES esp32_hal
                       )
