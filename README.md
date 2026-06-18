# CPP-Module

## Setup

Prerequisites: Nix and direnv are installed.

This repo pins clang/make/lefthook through a Nix flake so that builds on
macOS match the 42 Linux cluster (clang, c++98).

```sh
git clone git@github.com:42nkojima/CPP-Module.git
cd CPP-Module
direnv allow    # loads the flake devShell (clang, make, lefthook)
lefthook install
```
