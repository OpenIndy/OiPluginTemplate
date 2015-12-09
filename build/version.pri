
#--------------------------
# get OpenIndy-Math version
#--------------------------

OpenIndyMath_VERSION = $$system(git --git-dir $$PWD/../lib/OpenIndy-Core/lib/OpenIndy-Math/.git --work-tree $$PWD describe --always --tags) # get git version
OpenIndyMath_VERSION = $$replace(OpenIndyMath_VERSION, "-g"{1}\w*, ) # remove commit hash after tag name
OpenIndyMath_VERSION = $$replace(OpenIndyMath_VERSION, "-", ".") # remove remaining hyphen
OpenIndyMath_VERSION = $$replace(OpenIndyMath_VERSION, "\b[0-9a-f]{5,40}\b", ) # remove commit hash (only if no tag has been set yet)

isEmpty(OpenIndyMath_VERSION){
    message("no math version")
}else{
    message("OpenIndy-Math version:")
    message($$OpenIndyMath_VERSION)
}

#--------------------------
# get OpenIndy-Core version
#--------------------------

OpenIndyCore_VERSION = $$system(git --git-dir $$PWD/../lib/OpenIndy-Core/.git --work-tree $$PWD describe --always --tags) # get git version
OpenIndyCore_VERSION = $$replace(OpenIndyCore_VERSION, "-g"{1}\w*, ) # remove commit hash after tag name
OpenIndyCore_VERSION = $$replace(OpenIndyCore_VERSION, "-", ".") # remove remaining hyphen
PluginVersion = $$replace(OpenIndyCore_VERSION, "[/.]", )
DEFINES += PLUGIN_INTERFACE_VERSION=$$PluginVersion
OpenIndyCore_VERSION = $$replace(OpenIndyCore_VERSION, "\b[0-9a-f]{5,40}\b", ) # remove commit hash (only if no tag has been set yet)

isEmpty(OpenIndyCore_VERSION){
    message("no core version")
}else{
    message("OpenIndy-Core version:")
    message($$OpenIndyCore_VERSION)
}

#------------------------------------
# get OpenIndy-PluginTemplate version
#------------------------------------

OpenIndyPluginTemplate_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags) # get git version
OpenIndyPluginTemplate_VERSION = $$replace(OpenIndyPluginTemplate_VERSION, "-g"{1}\w*, ) # remove commit hash after tag name
OpenIndyPluginTemplate_VERSION = $$replace(OpenIndyPluginTemplate_VERSION, "-", ".") # remove remaining hyphen
OpenIndyPluginTemplate_VERSION = $$replace(OpenIndyPluginTemplate_VERSION, "\b[0-9a-f]{5,40}\b", ) # remove commit hash (only if no tag has been set yet)

isEmpty(OpenIndyPluginTemplate_VERSION){
    message("no plugin version")
}else{
    message("OpenIndy-PluginTemplate version:")
    message($$OpenIndyPluginTemplate_VERSION)
    VERSION = $$OpenIndyPluginTemplate_VERSION
}
