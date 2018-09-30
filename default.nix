with (import <nixpkgs> {});
{
  rosalind = pkgs.callPackage ./rosalind.nix {};
}
