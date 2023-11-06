#version 330 core //Koju verziju GLSL jezika da koristim (za programabilni pipeline: GL verzija * 100) i koji profil (core - samo programabilni pipeline, compatibility - core + zastarjele stvari)

//Kanali (in, out, uniform)
layout(location = 0) in vec2 inPos; //Pozicija tjemena
layout(location = 1) in vec4 inCol; //Boja tjemena - ovo saljemo u fragment sejder
out vec4 channelCol; //Izlazni kanal kroz koji saljemo boju do fragment sejdera
out vec3 colOffset; 
uniform vec2 uPos;
void main() //Glavna funkcija sejdera
{	

   if(inPos.y>0){ 
	gl_Position = vec4(inPos.x-uPos.x , inPos.y+uPos.y, 0.0, 1.0); //Pozitivan matematicki smer ukoliko je teme iznad x ose
	colOffset = vec3(inPos.y+uPos.y-0.5);  //Kako je y koordinata veca od nule, sabiramo vrednost uniforme sa koordinatom, oduzimamo 0.5 kako bismo dobili potamnjenje/posvetljenje                 
	channelCol = inCol;
	}
   else{
    gl_Position = vec4(inPos.x-uPos.x , inPos.y-uPos.y, 0.0, 1.0); //Negativan matematicki smer ukoliko je teme ispod x ose
	colOffset = vec3(abs(inPos.y-uPos.y)-0.5); //kako je y koordinata negativna, vrsimo oduzimanje vrednosti uniforme
	channelCol = inCol;
	}
	
}