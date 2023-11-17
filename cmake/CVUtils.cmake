#[[
    @brief  Set the given variable with parent_scope if not defined.
    @param  name - the name of variable want to define
    @param  value - the value of the variable
]]
FUNCTION(set_if_not_defined name value)
    IF(NOT DEFINED ${name})
        SET(${name} ${value} PARENT_SCOPE)
    ENDIF()
ENDFUNCTION()

# ================================================================================
#[[
    @brief  Download dependency library from git repository.
    @param  url - git repository address
    @param  branch - the branch or tag name
    @param  lib_name - the expected local name
]]
FUNCTION(cv_download_dependency url branch lib_name work_directory)
    EXECUTE_PROCESS(COMMAND bash "-c" "if [ ! -d ${work_directory} ];\
        then mkdir -p ${work_directory}; fi")

    EXECUTE_PROCESS(COMMAND bash "-c" "if [ ! -d ${lib_name} ]; then \
        git clone --progress -q --depth=1 -b ${branch} ${url} ${lib_name}; fi"
        WORKING_DIRECTORY ${work_directory})
    #EXECUTE_PROCESS(COMMAND bash "-c" "if [ -d ${lib_name} ];then cd ${lib_name}; \
    #    if [[ `git rev-parse --abbrev-ref HEAD` != ${branch} && `git tag` != ${branch} ]];then cd .. && rm -rf \
    #    ${lib_name} && git clone --depth=1 -b ${branch} ${url} ${libname}; fi else
    #    git clone --depth=1 -b ${branch} ${url} ${libname}; fi"
    #    WORKING_DIRECTORY ${work_directory})
ENDFUNCTION()