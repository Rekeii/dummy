{
    "targets": [
        {
            "target_name": "addon",
            "sources": ["addon.cpp"],
            "include_dirs": [
                "/usr/lib/node_modules/node-addon-api",
                "./node_modules/node-addon-api"
            ],
            "dependencies": ["<!(node -p \"require('node-addon-api').gyp\")"],
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
        }
    ]
}
