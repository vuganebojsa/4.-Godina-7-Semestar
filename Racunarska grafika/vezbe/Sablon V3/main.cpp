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
        -1.0, 0.0,    1.0, 1.0, 1.0, 0.0,  //tjeme 0
        0.0, 0.0,     1.0, 1.0, 1.0, 0.0,  //tjeme 1
        0.0, 1.0,    1.0, 1.0, 1.0, 0.0,  //tjeme 2
        -1.0, 1.0,    1.0, 1.0, 1.0, 0.0,  //tjeme 2

        -1.0, 0.0,    1.0, 0.0, 0.0, 0.0,  //tjeme 0
        0.0, 0.0,     1.0, 0.0, 0.0, 0.0,  //tjeme 1
        0.0, -1.0,    1.0, 0.0, 0.0, 0.0,  //tjeme 2
        -1.0, -1.0,    1.0, 0.0, 0.0, 0.0,  //tjeme 2

       0.0, 1.0,    1.0, 1.0, 1.0, 0.0,  //tjeme 0
        1.0, 1.0,     1.0, 1.0, 1.0, 0.0,  //tjeme 1
        1.0, -1.0,    1.0, 1.0, 1.0, 0.0,  //tjeme 2
        0.0, -1.0,    1.0, 1.0, 1.0, 0.0,  //tjeme 2


    };
    unsigned int stride = (2 + 4) * sizeof(float);

    unsigned int indices[] = // Indeksi tjemena
    {
        0, 1, 2, //Prvi trougao sacinjen od tjemena 0, tjemena 1 i tjemena 2 (Prednja strana mu je naprijed)
        0, 3, 2,

        4, 5, 6,
        4, 7, 6,

        8, 9, 10,
        10, 11, 8
        
    };

    float circle[30 * 2 + 4]; // +4 je za x i y koordinate centra kruga, i za x i y od nultog ugla
    float r = 0.5; //poluprecnik

    circle[0] = 0; //Centar X0
    circle[1] = 0; //Centar Y0
    int i;
    for (i = 0; i <= 30; i++)
    {

        circle[2 + 2 * i] = r * cos((3.141592 / 180) * (i * 360 / 30)); //Xi
        circle[2 + 2 * i + 1] = r * sin((3.141592 / 180) * (i * 360 / 30)); //Yi
    }

    //Vertex Array Object - Kontejner za VBO, EBO i pokazivace na njihove atribute i tjemena
    unsigned int VAO[2];
    glGenVertexArrays(2, VAO); //Generisi 1 kontejner na adresi od promjenljive "VAO"
    glBindVertexArray(VAO[0]); //Povezi VAO za aktivni kontekst - Sve sto radimo ispod ovoga ce se odnositi na kontejner "VAO"

    //Vertex Buffer Object - Nase figure koje crtamo
    unsigned int VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 + sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    //Element Buffer Object
    //Radimo identicne stvari kao za VBO, samo sto saljemo podatke o indeksima tjemena - na Element array buffer


    unsigned int unifiedShader = createShader("basic.vert", "basic.frag");
    int uColLoc = glGetUniformLocation(unifiedShader, "uCol"); //Nadji adresu uniforme - obavezno NAKON sto je napravljen sejder
    //glGetUniformLocation(objedinjeni sejder, ime uniforme kako je definisana unutar sejdera) - vraca lokaciju uniforme unutar sejder programa

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); 
    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
        glViewport(wWidth / 2 + 1, 0, wWidth / 2, wHeight);  // Da crtamo na desnoj polovini ekrana
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(circle) / (2 * sizeof(float)));

    
        glfwSwapBuffers(window);

        glfwPollEvents();
    }



    glDeleteBuffers(2, VBO);
    glDeleteVertexArrays(2, VAO);
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
