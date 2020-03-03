#version 330 core

#define MAXITER 100
#define PI 3.1415926535897932384626433832795

out vec4 fragColor;

uniform vec3 iResolution;
uniform float iTime;

//Funcion que calcula la ubicacion de los puntos
int julia(vec2 z, vec2 c){
    int i = 0;
    vec2 zi = z;

    for(int n=0; n < MAXITER; ++n)
    {
        if(dot(zi,zi) > 2.*PI)
        break;
        i++;
        zi = c*vec2(sin(zi.x)*cosh(zi.y),cos(zi.x)*sinh(zi.y));      // c*sin(zi)  Seno de un numero complejo

    }

    return i;
}

//Transformamos las coordenadas de la pantalla a puntos complejos en el espacio definido.
vec2 pixelToComplex(vec2 resolucion, vec2 pixelPosition, float zoom){

    vec2 vectorComplejo = (2.*pixelPosition.xy - resolucion.xy) / resolucion.x;

    //Movemos para hacer zoom justo a un espiral.
    return vectorComplejo/(zoom*zoom) + vec2(-1.08697,0.66294);
}

//Funcion principal que correra el shader.
void mainImage(out vec4 fragColor,in vec2 fragCoord ){

    //obtenemos la posicion del punto en complejo
    vec2 z = pixelToComplex(iResolution.xy, fragCoord.xy, iTime);

    // Ejecutamos la funcion de julia, y guardamos el numero de la iteracion
    int iter = julia(z, vec2(1, 2));

    //Solo hay blancos o negros
    fragColor = vec4(vec3(float(iter)/float(MAXITER)),1.0);
}

void main(){

    //Variable para almacenar el color de salida
    vec4 color;

    //Llamamos a la funcion principal del shader
    mainImage(color,gl_FragCoord.xy);

    //Asignamos el color a la salida del shader
    fragColor = color;
}