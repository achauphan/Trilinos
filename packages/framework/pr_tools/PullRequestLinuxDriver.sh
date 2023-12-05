#!/usr/bin/env bash
SCRIPTFILE=$(realpath ${WORKSPACE:?}/Trilinos/packages/framework/pr_tools/PullRequestLinuxDriver.sh)
SCRIPTPATH=$(dirname $SCRIPTFILE)
source ${SCRIPTPATH:?}/common.bash
# set -x  # echo commands

# Fetch arguments
on_weaver=$(echo "$@" | grep '\-\-on_weaver' &> /dev/null && echo "1")
on_ats2=$(echo "$@" | grep '\-\-on_ats2' &> /dev/null && echo "1")
on_kokkos_develop=$(echo "$@" | grep '\-\-kokkos\-develop' &> /dev/null && echo "1")
on_rhel8=$(echo "$@" | grep '\-\-on_rhel8' &> /dev/null && echo "1")

bootstrap=$(echo "$@" | grep '\-\-\no\-bootstrap' &> /dev/null && echo "0" || echo "1")

# Configure ccache via environment variables
function configure_ccache() {
    print_banner "Configuring ccache"

    envvar_set_or_create CCACHE_NODISABLE true
    envvar_set_or_create CCACHE_DIR '/fgs/trilinos/ccache/cache'
    envvar_set_or_create CCACHE_BASEDIR "${WORKSPACE:?}"
    envvar_set_or_create CCACHE_NOHARDLINK true
    envvar_set_or_create CCACHE_UMASK 077
    envvar_set_or_create CCACHE_MAXSIZE 100G

    message_std "PRDriver> " "$(ccache --show-stats --verbose)"
}

# Load the right version of Git / Python based on a regex
# match to the Jenkins job name.
function bootstrap_modules() {
    print_banner "Bootstrap environment modules start"
    message_std "PRDriver> " "Job is $JOB_BASE_NAME"

    vortex_regex=".*(vortex).*"
    container_regex=".*(container).*"
    if [[ ${NODE_NAME:?} =~ ${vortex_regex} || ${on_ats2} == "1" ]]; then
        execute_command_checked "module load git/2.20.0"
        execute_command_checked "module load python/3.7.2"
        get_python_packages pip3
        # Always create user's tmp dir for nvcc. See https://github.com/trilinos/Trilinos/issues/10428#issuecomment-1109956415.
        mkdir -p /tmp/trilinos

        module list
    elif [[ ${NODE_NAME:?} =~ ${container_regex} ]]; then
	echo "Nothing done for bootstrap in a container"
	module list
    elif [[ ${on_weaver} == "1" ]]; then
        module unload git
        module unload python
        module load git/2.10.1
        module load python/3.7.3
        get_python_packages pip3

        module list
    elif [[ ${on_rhel8} == "1" ]]; then
        source /projects/sems/modulefiles/utils/sems-modules-init.sh
        module unload sems-git
        module unload sems-python
        module load sems-git/2.37.0
        module load sems-python/3.9.0

        module list
    else
        source /projects/sems/modulefiles/utils/sems-modules-init.sh
        execute_command_checked "module unload sems-git"
        execute_command_checked "module unload sems-python"
        execute_command_checked "module load sems-git/2.37.0"
        execute_command_checked "module load sems-python/3.9.0"
        execute_command_checked "module load sems-ccache"
        configure_ccache

        module list
    fi

    print_banner "Bootstrap environment modules complete"
}

print_banner "PullRequestLinuxDriver.sh"

# Set up Sandia PROXY environment vars
envvar_set_or_create https_proxy 'http://proxy.sandia.gov:80'
envvar_set_or_create http_proxy  'http://proxy.sandia.gov:80'
envvar_set_or_create no_proxy    'localhost,.sandia.gov,localnets,127.0.0.1,169.254.0.0/16,forge.sandia.gov'
#export https_proxy=http://proxy.sandia.gov:80
#export http_proxy=http://proxy.sandia.gov:80
#export no_proxy='localhost,.sandia.gov,localnets,127.0.0.1,169.254.0.0/16,forge.sandia.gov'

# bootstrap the python and git modules for this system
if [[ ${bootstrap} == "1" ]]; then
    bootstrap_modules
fi

envvar_set_or_create PYTHON_EXE $(which python3)
message_std "PRDriver> " "Python EXE : ${PYTHON_EXE:?}"

# Identify the path to the trilinos repository root
REPO_ROOT=`readlink -f ${SCRIPTPATH:?}/../..`
test -d ${REPO_ROOT:?}/.git || REPO_ROOT=`readlink -f ${WORKSPACE:?}/Trilinos`
message_std "PRDriver> " "REPO_ROOT : ${REPO_ROOT}"

# Get the md5 checksum of this script:
sig_script_old=$(get_md5sum ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriver.sh)

# Get the md5 checksum of the Merge script
sig_merge_old=$(get_md5sum ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriverMerge.py)

if [[ ${on_kokkos_develop} == "1" ]]; then
    message_std "PRDriver> --kokkos-develop is set - setting kokkos and kokkos-kernels packages to current develop"
    "${SCRIPTPATH}"/SetKokkosDevelop.sh
else
    print_banner "Merge Source into Target"
    message_std "PRDriver> " "TRILINOS_SOURCE_SHA: ${TRILINOS_SOURCE_SHA:?}"

    # Prepare the command for the MERGE operation
    merge_cmd_options=(
        ${TRILINOS_SOURCE_REPO:?}
        ${TRILINOS_TARGET_REPO:?}
        ${TRILINOS_TARGET_BRANCH:?}
        ${TRILINOS_SOURCE_SHA:?}
        ${WORKSPACE:?}
        )
    merge_cmd="${PYTHON_EXE:?} ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriverMerge.py ${merge_cmd_options[@]}"


    # Call the script to handle merging the incoming branch into
    # the current trilinos/develop branch for testing.
    message_std "PRDriver> " ""
    message_std "PRDriver> " "Execute Merge Command: ${merge_cmd:?}"
    message_std "PRDriver> " ""
    execute_command_checked "${merge_cmd:?}"
    #err=$?
    #if [ $err != 0 ]; then
    #    print_banner "An error occurred during merge"
    #    exit $err
    #fi
    print_banner "Merge completed"


    print_banner "Check for PR Driver Script Modifications"

    # Get the md5 checksum of this script:
    #sig_script_new=$(get_md5sum ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriver.sh)
    sig_script_new=$(get_md5sum ${SCRIPTFILE:?})
    message_std "PRDriver> " ""
    message_std "PRDriver> " "Script File: ${SCRIPTFILE:?}"
    message_std "PRDriver> " "Old md5sum : ${sig_script_old:?}"
    message_std "PRDriver> " "New md5sum : ${sig_script_new:?}"

    # Get the md5 checksum of the Merge script
    #sig_merge_new=$(get_md5sum ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriverMerge.py)
    export MERGE_SCRIPT=${SCRIPTPATH:?}/PullRequestLinuxDriverMerge.py
    sig_merge_new=$(get_md5sum ${MERGE_SCRIPT:?})
    message_std "PRDriver> " ""
    message_std "PRDriver> " "Script File: ${MERGE_SCRIPT:?}"
    message_std "PRDriver> " "Old md5sum : ${sig_merge_old:?}"
    message_std "PRDriver> " "New md5sum : ${sig_merge_new:?}"

    if [ "${sig_script_old:?}" != "${sig_script_new:?}" ] || [ "${sig_merge_old:?}" != "${sig_merge_new:?}"  ]
    then
        message_std "PRDriver> " ""
        message_std "PRDriver> " "Driver or Merge script change detected. Re-launching PR Driver"
        message_std "PRDriver> " ""
        ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriver.sh
        exit $?
    fi

    message_std "PRDriver> " ""
    message_std "PRDriver> " "Driver and Merge scripts unchanged, proceeding to TEST phase"
    message_std "PRDriver> " ""
fi

# determine what MODE we are using
mode="standard"
if [[ "${JOB_BASE_NAME:?}" == "Trilinos_pullrequest_gcc_8.3.0_installation_testing" ]]; then
    mode="installation"
fi


envvar_set_or_create TRILINOS_BUILD_DIR ${WORKSPACE}/pull_request_test

#message_std "PRDriver> " "Create build directory if it does not exist."
#message_std "PRDriver> " "Build Dir: ${TRILINOS_BUILD_DIR:?}"
#mkdir -p ${TRILINOS_BUILD_DIR:?}



print_banner "Launch the Test Driver"


# Prepare the command for the TEST operation
test_cmd_options=(
    --source-repo-url=${TRILINOS_SOURCE_REPO:?}
    --target-repo-url=${TRILINOS_TARGET_REPO:?}
    --target-branch-name=${TRILINOS_TARGET_BRANCH:?}
    --pullrequest-build-name=${JOB_BASE_NAME:?}
    --genconfig-build-name=${GENCONFIG_BUILD_NAME:?}
    --pullrequest-env-config-file=${LOADENV_CONFIG_FILE:?}
    --pullrequest-gen-config-file=${GENCONFIG_CONFIG_FILE:?}
    --pullrequest-number=${PULLREQUESTNUM:?}
    --jenkins-job-number=${BUILD_NUMBER:?}
    --req-mem-per-core=3.0
    --max-cores-allowed=${TRILINOS_MAX_CORES:=29}
    --num-concurrent-tests=4
    --test-mode=${mode}
    --workspace-dir=${WORKSPACE:?}
    --filename-packageenables=${WORKSPACE:?}/packageEnables.cmake
    --filename-subprojects=${WORKSPACE:?}/package_subproject_list.cmake
    --source-dir=${WORKSPACE}/Trilinos
    --build-dir=${TRILINOS_BUILD_DIR:?}
    --ctest-driver=${WORKSPACE:?}/Trilinos/cmake/SimpleTesting/cmake/ctest-driver.cmake
    --ctest-drop-site=${TRILINOS_CTEST_DROP_SITE:?}
)

if [[ ${on_kokkos_develop} == "1" ]]
then
    test_cmd_options+=( "--extra-configure-args=\"-DKokkos_SOURCE_DIR_OVERRIDE:string=kokkos;-DKokkosKernels_SOURCE_DIR_OVERRIDE:string=kokkos-kernels\" ")
fi

if [[ ${GENCONFIG_BUILD_NAME} == *"gnu"* ]]
then
    test_cmd_options+=( "--use-explicit-cachefile ")
fi 

# Execute the TEST operation
test_cmd="${PYTHON_EXE:?} ${REPO_ROOT:?}/packages/framework/pr_tools/PullRequestLinuxDriverTest.py ${test_cmd_options[@]}"

# Call the script to launch the tests
print_banner "Execute Test Command"
message_std "PRDriver> " "cd $(pwd)"
message_std "PRDriver> " "${test_cmd:?} --pullrequest-cdash-track='${PULLREQUEST_CDASH_TRACK:?}'"
execute_command_checked "${test_cmd:?} --pullrequest-cdash-track='${PULLREQUEST_CDASH_TRACK:?}'"

#${test_cmd} --pullrequest-cdash-track="${PULLREQUEST_CDASH_TRACK:?}"
#exit $?
