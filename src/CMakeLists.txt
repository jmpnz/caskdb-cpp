set(caskdb_lib_src 
    main.cpp  
    serde.cpp
    file_manager.cpp
    storage.cpp
    )

add_library(libcaskdb ${caskdb_lib_src})