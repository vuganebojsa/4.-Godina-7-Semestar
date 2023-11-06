// Autor: Nedeljko Tesanovic
// Opis: V3 Z5

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
        std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    unsigned int wWidth = 1280; //Podesiti u zavisnosti od rezolucije monitora
    unsigned int wHeight = 720;
    const char wTitle[] = "[Generic title]";
    window = glfwCreateWindow(wWidth, wHeight, wTitle, glfwGetPrimaryMonitor(), NULL); //fullscreen
    if (window == NULL)
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, wWidth, wHeight); //recentrira ekran (u nekim slucajevima fullscreen se ne centrira pravilno)

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }


    float vertices[] = {
        0.0, 0.0
    };

    unsigned int stride = 2 * sizeof(float);

    unsigned VAO;
    glGenVertexArrays(1, &VAO);
    unsigned VBO;
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float x = 0;
    float y = 0;
    unsigned int basicShader = createShader("basic.vert", "basic.frag");
    unsigned int uA = glGetUniformLocation(basicShader, "uA");
    unsigned int uPosLoc = glGetUniformLocation(basicShader, "uPos");    

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(5);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
                y += 0.01;
                if (y > 1.0)
                    y = -1;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            y -= 0.01;
            if (y < -1.0)
                y = 1;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            x += 0.01;
            if (x > 1.0)
                x = -1;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            x -= 0.01;
            if (x < -1.0)
                x = 1;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            x = 0;
            y = 0;
            glClear(GL_COLOR_BUFFER_BIT);
        }

        glUseProgram(basicShader);
        glUniform1f(uA, abs(sin(10 * (0.01 + abs(x) + abs(y)) * glfwGetTime())));
        //                      ^ 10 je hardcode-ovano ubrzanje pulsiranja. 0.01 je tu da tacka pulsira i u koordinatnom pocetku
        glBindVertexArray(VAO);
        glUniform2f(uPosLoc, x, y);
        glDrawArrays(GL_POINTS, 0, sizeof(vertices) / stride);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glUseProgram(0);

        glfwSwapBuffers(window);

    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(basicShader);

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
