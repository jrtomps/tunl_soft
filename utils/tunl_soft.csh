
#change the line below to reflect experiment name
setenv MY_EXPERIMENT /home/coda/experiments/coda2root_template

setenv RELEASE_MY ${CODA}/../tunl_soft

#change the line below to reflect raw data location
setenv RELEASE_CODA_FILE_PATH /disk/userdata/data_location

if(!($?RELEASE_ROOT_FILE_PATH)) then
    test -d ${MY_EXPERIMENT}/analysis | mkdir -p ${MY_EXPERIMENT}/analysis
    setenv RELEASE_ROOT_FILE_PATH ${MY_EXPERIMENT}/analysis
endif

if(-f ${MY_EXPERIMENT}/ro_config.xml) then
 echo "found config file ${MY_EXPERIMENT}/ro_config.xml"
else 
 cp ${CODA}/../tunl_soft/source/programs/coda2root/config/ro_config.xml ${MY_EXPERIMENT}/.
endif

setenv RELEASE_CONFIG_PATH ${MY_EXPERIMENT}/ro_config.xml
