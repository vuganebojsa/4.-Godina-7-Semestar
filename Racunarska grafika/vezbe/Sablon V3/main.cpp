// Autor: Nedeljko Tesanovic
// Opis: EBO, Uniforme

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>


#include <GL/glew.h> 
#include <GLFW/glfw3.h>

unsigned int compileShader(GLenum type, const char* source);
unsigned int createShader(const char* vsSource, const char* fsSource);

int main(void)
{

    
    if (!glfwInit())
    {
        std::cout<<"GLFW Biblioteka se nije ucitala! :(\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    unsigned int wWidth = 500;
    unsigned int wHeight = 500;
    const char wTitle[] = "[Generic Title]";
    window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }



    float vertices[] = //Tjemena trougla koja sadrze sve informacije o njemu
    {
        //Pozicija    |    Boja
        //X    Y       R    G    B    A
        -0.25, 0.0,    1.0, 0.0, 0.0, 0.0,  //tjeme 0
        0.25, 0.0,     0.0, 1.0, 0.0, 0.0,  //tjeme 1
        -0.25, 0.25,    0.0, 0.0, 1.0, 0.0,  //tjeme 2
        0.25, 0.25,    1.0, 1.0, 0.0, 0.0,   //tjeme 3
    };
    unsigned int stride = (2 + 4) * sizeof(float);

    unsigned int indices[] = // Indeksi tjemena
    {
        0, 1, 2, //Prvi trougao sacinjen od tjemena 0, tjemena 1 i tjemena 2 (Prednja strana mu je naprijed)
        1, 2, 3, //Drugi trougao (Zadnja strana mu je naprijed)
    };

    //Vertex Array Object - Kontejner za VBO, EBO i pokazivace na njihove atribute i tjemena
    unsigned int VAO;
    glGenVertexArrays(1, &VAO); //Generisi 1 kontejner na adresi od promjenljive "VAO"
    glBindVertexArray(VAO); //Povezi VAO za aktivni kontekst - Sve sto radimo ispod ovoga ce se odnositi na kontejner "VAO"

    //Vertex Buffer Object - Nase figure koje crtamo
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Element Buffer Object
    //Radimo identicne stvari kao za VBO, samo sto saljemo podatke o indeksima tjemena - na Element array buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    unsigned int unifiedShader = createShader("basic.vert", "basic.frag");
    int uColLoc = glGetUniformLocation(unifiedShader, "uCol"); //Nadji adresu uniforme - obavezno NAKON sto je napravljen sejder
    //glGetUniformLocation(objedinjeni sejder, ime uniforme kako je definisana unutar sejdera) - vraca lokaciju uniforme unutar sejder programa

    glClearColor(0.5, 0.5, 0.5, 1.0);
    while (!glfwWindowShouldClose(window)) 
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        // [KOD ZA CRTANJE]
        glUseProgram(unifiedShader);
        glBindVertexArray(VAO);
        //Slanje vrijednosti na uniformu NAKON sto je aktiviran sejder
        float R = abs(sin(glfwGetTime())); //Absolutna vrijednost sinusa trenutnog vremena
        float G = 0.25;
        glUniform3f(uColLoc, R, G, 0); //Postavi uniformu na odredjenu vrijednost. 3f jer je uCol definisan kao vec3
        //glUniform(adresa uniforme, nova vrijednost uniforme) - Postavlja uniformu na prosledjenu vrijednost.
        //Ime zavisi od tipa uniforme (pogledati nomenklaturu sa prve prezentacije). 

        //Crtanje bez indeksa
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //To i nacrtamo
        //glDrawArrays(tip primitive, indeks pocetnog tjemena, koliko narednih tjemena crtamo);

        //Crtanje sa indeksima
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(0 * sizeof(unsigned int)));
        //glDrawElements(Tip primitive, koliko indeksa se koristi, koji su tip indeksi, pomjeraj sa pocetka niza indeksa da bi dosli do prvog indeksa koji koristimo

        glfwSwapBuffers(window);

        glfwPollEvents();
    }



    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(unifiedShader);

    glfwTerminate();
    return 0;
}

unsigned int compileShader(GLenum type, const char* source)
{
    //Uzima kod u fajlu na putanji "source", kompajlira ga i vraca sejder tipa "type"
    //Citanje izvornog koda iz fajla
    std::string content = "";
    std::ifstream file(source);
    std::stringstream ss;
    if (file.is_open())
    {
        ss << file.rdbuf();
        file.close();
        std::cout << "Uspjesno procitao fajl sa putanje \"" << source << "\"!" << std::endl;
    }
    else {
        ss << "";
        std::cout << "Greska pri citanju fajla sa putanje \"" << source << "\"!" << std::endl;
    }
     std::string temp = ss.str();
     const char* sourceCode = temp.c_str(); //Izvorni kod sejdera koji citamo iz fajla na putanji "source"

    int shader = glCreateShader(type); //Napravimo prazan sejder odredjenog tipa (vertex ili fragment)
    
    int success; //Da li je kompajliranje bilo uspjesno (1 - da)
    char infoLog[512]; //Poruka o gresci (Objasnjava sta je puklo unutar sejdera)
    glShaderSource(shader, 1, &sourceCode, NULL); //Postavi izvorni kod sejdera
    glCompileShader(shader); //Kompajliraj sejder

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success); //Provjeri da li je sejder uspjesno kompajliran
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog); //Pribavi poruku o gresci
        if (type == GL_VERTEX_SHADER)
            printf("VERTEX");
        else if (type == GL_FRAGMENT_SHADER)
            printf("FRAGMENT");
        printf(" sejder ima gresku! Greska: \n");
        printf(infoLog);
    }
    return shader;
}
unsigned int createShader(const char* vsSource, const char* fsSource)
{
    //Pravi objedinjeni sejder program koji se sastoji od Vertex sejdera ciji je kod na putanji vsSource

    unsigned int program; //Objedinjeni sejder
    unsigned int vertexShader; //Verteks sejder (za prostorne podatke)
    unsigned int fragmentShader; //Fragment sejder (za boje, teksture itd)

    program = glCreateProgram(); //Napravi prazan objedinjeni sejder program

    vertexShader = compileShader(GL_VERTEX_SHADER, vsSource); //Napravi i kompajliraj vertex sejder
    fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsSource); //Napravi i kompajliraj fragment sejder

    //Zakaci verteks i fragment sejdere za objedinjeni program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program); //Povezi ih u jedan objedinjeni sejder program
    glValidateProgram(program); //Izvrsi provjeru novopecenog programa

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_VALIDATE_STATUS, &success); //Slicno kao za sejdere
    if (success == GL_FALSE)
    {
        glGetShaderInfoLog(program, 512, NULL, infoLog);
        std::cout << "Objedinjeni sejder ima gresku! Greska: \n";
        std::cout << infoLog << std::endl;
    }

    //Posto su kodovi sejdera u objedinjenom sejderu, oni pojedinacni programi nam ne trebaju, pa ih brisemo zarad ustede na memoriji
    glDetachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    return program;
}
