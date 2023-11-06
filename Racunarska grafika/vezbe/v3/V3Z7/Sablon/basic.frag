#version 330 core //Koju verziju GLSL jezika da koristim (za programabilni pipeline: GL verzija * 100) i koji profil (core - samo programabilni pipeline, compatibility - core + zastarjele stvari)

//Kanali (in, out, uniform)
in vec4 channelCol; //Kanal iz Verteks sejdera - mora biti ISTOG IMENA I TIPA kao u vertex sejderu
in vec3 colOffset; //Promena boje u odnosu na udaljenost od x ose
out vec4 outCol; //Izlazni kanal koji ce biti zavrsna boja tjemena (ukoliko se ispisuju podaci u memoriju, koristiti layout kao za ulaze verteks sejdera)

void main() //Glavna funkcija sejdera
{
	outCol = vec4(channelCol.r+colOffset.r,channelCol.g+colOffset.g,channelCol.b+colOffset.b,1.0);
}