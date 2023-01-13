{ pkgs }: {
	deps = [
        pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
        pkgs.neovim
        pkgs.gcc
        pkgs.time
	];
}