-- csg2d
target("csg2d")
    add_includedirs("../")
    add_files("**.cpp")
    add_packages("sfml")
    set_kind("binary")
