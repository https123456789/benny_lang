{ pkgs }: {
	deps = [
        pkgs.tokei
        pkgs.valgrind-light
        pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
        pkgs.neovim
        pkgs.gcc
        pkgs.time
	];
}