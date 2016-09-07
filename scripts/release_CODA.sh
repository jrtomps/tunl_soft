
# set RELEASE home
if [ ! -d $RELEASE_TOP_DIR ] ; then
    echo ${HOME}
    export RELEASE_TOP_DIR=${HOME}
fi

# specify the version of the build to use
if [ ! -d $RELEASE_MY ] ; then
    export RELEASE_BUILD=${RELEASE_TOP_DIR}/tunl_soft
    test -d ${RELEASE_TOP_DIR}/tunl_soft | mkdir -p ${RELEASE_TOP_DIR}/tunl_soft
else 
    export RELEASE_BUILD=${RELEASE_MY}
fi

#make sure ROOT is available
if [ ! -d $ROOTSYS ] ; then
    echo ROOTSYS variable is not set.... EXITING...
    exit
fi

if [ X$OS=X ] ; then 
    export OS=`uname`
fi
if [ XARCH=X ] ; then
    export ARCH=`uname -m`
fi
if [ X$OSNAME=X ] ; then
  export OSNAME=${OS}-${ARCH}
fi

# set common environment variables
export RELEASE_SCRIPTS=${RELEASE_BUILD}/scripts
export RELEASE_BIN=${RELEASE_BUILD}/bin/${OSNAME}
export RELEASE_LIB=${RELEASE_BUILD}/lib/${OSNAME}
export RELEASE_SLIB=${RELEASE_BUILD}/slib/${OSNAME}
export RELEASE_SRC=${RELEASE_BUILD}/source
export RELEASE_INC=${RELEASE_SRC}/include
export RELEASE_CMS=${RELEASE_BUILD}/CMS
export RELEASE_CONFIG_PATH=${RELEASE_SRC}/programs/coda2root/config/ro_config.xml


# Add TUNL_BIN to the PATH
export PATH=${PATH}:${RELEASE_BIN}

# append LD_LIBRARY_PATH
if [ ! -d $LD_LIBRARY_PATH ] ; then
        export LD_LIBRARY_PATH=${RELEASE_SLIB}:${RELEASE_LIB}
else
        export LD_LIBRARY_PATH=${RELEASE_SLIB}:${RELEASE_LIB}:${LD_LIBRARY_PATH}
fi
