## This cmakelist.txt file was generated from
## the UAV Toolbox Support Package for PX4 Autopilots

add_definitions(
-DMODEL=lee_controller -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 -DPX4 -DFMUv5 -DNULL=0 -DMW_PX4_NUTTX_BUILD -DEXTMODE_DISABLETESTING -DEXTMODE_DISABLEPRINTF -DEXTMODE_DISABLE_ARGS_PROCESSING=1 -D__linux__ -DXCP_PLATFORM_LINUX_NO_PIE_SUPPORT -DSTACK_SIZE=64 -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__ -DRT )

px4_add_module(
    MODULE modules__px4_simulink_app
    MAIN px4_simulink_app
    STACK_MAIN 2000
SRCS
   MW_PX4_PWM.cpp
   MW_uORB_Read.cpp
   MW_uORB_Write.cpp
   MW_ParameterRead.cpp
   MW_SCI.cpp
   ert_main.cpp
   lee_controller.cpp
   lee_controller_data.cpp
   rtGetInf.cpp
   rtGetNaN.cpp
   rt_nonfinite.cpp
   MW_PX4_TaskControl.cpp
   nuttxinitialize.cpp
    COMPILE_FLAGS
       -fpermissive
       -Wno-narrowing
    INCLUDES
       ${PX4_SOURCE_DIR}/src/modules/mavlink
       ${PX4_SOURCE_DIR}/mavlink/include/mavlink
       /home/simone/Scrivania/MATLAB/tarot_simulink
       /home/simone/Documents/MATLAB/SupportPackages/R2021b/toolbox/target/supportpackages/px4/include
       /home/simone/Documents/MATLAB/SupportPackages/R2021b/toolbox/target/shared/svd/include
       /home/simone/Scrivania/MATLAB/tarot_simulink/lee_controller_ert_rtw
       /home/simone/MATLAB/R2021b/extern/include
       /home/simone/MATLAB/R2021b/simulink/include
       /home/simone/MATLAB/R2021b/rtw/c/src
       /home/simone/MATLAB/R2021b/rtw/c/src/ext_mode/common
       /home/simone/MATLAB/R2021b/rtw/c/ert
       /home/simone/MATLAB/R2021b/rtw/c/src/ext_mode/serial
       /home/simone/Documents/MATLAB/SupportPackages/R2021b/toolbox/target/shared/externalmode_daemon/include
)

get_target_property(PX4_SL_APP_COMPILE_FLAGS modules__px4_simulink_app COMPILE_OPTIONS)
list(REMOVE_ITEM PX4_SL_APP_COMPILE_FLAGS -Werror)
set_target_properties(modules__px4_simulink_app PROPERTIES COMPILE_OPTIONS "${PX4_SL_APP_COMPILE_FLAGS}")

