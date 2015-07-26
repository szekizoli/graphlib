solution "GraphLib"
    configurations  { "Debug", "Release" }
    startproject    "GraphLib-unittest"

project "GraphLib-core"
    kind      "StaticLib"
    language  "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "../src/core/**.h", 
            "../src/core**.cpp" }
    removefiles { "../src/core/graph/iterator/*" }

    filter "configurations:Debug"
    	defines {"DEBUG"}
    	flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "GraphLib-example"
    kind      "ConsoleApp"
    language  "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "../src/example/**.h", 
            "../src/example/**.cpp" }

    links {"GraphLib-core"}
    includedirs { "../src/core" }

    filter "configurations:Debug"
        defines {"DEBUG"}
        flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "GoogleTest"
    kind      "StaticLib"
    language  "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "../3rd/gtest-1.7.0/src/gtest_main.cc", 
            "../3rd/gtest-1.7.0/src/gtest-all.cc" }

    libdirs { "../3rd/" }
    includedirs {"../3rd/gtest-1.7.0","../3rd/gtest-1.7.0/include"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

project "GraphLib-unittest"
    kind      "ConsoleApp"
    language  "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "../src/unittest/**.h", 
            "../src/unittest/**.cpp" }

    links {"GraphLib-core", "GoogleTest"}
    libdirs { "../3rd/" }
    includedirs {"../3rd/gtest-1.7.0","../3rd/gtest-1.7.0/include", "../src/core" }
    filter "configurations:Debug"
        defines {"DEBUG"}
        flags {"Symbols"}
    
    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"