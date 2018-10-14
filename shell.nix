let
  vscode-overlay = self: super: {
    vscode-with-extensions = super.vscode-with-extensions.override {
      vscodeExtensions = with super.vscode-extensions; [
        ms-vscode.cpptools
        bbenoist.Nix
      ] ++ super.vscode-utils.extensionsFromVscodeMarketplace [
        {
          name = "cmake";
          publisher = "twxs";
          version = "0.0.17";
          sha256 = "11hzjd0gxkq37689rrr2aszxng5l9fwpgs9nnglq3zhfa1msyn08";
        }
        {
          name = "cmake-tools";
          publisher = "vector-of-bool";
          version = "1.1.2";
          sha256 = "199nr3mimgvmc7nj2va7xgciba3b0863rjz4k6sizl7rkqjigca4";
        }
        {
          name = "clang-format";
          publisher = "xaver";
          version = "1.6.2";
          sha256 = "1cl61g6lwbknhgwxd1hwrbkyj9rb4mkk7k7lyiclsbyj99jdrywk";
        }
        {
          name = "githistory";
          publisher = "donjayamanne";
          version = "0.4.3";
          sha256 = "12vhs0jrzqh1gq38qfq0h3pfpnan01sx4a4ik14hdby0558han9j";
        }
      ];
    };
  };
  clang-tools-overlay = self: super: {
    llvmPackages = super.llvmPackages_7;
  };
in
  with import <nixpkgs> {
    overlays = [ vscode-overlay clang-tools-overlay ];
  };
  with import ./default.nix;

  pkgs.mkShell {
    inputsFrom = [
      rosalind
    ];
    buildInputs = [
      vscode-with-extensions
      which
      clang-tools
      git
    ];
  }
