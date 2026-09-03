-- import("core.base.json")
-- import("core.base.option")

add_rules("mode.debug", "mode.release")

option("LoaderArchitecture", function()
	set_default("Auto")
	set_values("LoaderArchitecture","Auto", "OneProcess", "MicrokernelLike")
	local Value = get_config("LoaderArchitecture")
	Value = get_config("LoaderArchitecture")
	if Value == "OneProcess" or ((Value == "Auto") and (is_plat("windows"))) then
		add_defines("OgMacroOptionsLoaderArchitecture=OneProcess")
	elseif Value == "MicrokernelLike" or (Value == "Auto") then
		add_defines("OgMacroOptionsLoaderArchitecture=MicrokernelLike")
	end
end)

option("ThreadsLibrary", function()
	set_default("Auto")
	set_values("ThreadsLibrary", "C11Threads", "Pthread", "McfGThread", "Auto")
	local Value = get_config("ThreadsLibrary")
	if
		(Value == "McfGThread")
		or (Value == "Auto" and (is_os("windows") and is_subhost("msys", "cygwin") and has_package("McfGThread")))
	then
		add_packages("mcfgthread")
        add_defines("OgMacroOptionsThreadsLibrary=McfGThread")
	elseif (Value == "Pthread") or ((Value == "Auto") and (is_os("windows") and is_subhost("msys", "cygwin"))) then
		add_links("pthread")
		add_defines("_REENTRANT")
		add_cflags("-pthread")
        add_defines("OgMacroOptionsThreadsLibrary=Pthread")
	elseif Value == "C11Threads" then
        add_defines("OgMacroOptionsThreadsLibrary=C11Threads")
	end
end)
option("EnableLibdwarf", function()
	set_default(false)
	local Value = get_config("EnableLibdwarf")
	if Value then
		add_links("dwarf")
		add_defines("OgMacroOptionsEnableLibdwarfComponent=true")
		add_packages("libdwarf")
	end
end)
option("EnableUnicode", function()
	set_default(true)
	local Value = get_config("EnableUnicode")
	if Value then
		add_defines("OgMacroOptionsEnableUnicode=true")
	end
end)
option("ExternLinker", function()
	set_default("None")
	set_values("Gold", "Bfd", "Mold", "Lld", "Wild", "None")
	local Value = get_config("ExternLinker")
	if Value == "None" then
	elseif Value == "Gold" then
		add_ldflags("gcc::-fuse-ld=gold", "clang::-fuse-ld=gold")
	elseif Value == "Bfd" then
		add_ldflags("gcc::-fuse-ld=bfd", "clang::-fuse-ld=bfd")
	elseif Value == "Mold" then
		add_ldflags("gcc;;-fuse-ld=mold", "clang::-fuse-ld=mold")
	elseif Value == "Wild" then
		add_ldflags("gcc::-fuse-ld=wild", "clang::-fuse-ld=wild")
	elseif Value == "Lld" then
		add_ldflags("gcc::-fuse-ld=lld", "clang::-fuse-ld=lld")
	end
end)
-- package("McfGThread", function() end)
target("OpenStgBase", function()
	set_kind("library")
	set_languages("c17", "cxx")
	set_encodings("utf-8")
	set_prefixname("lib")
	add_files("Source.CAndCpp/Base/*.c")
	add_includedirs("Source.CAndCpp/include", { public = true })
	add_options("LoaderArchitecture")
	add_options("ThreadsLibrary")
	add_options("ExternLinker")
	add_options("EnableLibdwarf")
	if is_plat("windows") then
		add_defines("_CRT_SECURE_NO_WARNINGS", "__STDC_WANT_LIB_EXT1__=1")
		add_defines("UNICODE=1", "_UNICODE=1")
	elseif is_plat("linux") then
		add_defines("_FORTIFY_SOURCE=true")
	end
	if is_mode("debug") then
		add_defines("DEBUG=1", "_DEBUG=1")
	end
	add_cflags("/Zc:__STDC__", { tools = { "cl", "clang_cl" }, public = true })
	add_cflags("/Zc:__plusplus", { tools = { "cl", "clang_cl" }, public = true })
	add_cxflags(
		"/SOURCE-CHARSET:utf-8",
		"/EXECUTION-CHARSET:utf-8",
		"/Wall",
		"/W4",
		{ tools = { "cl", "clang_cl" }, public = true }
	)
	add_cxflags(
		"gcc::-fexec-charset=UTF-8",
		"gcc::-finput-charset=UTF-8",
		"-rdynamic",
		"-fpic", -- 位置无关代码
		"-Wall",
		"-Wextra",
		"-Wpedantic",
		"-Wno-unused-parameter",
		"-Wno-tautological-undefined-compare",
		"-Wconversion",
		"-Wcast-align",
		"-Wincompatible-function-pointer-types",
		"-Wincompatible-function-pointer-types-strict",
		"-Wincompatible-pointer-types",
		{ public = true }
	)
end)
