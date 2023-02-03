# Copyright (c) 2020 Continental AG and subsidiaries

# Order based on specs Requires/After
declare -a specs_list=(
"oem-configuration.mk"
"telematics-services-frwk.mk"
"telematics-services.mk"
"telematics-services-voicemgr.mk"
"audio.mk"
"common.mk"
"call-apps.mk"
)

#Fill the map with executables used for testing NAD on VM
#run_repo_list["executable with params"]="parent path of executable"
declare -A run_repo_list;
run_repo_list["audio-mgrd"]="./vmbuild/bin"
run_repo_list["antennamgrd"]="./vmbuild/bin"
run_repo_list["SuzukiApp"]="./vmbuild/bin"
run_repo_list["RemoteCtrlApp"]="./vmbuild/bin"
run_repo_list["RemoteSrvcApp"]="./vmbuild/bin"
run_repo_list["sdbServer"]="./vmbuild/bin"
run_repo_list["voicemgrd"]="./vmbuild/bin"
run_repo_list["mobile-mgrd"]="./vmbuild/bin"
run_repo_list["featuremgr"]="./vmbuild/bin"
run_repo_list["ConsoleService"]="./vmbuild/tst/bin"
run_repo_list["ConnCoreApp"]="./vmbuild/bin"
run_repo_list["VoiceCallApp"]="./vmbuild/tst/bin"
run_repo_list["test-alx-ipc"]="./vmbuild/tst/bin"

# Special services have dedicated columns (right to left)
# Remaining services are organized in the leftmost column randomly
special_services=("ConsoleService" "SuzukiApp" "RemoteCtrlApp" "RemoteSrvcApp" "ConnCoreApp" "test-alx-ipc")
