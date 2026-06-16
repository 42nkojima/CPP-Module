{
  description = "C++ Module development shell pinning the 42 toolchain";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      {
        devShells.default = pkgs.mkShell {
          packages = with pkgs; [
            # Compiler / build: provides `c++` (clang) so macOS builds match the
            # 42 Linux cluster instead of the host's native toolchain.
            clang
            gnumake

            # Formatting: clang-tools provides clang-format.
            clang-tools

            # Git hooks
            lefthook
          ];
        };
      }
    );
}
