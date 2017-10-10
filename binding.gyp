{
    "targets": [
        {
            "target_name": "phi",
            "sources": [
                "phi.cc",
                "phi.c",                
                "sph/aes_helper.c",             
                "sph/sph_gost.c",               
                "sph/sph_fugue.c",
                "sph/sph_cubehash.c",
                "sph/sph_echo.c",            
                "sph/sph_jh.c",              
                "sph/sph_skein.c",              
            ],
            "include_dirs": [               
                "sph",
                "<!(node -e \"require('nan')\")"
            ],
            "cflags_cc": [
                "-std=c++0x"
            ],
        }
    ]
}
