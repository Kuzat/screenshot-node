{
    "targets": [
        {
            "target_name": "screenshot",
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ],
            "conditions": [
                ['OS=="linux"', {
                    "sources": ["screenshot.cpp", "prtscn.c"],
                    "link_settings": {
                        "libraries": [
                            "-lX11",
                            "-lpng"
                        ]
                    }
                }]
            ]
        }
    ]
}
