{ stdenv, cmake, boost }:

stdenv.mkDerivation rec {
  pname = "rosalind";
  version = "1.0";
  name = "${pname}-${version}";
  src = ./.;
  nativeBuildInputs = [ cmake ];
  buildInputs = [ boost ];
}
