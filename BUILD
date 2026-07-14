
cc_library(
	name = "nudny-cmd",
	srcs = [
		"src/nudny/cmd/cli_parser.cpp",
	],
	hdrs = [
		"include/nudny/cmd/cli_parser.hpp",
	],
	includes = [
		"include",
	],
	visibility = [
		"//visibility:public",
	],
	deps = [ 
		"@nlohmann_json//:json",
	],
)

cc_test(
	name = "nudny-cmd-test",
	includes = ["test/include"],
	srcs = glob([
		"test/include/nudny/cmd/cli_parser_test.hpp",
		"test/src/nudny/cmd/cli_parser_test.cpp"
	]),
	copts = [
		"-Wall",
		"-Wextra",
		"-Wpedantic",
	],
	deps = [
		":nudny-cmd",
		"@googletest//:gtest_main",
		"@nlohmann_json//:json",
	],
)

cc_binary(
	name = "app",
	srcs = [ "src/main.cpp"	],
	deps = [ 
		":nudny-cmd",
		"@nlohmann_json//:json"
	],
)
