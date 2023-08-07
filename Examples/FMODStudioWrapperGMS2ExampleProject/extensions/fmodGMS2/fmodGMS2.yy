{
  "resourceType": "GMExtension",
  "resourceVersion": "1.2",
  "name": "fmodGMS2",
  "androidactivityinject": "",
  "androidclassname": "",
  "androidcodeinjection": "",
  "androidinject": "",
  "androidmanifestinject": "",
  "androidPermissions": [],
  "androidProps": false,
  "androidsourcedir": "",
  "author": "",
  "classname": "",
  "copyToTargets": -1,
  "date": "2023-03-31T09:42:00.9043699+08:00",
  "description": "",
  "exportToGame": true,
  "extensionVersion": "3.1.0",
  "files": [
    {"resourceType":"GMExtensionFile","resourceVersion":"1.0","name":"","constants":[
        {"resourceType":"GMExtensionConstant","resourceVersion":"1.0","name":"FMOD_STUDIO_PLAYBACK_PLAYING","hidden":false,"value":"0",},
        {"resourceType":"GMExtensionConstant","resourceVersion":"1.0","name":"FMOD_STUDIO_PLAYBACK_SUSTAINING","hidden":false,"value":"1",},
        {"resourceType":"GMExtensionConstant","resourceVersion":"1.0","name":"FMOD_STUDIO_PLAYBACK_STOPPED","hidden":false,"value":"2",},
        {"resourceType":"GMExtensionConstant","resourceVersion":"1.0","name":"FMOD_STUDIO_PLAYBACK_STARTING","hidden":false,"value":"3",},
        {"resourceType":"GMExtensionConstant","resourceVersion":"1.0","name":"FMOD_STUDIO_PLAYBACK_STOPPING","hidden":false,"value":"4",},
      ],"copyToTargets":3026418971067810030,"filename":"FMODWrapperGMS.dll","final":"","functions":[
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_init","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_init","help":"numberofchannels","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_loadBank","argCount":0,"args":[
            1,
          ],"documentation":"","externalName":"fmod_loadBank","help":"path","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_play","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_play","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_update","argCount":0,"args":[],"documentation":"","externalName":"fmod_update","help":"","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_create","argCount":0,"args":[],"documentation":"","externalName":"fmod_create","help":"","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_bank_loadSampleData","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_bank_loadSampleData","help":"bank_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_createEventInstance","argCount":0,"args":[
            1,
          ],"documentation":"","externalName":"fmod_createEventInstance","help":"event_path","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setParameter","argCount":0,"args":[
            2,
            1,
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_setParameter","help":"handle, parameter_name, value, ignoreseekspeed","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_getBus","argCount":0,"args":[
            1,
          ],"documentation":"","externalName":"fmod_getBus","help":"bus_path","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_bus_getVolume","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_bus_getVolume","help":"bus_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_bus_setVolume","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_bus_setVolume","help":"bus_handle, volume","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_bus_getMute","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_bus_getMute","help":"bus_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_bus_setMute","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_bus_setMute","help":"bus_handle, mute","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getParameter","argCount":0,"args":[
            2,
            1,
          ],"documentation":"","externalName":"fmod_event_getParameter","help":"handle, parameter_name","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_listener_setPosition","argCount":0,"args":[
            2,
            2,
            2,
            2,
          ],"documentation":"","externalName":"fmod_listener_setPosition","help":"listener, x, y, [z]","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_listener_getPosition","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_listener_getPosition","help":"listener","hidden":true,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_set3DPosition","argCount":0,"args":[
            2,
            2,
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_set3DPosition","help":"event_handle, x, y, z","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_release","argCount":0,"args":[],"documentation":"","externalName":"fmod_release","help":"","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_global_setParameter","argCount":0,"args":[
            1,
            2,
            2,
          ],"documentation":"","externalName":"fmod_global_setParameter","help":"parameter_name, value, ignoreseekspeed","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_global_getParameter","argCount":0,"args":[
            1,
          ],"documentation":"","externalName":"fmod_global_getParameter","help":"parameter_name","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setPause","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_setPause","help":"event_handle, paused","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_release","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_release","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_stop","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_stop","help":"event_handle, instant","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setTimelinePosition","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_setTimelinePosition","help":"event_handle, timeline_position","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getTimelinePosition","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_getTimelinePosition","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getVolume","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_getVolume","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setVolume","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_setVolume","help":"event_handle, audio_volume","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getPitch","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_getPitch","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setPitch","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_setPitch","help":"event_handle, audio_pitch","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getReverb","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_getReverb","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setReverb","argCount":0,"args":[
            2,
            2,
          ],"documentation":"","externalName":"fmod_event_setReverb","help":"event_handle, audio_reverb","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_getEventLength","argCount":0,"args":[
            1,
          ],"documentation":"","externalName":"fmod_getEventLength","help":"event_path","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getPlaybackState","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_getPlaybackState","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_getPause","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_getPause","help":"event_handle","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_setPause_all","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_setPause_all","help":"paused","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_release_all","argCount":0,"args":[],"documentation":"","externalName":"fmod_event_release_all","help":"","hidden":false,"kind":1,"returnType":2,},
        {"resourceType":"GMExtensionFunction","resourceVersion":"1.0","name":"fmod_event_stop_all","argCount":0,"args":[
            2,
          ],"documentation":"","externalName":"fmod_event_stop_all","help":"instant","hidden":false,"kind":1,"returnType":2,},
      ],"init":"","kind":1,"order":[
        {"name":"fmod_init","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_create","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_release","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_update","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_loadBank","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_bank_loadSampleData","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_createEventInstance","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_getBus","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_bus_getVolume","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_bus_setVolume","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_bus_getMute","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_bus_setMute","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_listener_setPosition","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_listener_getPosition","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_global_setParameter","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_global_getParameter","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_play","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_setPause","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_set3DPosition","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_release","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_stop","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_setParameter","path":"extensions/fmodGMS2/fmodGMS2.yy",},
        {"name":"fmod_event_getParameter","path":"extensions/fmodGMS2/fmodGMS2.yy",},
      ],"origname":"","ProxyFiles":[],"uncompress":false,"usesRunnerInterface":false,},
  ],
  "gradleinject": "",
  "hasConvertedCodeInjection": true,
  "helpfile": "",
  "HTML5CodeInjection": "",
  "html5Props": false,
  "IncludedResources": [],
  "installdir": "",
  "iosCocoaPodDependencies": "",
  "iosCocoaPods": "",
  "ioscodeinjection": "",
  "iosdelegatename": "",
  "iosplistinject": "",
  "iosProps": false,
  "iosSystemFrameworkEntries": [],
  "iosThirdPartyFrameworkEntries": [],
  "license": "",
  "maccompilerflags": "",
  "maclinkerflags": "",
  "macsourcedir": "",
  "options": [],
  "optionsFile": "options.json",
  "packageId": "",
  "parent": {
    "name": "FMODGMS",
    "path": "folders/FMODGMS.yy",
  },
  "productId": "",
  "sourcedir": "",
  "supportedTargets": -1,
  "tvosclassname": null,
  "tvosCocoaPodDependencies": "",
  "tvosCocoaPods": "",
  "tvoscodeinjection": "",
  "tvosdelegatename": null,
  "tvosmaccompilerflags": "",
  "tvosmaclinkerflags": "",
  "tvosplistinject": "",
  "tvosProps": false,
  "tvosSystemFrameworkEntries": [],
  "tvosThirdPartyFrameworkEntries": [],
}