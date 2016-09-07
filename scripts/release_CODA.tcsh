#!/bin/csh

# set RELEASE home
if(!($?RELEASE_TOP_DIR)) setenv RELEASE_TOP_DIR ${HOME}

# specify the version of the build to use
if(!($?RELEASE_MY)) then
    setenv RELEASE_BUILD ${RELEASE_TOP_DIR}/tunl_soft
    test -d ${RELEASE_TOP_DIR}/tunl_soft | mkdir -p ${RELEASE_TOP_DIR}/tunl_soft
else 
    setenv RELEASE_BUILD ${RELEASE_MY}
endif

#make sure ROOT is available
if(!($?ROOTSYS)) then
    echo ROOTSYS variable is not set.... EXITING...
    exit
endif

if(!($?OS)) setenv OS `uname`
if(!($?ARCH)) setenv ARCH `uname -m`
if(!($?OSNAME)) setenv OSNAME ${OS}-${ARCH}

# set common environment variables
setenv RELEASE_SCRIPTS ${RELEASE_BUILD}/scripts
test -d ${CODA_BIN}/tunl_soft | mkdir -p ${CODA_BIN}/tunl_soft
setenv RELEASE_BIN ${CODA_BIN}/tunl_soft
setenv RELEASE_LIB ${RELEASE_BUILD}/lib/${OSNAME}
setenv RELEASE_SLIB ${RELEASE_BUILD}/slib/${OSNAME}
setenv RELEASE_SRC ${RELEASE_BUILD}/source
setenv RELEASE_INC ${RELEASE_SRC}/include
setenv RELEASE_CMS ${RELEASE_BUILD}/CMS
setenv RELEASE_CONFIG_PATH ${RELEASE_SRC}/programs/coda2root/config/ro_config.xml


# Add TUNL_BIN to the PATH
setenv PATH ${PATH}:${RELEASE_BIN}

# append LD_LIBRARY_PATH
if(!($?LD_LIBRARY_PATH)) then
        setenv LD_LIBRARY_PATH ${RELEASE_SLIB}:${RELEASE_LIB}
else
        setenv LD_LIBRARY_PATH ${RELEASE_SLIB}:${RELEASE_LIB}:${LD_LIBRARY_PATH}
endif
