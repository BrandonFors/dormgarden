set(srcs)
set(include_dirs ".")



list(APPEND srcs "hal.c") 



idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS "${include_dirs}"
                       PRIV_REQUIRES 
                                     esp_driver_spi
                                     esp_driver_gpio
                                     esp_driver_i2c
                                     esp_timer ) 
# PRIV_REQUIRES tells espidf the component dependancies of this component