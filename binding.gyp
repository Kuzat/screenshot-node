{
    "targets": [
        {
            "target_name": "screenshot",
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
            "conditions": [
                ['OS=="linux"', {
                    "sources": ["bin/linux/screenshot_linux.cpp", "bin/linux/prtscn_linux.c"],
                    "link_settings": {
                        "libraries": [
                            "-lX11",
                            "-lpng"
                        ]
                    }
                }],
                ['OS=="mac"', {
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                        'OTHER_CFLAGS': [
                            '-ObjC++'
                        ]
                    },
                    "sources": ["bin/osx/screenshot_osx.cpp", "bin/osx/prtscn_osx.mm"],
                    "link_settings": {
                        "libraries": [
                            "-framework CoreGraphics",
                            "-framework CoreServices",
                            "-framework ImageIO",
                            "-framework Foundation"
                        ]
                    }
                }]
            ]
        }
    ]
}
