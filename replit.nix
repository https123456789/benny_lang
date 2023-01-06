{ pkgs }: {
	deps = [
		pkgs.checkstyle
  pkgs.cppcheck
  pkgs.clang-tools
  pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
        pkgs.neovim
        pkgs.cpplint
        pkgs.gcc
	];
}