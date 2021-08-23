{
	"targets": [
		{
			"target_name": "nodevision",
			"cflags!": ["-fno-exceptions"],
			"cflags_cc!": ["-fno-exceptions", "-fno-rtti"],
			"include_dirs": [
				"/usr/include/opencv4",
				"<!(node -p \"require('node-addon-api').include_dir\")",
			],
			"libraries": [
				"-lopencv_imgcodecs",
				"-lopencv_core",
			],
			"sources": [
				"src/core/Mat.cpp",
				"src/imgcodecs.cpp",
				"src/main.cpp",
			],
			"xcode_settings": {
				"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
				"CLANG_CXX_LIBRARY": "libc++",
				"MACOSX_DEPLOYMENT_TARGET": "10.7",
			},
			"msvs_settings": {
				"VCCLCompilerTool": {
					"ExceptionHandling": 1,
				},
			},
			"conditions": [
				['OS=="mac"', {
					"cflags+": ["-fvisibility=hidden"],
					"xcode_settings": {
						"GCC_SYMBOLS_PRIVATE_EXTERN": "YES", # -fvisibility=hidden
					},
				}],
			],
		}
	]
}
